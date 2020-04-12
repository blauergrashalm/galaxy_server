#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "websocketpp/server.hpp"

/**
 * @todo write docs
 */
static unsigned int p_id = 0;
/**
 * @brief represents a individual player/client
 *
 */
class Player
{
private:
public:
    /**
     * @brief unique player id
     *
     */
    const unsigned int id;
    /**
     * @brief the network connection the player uses
     *
     */
    websocketpp::connection_hdl websocket_handle;
    /**
     * Default constructor
     */
    Player(websocketpp::connection_hdl hdl) : id{p_id++}, websocket_handle{hdl}
    {
        std::cout << "Player " << id << " erstellt" << std::endl;
    };

    Player(const Player &) = delete;

    /**
     * Destructor
     */
    ~Player();

    std::string name;
    std::string passphrase;

    bool isActive()
    {
        return websocket_handle.use_count() > 0;
    };
};

#endif // PLAYER_H
