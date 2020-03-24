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

void Network::processMessages(){
    while(!(shutdown && to_process.empty())){
        std::cout << "Durchlauf des Prozessieren" << std::endl;
        std::unique_lock<std::mutex> lock(message_mutex);
        
        while(to_process.empty() && !shutdown){
            messages_available.wait(lock);
        }
        if(!to_process.empty()){
            message_t current = to_process.front();
            to_process.pop();
        }
        if (!shutdown) lock.unlock();
        
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
}


void Network::stop(){
    std::cout << "Netzwerk soll gestoppt werden" << std::endl;
    server.stop();
    shutdown = true;
    messages_available.notify_all();
    process_thread.join();
    std::cout << "Thread ist gejoint" << std::endl;
}

void Network::on_open(websocketpp::connection_hdl con)
{
    galaxy->registerNewPlayer(con);
    std::cout << "Neuen Mitspieler erstellt" << std::endl; 
}
