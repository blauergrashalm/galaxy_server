#include "galaxy.h"
#include "network.h"


void Galaxy::run()
{
    std::cout << "Galaxy wurde gestartet" << std::endl;
    Network net(this);
    std::cout << "Netzwerk erstellt" << std::endl;
    net.run(9000);
    std::cout << "Netzwerk gestartet" << std::endl;
    // wait for completion
    std::unique_lock<std::mutex> lock(exit_mutex);
    while (!needs_stopping) exit_condition.wait(lock);
    std::cout << "Galaxy Wartebedingung erfült" << std::endl;
    net.stop();
}

void Galaxy::stop()
{
    std::cout<< "Galaxie soll gestoppt werden" << std::endl;
    needs_stopping = true;
    exit_condition.notify_all();
}

void Galaxy::registerNewPlayer(websocketpp::connection_hdl connection)
{
    players.insert( std::pair<websocketpp::connection_hdl, std::shared_ptr<Player> >(connection, new Player(connection)) );
}

void Galaxy::deletePlayer(websocketpp::connection_hdl connection)
{
    players.erase(connection);
}
