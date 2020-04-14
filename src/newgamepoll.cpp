#include "galaxy.hpp"
#include "newgamepoll.hpp"
#include <chrono>
#include "debug_functions.hpp"
using namespace std::chrono_literals;
void NewGamePoll::reset(const shared_player &p, int num_players)
{
    if (active)
        return;
    amount = num_players;
    active = true;
    registerPositiveVote(p);
    std::thread([&]() {
        std::unique_lock<std::mutex> l(set_mutex);
        DBG_LOG(LOW, "thread startet");
        cv.wait_for(l, 10s, [&]() { return allVoted(); });
        DBG_LOG(LOW, "wait ended; all votes? " + std::to_string(allVoted()));
        active = false;
        if (positive_votes.size() > negative_votes.size())
        {
            g.newGame();
        }
        positive_votes.clear();
        negative_votes.clear();
    }).detach();
}

nlohmann::json NewGamePoll::toJSON()
{
    nlohmann::json result;
    result["type"] = "poll";
    result["positives"] = positive_votes.size();
    result["negatives"] = negative_votes.size();
    return result;
}

void NewGamePoll::registerPositiveVote(const shared_player &p)
{
    std::lock_guard<std::mutex> l(set_mutex);
    if (active)
    {
        positive_votes.insert(p);
        negative_votes.erase(p);
        g.noitifyVoteState(toJSON());
        cv.notify_all();
    }
};

void NewGamePoll::registerNegativeVote(const shared_player &p)
{
    std::lock_guard<std::mutex> l(set_mutex);
    if (active)
    {
        negative_votes.insert(p);
        positive_votes.erase(p);
        g.noitifyVoteState(toJSON());
        cv.notify_all();
    }
};