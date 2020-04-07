#ifndef GALAXY_H
#define GALAXY_H

#include <condition_variable>
#include "player.h"
#include "network.h"
#include "nlohmann/json.hpp"
#include "gamechange.h"
#include "gamestate.h"
#include <queue>

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
    std::unique_ptr<GameState> current_state;
    std::queue<std::shared_ptr<GameChange> > history;
    
    void setPlayerName(std::string name);
    void makeAMove();
    nlohmann::json toJson();
    
    void makeGameChange(std::shared_ptr<Player> p, nlohmann::json payload);
public:
    
    Player& operator[](websocketpp::connection_hdl &con){return *players[con];};
    
    Galaxy();
    
    bool needs_stopping = false;
    void run();
    void stop();
    
    void registerNewPlayer(websocketpp::connection_hdl connection);
    void deletePlayer(websocketpp::connection_hdl connection);
    
    void executeCommand(websocketpp::connection_hdl con, std::string command, nlohmann::json payload);
    
};

#endif // GALAXY_H
