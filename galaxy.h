#ifndef GALAXY_H
#define GALAXY_H

#include <condition_variable>
#include "player.h"
#include "network.h"

/**
 * @todo write docs

 */
class Galaxy
{
private:
    std::condition_variable exit_condition;
    std::mutex exit_mutex;
    std::unique_ptr<Network> net;
    
    std::map<websocketpp::connection_hdl, std::shared_ptr<Player>, std::owner_less<websocketpp::connection_hdl> > players;
    
public:
    
    Player& operator[](websocketpp::connection_hdl &con){return *players[con];};
    
    
    bool needs_stopping = false;
    void run();
    void stop();
    
    void registerNewPlayer(websocketpp::connection_hdl connection);
    void deletePlayer(websocketpp::connection_hdl connection);
    
    
};

#endif // GALAXY_H
