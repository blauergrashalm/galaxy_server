#include "galaxy.h"
#include "network.h"

Galaxy::Galaxy()
{
    current_state.reset(new GameState(10,10));
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
    std::cout<< "Galaxie soll gestoppt werden" << std::endl;
    net->stop();
}

void Galaxy::registerNewPlayer(websocketpp::connection_hdl connection)
{
    players.insert( std::pair<websocketpp::connection_hdl, std::shared_ptr<Player> >(connection, std::make_shared<Player>(connection)));
}

void Galaxy::deletePlayer(websocketpp::connection_hdl connection)
{
    players.erase(connection);
}

void Galaxy::executeCommand(websocketpp::connection_hdl con, std::string command, nlohmann::json payload)
{
    if(command == "player_register"){
        auto p = *players[con];
        p.name = payload["name"];
        net->send(p, toJson());
    }else{
        stop();
    }
}

nlohmann::json Galaxy::toJson()
{
    nlohmann::json galaxy;
    galaxy["state"] = current_state->toJson();
    galaxy["type"] = "galaxy";
    return galaxy;
}

