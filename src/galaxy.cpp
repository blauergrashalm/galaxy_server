#include "galaxy.hpp"
#include "network.hpp"
#include <memory>

Galaxy::Galaxy() : net(*this), current_state(10, 10)
{
}

Galaxy::~Galaxy()
{
}

void Galaxy::run()
{
    std::cout << "Galaxy wurde gestartet" << std::endl;
    net.run(9000);
}

void Galaxy::stop()
{
    net.stop();
    for (auto it = players.begin(); it != players.end(); it++)
    {
        net.closeCon(it->first);
    }
}

void Galaxy::registerNewPlayer(web_con connection)
{
    players.insert(std::pair<web_con, shared_player>(connection, std::make_shared<Player>(connection)));
}

void Galaxy::deletePlayer(web_con connection)
{
    players.erase(connection);
}

void Galaxy::executeCommand(web_con con, std::string command, nlohmann::json payload)
{
    auto p = players[con];
    if (command == "player_register")
    {
        p->name = payload["name"];
        net.send(*p, toJson());
    }
    else if (command == "game_change")
    {
        makeGameChange(p, payload);
    }
    else if (command == "new_game")
    {
        history.clear();
        current_state = GameState((int)payload["width"], (int)payload["height"]);
        net.broadcast(players, toJson());
    }
    else
    {
        stop();
    }
}

void Galaxy::makeGameChange(std::shared_ptr<Player> p, nlohmann::json payload)
{
    auto field = current_state[(unsigned int)payload["field"]];
    GameChange change(p, field);
    if (payload["dot"] != nullptr)
    {
        change.set_dot(current_state((unsigned int)payload["dot"]));
    }
    change.apply();
    net.broadcast(players, change.toJson());
    history.push_back(std::move(change));
    while (history.size() > 5)
        history.pop_front();
}

nlohmann::json Galaxy::toJson()
{
    nlohmann::json galaxy;
    galaxy["state"] = current_state.toJson();
    galaxy["type"] = "galaxy";
    return galaxy;
}
