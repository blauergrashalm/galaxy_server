#ifndef NETWORK_H
#define NETWORK_H
#include "nlohmann/json.hpp"
#include "websocketpp/config/asio_no_tls.hpp"

#include "websocketpp/server.hpp"
#include "player.hpp"

#include <queue>
typedef websocketpp::server<websocketpp::config::asio> server_t;

enum action_type
{
    SUBSCRIBE,
    UNSUBSCRIBE,
    MESSAGE
};

struct message_t
{
    websocketpp::connection_hdl connection;
    action_type type;
    server_t::message_ptr mesage;
};

class Galaxy;

class Network
{

    friend Galaxy;

private:
    Galaxy &galaxy;
    std::queue<message_t> to_process;

    std::thread process_thread;

    std::mutex message_mutex;
    std::condition_variable messages_available;

    server_t server;

    bool shutdown = false;

    void on_open(websocketpp::connection_hdl);
    void on_close(websocketpp::connection_hdl con);
    void on_message(websocketpp::connection_hdl, server_t::message_ptr);

public:
    Network() = delete;

    Network(Galaxy&);

    bool active = true;

    void run(uint16_t port);

    void processMessages();

    void stop();

    void send(Player &p, nlohmann::json data);

    void broadcast(const std::map<websocketpp::connection_hdl, std::shared_ptr<Player>, std::owner_less<websocketpp::connection_hdl>> &players, nlohmann::json data);

    void closeCon(websocketpp::connection_hdl);
};

#endif // NETWORK_H
