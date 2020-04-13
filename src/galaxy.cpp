#include "galaxy.hpp"
#include "network.hpp"
#include <memory>
#include "debug_functions.hpp"
#include "json_schemas.hpp"

Galaxy::Galaxy() : net(*this), current_state(10, 10)
{
}

Galaxy::~Galaxy()
{
    for (auto &&c : commands)
    {
        delete c.second.my_validator;
    }
}

void Galaxy::run()
{
    commands = {
        {"player_register", command_mapping{std::bind(&Galaxy::playerSetup, this, _1, _2), new validator(constants::register_player_schema)}},
        {"game_change", command_mapping{std::bind(&Galaxy::makeGameChange, this, _1, _2), new validator(constants::game_change_schema)}},
        {"new_game", command_mapping{std::bind(&Galaxy::makePoll, this, _1, _2), new validator(constants::new_game_schema)}},
        {"cast_vote", command_mapping{std::bind(&Galaxy::castVote, this, _1, _2), new validator(constants::cast_vote_schema)}}};
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

void Galaxy::playerSetup(shared_player &p, const json &payload)
{
    p->name = payload["name"];
    net.send(*p, toJson());
}

void Galaxy::deletePlayer(web_con connection)
{
    players.erase(connection);
}

void Galaxy::executeCommand(web_con con, std::string command, nlohmann::json payload)
{
    auto p = players[con];
    try
    {
        auto &to_execute = commands.at(command);
        to_execute.my_validator->validate(payload);
        to_execute.call(p, payload);
    }
    catch (std::out_of_range)
    {
        std::cout << "from: " << p->name << ": Kommando unbekannt, sorry" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "from: " << p->name << ": Kommando nicht verstanden: " << e.what() << std::endl;
    }
}

void Galaxy::noitifyVoteState(nlohmann::json vote)
{
    net.broadcast(players, vote);
}

void Galaxy::makePoll(shared_player &p, const json &payload)
{
    new_height = payload["height"];
    new_width = payload["width"];
    poll->reset(p, players.size());
}

void Galaxy::castVote(shared_player &p, const json &payload)
{
    if (payload["vote"] == "positive")
        poll->registerPositiveVote(p);
    else
        poll->registerNegativeVote(p);
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

void Galaxy::makeGameChange(shared_player &p, const json &payload)
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
    for (auto &&p : players)
        galaxy["players"].push_back(p.second->toJson());
    galaxy["type"] = "galaxy";
    return galaxy;
}
