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
    
    std::weak_ptr<websocketpp::connection_hdl> websocket_handle;
    
public:
    /**
     * Default constructor
     */
    Player(std::string name, std::string passphrase): name{name}, passphrase{passphrase}{};

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
