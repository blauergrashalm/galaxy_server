#include "galaxy.h"
#include "network.h"
#include <memory>

Galaxy::Galaxy()
{
    current_state.reset(new GameState(10, 10));
}

void Galaxy::run()
{
    std::cout << "Galaxy wurde gestartet" << std::endl;
    net.reset(new Network(this));
    std::cout << "Netzwerk erstellt" << std::endl;
    net->run(9000);
}

void Galaxy::stop()
{
    net->stop();
    for (auto it = players.begin(); it != players.end(); it++)
    {
        net->closeCon(it->first);
    }
}

void Galaxy::registerNewPlayer(websocketpp::connection_hdl connection)
{
    players.insert(std::pair<websocketpp::connection_hdl, std::shared_ptr<Player>>(connection, std::make_shared<Player>(connection)));
}

void Galaxy::deletePlayer(websocketpp::connection_hdl connection)
{
    players.erase(connection);
}

void Galaxy::executeCommand(websocketpp::connection_hdl con, std::string command, nlohmann::json payload)
{
    auto p = players[con];
    if (command == "player_register")
    {
        p->name = payload["name"];
        net->send(*p, toJson());
    }
    else if (command == "game_change")
    {
        makeGameChange(p, payload);
    }
    else if (command == "new_game")
    {
        history.clear();
        current_state.reset(new GameState((int)payload["width"], (int)payload["height"]));
        net->broadcast(players, toJson());
    }
    else
    {
        stop();
    }
}

void Galaxy::makeGameChange(std::shared_ptr<Player> p, nlohmann::json payload)
{
    auto field = (*current_state)[(unsigned int)payload["field"]];
    std::shared_ptr<GameChange> change;
    if (payload["dot"] == nullptr)
    {
        change = std::make_shared<GameChange>(p, field, nullptr);
    }
    else
    {
        auto dot = (*current_state)((unsigned int)payload["dot"]);
        change = std::make_shared<GameChange>(p, field, dot);
    }
    change->apply(change);
    net->broadcast(players, change->toJson());
    history.push_back(change);
    while (history.size() > 5)
        history.pop_front();
}

nlohmann::json Galaxy::toJson()
{
    nlohmann::json galaxy;
    galaxy["state"] = current_state->toJson();
    galaxy["type"] = "galaxy";
    return galaxy;
}
