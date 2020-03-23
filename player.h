#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "websocketpp/server.hpp"

/**
 * @todo write docs
 */
class Player
{

private:
    
    websocketpp::connection_hdl websocket_handle;
    
public:
    /**
     * Default constructor
     */
    Player(websocketpp::connection_hdl hdl):websocket_handle{hdl}{};

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
