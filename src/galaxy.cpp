#include "galaxy.hpp"
#include "network.hpp"
#include <memory>
#include "debug_functions.hpp"

Galaxy::Galaxy() : net(*this), current_state(10, 10)
{
}

Galaxy::~Galaxy()
{
}

void Galaxy::run()
{
    poll.reset(new NewGamePoll(shared_from_this()));
    DBG_LOG(MEDIUM, "Galaxy startet");
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
        new_height = payload["height"];
        new_width = payload["width"];
        poll->reset(p, players.size());
    }
    else
    {
        stop();
    }
}

void Galaxy::noitifyVoteState(nlohmann::json vote)
{
    net.broadcast(players, vote);
}

void Galaxy::newGame()
{
    std::lock_guard<std::mutex> lock(net.message_mutex); // stop adding new messages
    std::lock_guard<std::mutex> lock2(my_mutex);         // wait until current processing is done
    net.setDiscardingTime();                             // tell network which messages should get invalidated

    history.clear();
    current_state = GameState(new_width, new_height);
    net.broadcast(players, toJson());
}

void Galaxy::makeGameChange(std::shared_ptr<Player> p, nlohmann::json payload)
{
    auto field = current_state[(unsigned int)payload["field"]];
    auto change = std::make_shared<GameChange>(p, field);
    if (payload["dot"] != nullptr)
    {
        change->set_dot(current_state((unsigned int)payload["dot"]));
    }
    change->apply();
    net.broadcast(players, change->toJson());
    history.push_back(change);
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
