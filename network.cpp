#include "network.h"
#include "galaxy.h"

Network::Network(Galaxy *parent) : galaxy{parent}
{
    server.init_asio();

    server.set_open_handler(std::bind(&Network::on_open, this, std::placeholders::_1));
    server.set_close_handler(std::bind(&Network::on_close, this, std::placeholders::_1));
    server.set_message_handler(std::bind(&Network::on_message, this, std::placeholders::_1, std::placeholders::_2));
    std::cout << "Server gestartet" << std::endl;
}

void Network::processMessages()
{
    while (!(shutdown && to_process.empty()))
    {
        std::cout << "Durchlauf des Prozessieren" << std::endl;
        std::unique_lock<std::mutex> lock(message_mutex);

        while (to_process.empty() && !shutdown)
        {
            messages_available.wait(lock);
        }
        if (shutdown)
            return;
        message_t current = to_process.front();
        to_process.pop();
        lock.unlock();
        json msg;

        switch (current.type)
        {
        case SUBSCRIBE:
            std::cout << "Subscribe verarbeiten" << std::endl;
            galaxy->registerNewPlayer(current.connection);
            break;
        case MESSAGE:
            std::cout << "Message verarbeiten: " << current.mesage->get_payload() << std::endl;
            msg = json::parse(current.mesage->get_payload());
            galaxy->executeCommand(current.connection, msg["command"], msg["payload"]);
            break;
        case UNSUBSCRIBE:
            galaxy->deletePlayer(current.connection);
            break;
        }

        // do processing
        //         galaxy->stop();
    }
    std::cout << "Prozess-Thread endet" << std::endl;
}

void Network::run(uint16_t port)
{
    process_thread = std::thread(std::bind(&Network::processMessages, this));
    server.listen(port);
    server.start_accept();
    server.run();
    process_thread.join();
}

void Network::stop()
{
    std::cout << "Netzwerk soll gestoppt werden" << std::endl;
    server.stop_listening();
    shutdown = true;
    messages_available.notify_all();
}

void Network::on_open(websocketpp::connection_hdl con)
{
    std::lock_guard<std::mutex> g(message_mutex);
    to_process.push({con, SUBSCRIBE, nullptr});
    messages_available.notify_one();
}

void Network::on_message(websocketpp::connection_hdl con, server_t::message_ptr msg)
{
    std::lock_guard<std::mutex> g(message_mutex);
    to_process.push({con, MESSAGE, msg});
    messages_available.notify_one();
}

void Network::on_close(websocketpp::connection_hdl con)
{
    std::lock_guard<std::mutex> g(message_mutex);
    to_process.push({con, UNSUBSCRIBE, nullptr});
    messages_available.notify_one();
}

void Network::send(Player &p, nlohmann::json data)
{
    server.send(p.websocket_handle, data.dump(), websocketpp::frame::opcode::TEXT);
}

void Network::broadcast(const std::map<websocketpp::connection_hdl, std::shared_ptr<Player>, std::owner_less<websocketpp::connection_hdl>> &players, nlohmann::json data)
{
    for (auto &&pair : players)
    {
        server.send(pair.first, data.dump(), websocketpp::frame::opcode::TEXT);
    }
}

void Network::closeCon(websocketpp::connection_hdl con)
{
    server.close(con, websocketpp::close::status::normal, "server goes to sleep");
}
