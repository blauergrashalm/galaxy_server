#ifndef NETWORK_H
#define NETWORK_H
#include "nlohmann/json.hpp"
#include "websocketpp/config/asio_no_tls.hpp"

#include "websocketpp/server.hpp"
#include "player.hpp"

#include <queue>
typedef websocketpp::server<websocketpp::config::asio> server_t;

/**
 * @brief the possible types of actions that can occour on the socket
 * 
 */
enum action_type
{
    SUBSCRIBE,
    UNSUBSCRIBE,
    MESSAGE
};

/**
 * @brief simple message type that stores relevant information about a message
 * 
 */
struct message_t
{
    websocketpp::connection_hdl connection;
    action_type type;
    server_t::message_ptr mesage;
};

class Galaxy;

/**
 * @brief Manages the Websocket connection
 * 
 */
class Network
{

    friend Galaxy;

private:
    /**
     * @brief knows the galaxy to send it messages
     * 
     */
    Galaxy &galaxy;

    /**
     * @brief input buffer, gets filled on message receive, gets emptied on another thread
     * 
     */
    std::queue<message_t> to_process;

    /**
     * @brief dedicated processing thread to eliminate race conditions
     * 
     */
    std::thread process_thread;

    /**
     * @brief mutex for protecting the to_process list.
     * 
     */
    std::mutex message_mutex;
    /**
     * @brief varible to notify prozessing thread
     * 
     */
    std::condition_variable messages_available;

    /**
     * @brief the websocket server
     * 
     */
    server_t server;

    /**
     * @brief state variable so all threads know when to stop
     * 
     */
    bool shutdown = false;

    void on_open(websocketpp::connection_hdl);
    void on_close(websocketpp::connection_hdl con);
    void on_message(websocketpp::connection_hdl, server_t::message_ptr);

public:
    Network() = delete;

    Network(Galaxy &);

    bool active = true;

    /**
     * @brief starts server and prozessing thread
     * 
     * @param port TCP Port on which server will listen
     */
    void run(uint16_t port);

    /**
     * @brief prozesses all incoming messages
     * 
     */
    void processMessages();

    /**
     * @brief starts the shutdown mechanism of the network operations
     * 
     */
    void stop();

    /**
     * @brief send a message to a player
     * 
     * @param p the receiver
     * @param data the data to send
     */
    void send(Player &p, nlohmann::json data);

    /**
     * @brief broadcast to all players
     * 
     * @param players the currently active players
     * @param data to broadcast
     */
    void broadcast(const std::map<websocketpp::connection_hdl, std::shared_ptr<Player>, std::owner_less<websocketpp::connection_hdl>> &players, nlohmann::json data);

    /**
     * @brief closes a specific connection
     * 
     */
    void closeCon(websocketpp::connection_hdl);
};

#endif // NETWORK_H
