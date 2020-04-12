#ifndef GALAXY_H
#define GALAXY_H

#include <list>

#include "nlohmann/json.hpp"

#include "player.hpp"
#include "gamechange.hpp"
#include "gamestate.hpp"
#include "network.hpp"

typedef websocketpp::connection_hdl web_con;
typedef std::shared_ptr<Player> shared_player;

class Galaxy
{
private:
    Network net;

    std::map<web_con, shared_player, std::owner_less<web_con>> players;
    std::list<std::shared_ptr<GameChange>> history;
    GameState current_state;

    void setPlayerName(std::string name);
    void makeAMove();
    nlohmann::json toJson();

    void makeGameChange(shared_player p, nlohmann::json payload);

public:
    Player &operator[](web_con &con) { return *players[con]; };

    Galaxy();

    Galaxy(const Galaxy &) = delete;
    Galaxy(Galaxy &&) = delete;
    Galaxy &operator=(const Galaxy &) = delete;
    Galaxy &operator=(Galaxy &&) = delete;

    ~Galaxy();

    bool needs_stopping = false;
    void run();
    void stop();

    void registerNewPlayer(web_con connection);
    void deletePlayer(web_con connection);

    void executeCommand(web_con con, std::string command, nlohmann::json payload);
};

#endif // GALAXY_H
