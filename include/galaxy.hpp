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

/**
 * @brief Main class of this project. Manages all ressources
 * 
 */
class Galaxy
{
private:
    Network net;

    /**
     * @brief manages all active players with their websocket connection
     * 
     */
    std::map<web_con, shared_player, std::owner_less<web_con>> players;

    /**
     * @brief History of the latest Game changes, as done from the players
     * 
     */
    std::list<std::shared_ptr<GameChange>> history;

    /**
     * @brief represents the current State of the Game
     * 
     */
    GameState current_state;

    /**
     * @brief generates a json object of the current state of the galaxy
     * 
     * @return nlohmann::json json object containing type, players and game_state
     */
    nlohmann::json toJson();

    /**
     * @brief converts data from the client into a GameChange and applies it
     * 
     * @param p The Player that sent the Change Request
     * @param payload The data representing the change
     */
    void makeGameChange(shared_player p, nlohmann::json payload);

public:
    /**
     * @brief gets the Player to the corresponding connection
     * 
     * @param con an active websocket connection
     * @return Player& the Player that is assoziated with that connection
     */
    Player &operator[](web_con &con) { return *players[con]; };

    /**
     * @brief Construct a new Galaxy object with a default GameState of 10 x 10 Fields
     * 
     */
    Galaxy();

    Galaxy(const Galaxy &) = delete;
    Galaxy(Galaxy &&) = delete;
    Galaxy &operator=(const Galaxy &) = delete;
    Galaxy &operator=(Galaxy &&) = delete;

    ~Galaxy();

    /**
     * @brief starts the "game loop". this blocks the thread until server stops.
     * 
     */
    void run();
    /**
     * @brief starts notifing all components to shutdown.
     * 
     */
    void stop();

    /**
     * @brief needs to be called when a new Player connects to the server
     * 
     * @param connection the websocket connection with wich the Player is identifiable
     */
    void registerNewPlayer(web_con connection);
    /**
     * @brief needs to be called when Player disconnects from server
     * 
     * @param connection the connection that just closed
     */
    void deletePlayer(web_con connection);

    /**
     * @brief central method that manages incomming messages from clients
     * 
     * @param con the connection from wich the messge came
     * @param command the command the client wants to execute
     * @param payload parameters to the execution request
     */
    void executeCommand(web_con con, std::string command, nlohmann::json payload);
};

#endif // GALAXY_H
