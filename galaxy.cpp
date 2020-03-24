#include "galaxy.h"
#include "network.h"


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
    players.insert( std::pair<websocketpp::connection_hdl, std::shared_ptr<Player> >(connection, new Player(connection)) );
}

void Galaxy::deletePlayer(websocketpp::connection_hdl connection)
{
    players.erase(connection);
}
