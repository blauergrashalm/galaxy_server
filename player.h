#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "websocketpp/server.hpp"

/**
 * @todo write docs
 */
static unsigned int p_id = 0;
class Player
{

private:
    
public:
    const unsigned int id;
    websocketpp::connection_hdl websocket_handle;
    /**
     * Default constructor
     */
    Player(websocketpp::connection_hdl hdl):id{p_id++},websocket_handle{hdl}{};
    
    
    /**
     * Destructor
     */
    ~Player();
    
    std::string name;
    std::string passphrase;
    
    bool isActive(){
        return websocket_handle.use_count() > 0;
    };
    
};

#endif // PLAYER_H
