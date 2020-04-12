#include "galaxy.hpp"
#include "newgamepoll.hpp"

void NewGamePoll::reset(const shared_player &p, int amount)
{
    positive_votes.insert(p);
    active = true;
    time_left = 10000;
    std::thread([&]() {
        for (int i = 0; i < 100; i++)
        {
            std::this_thread::sleep_for(millis(100));
            if (positive_votes.size() + negative_votes.size() == amount)
                break;
            time_left -= 100;
            g->noitifyVoteState(toJSON());
        }
        std::lock_guard<std::mutex> l(set_mutex);
        active = false;
        if (positive_votes.size() > negative_votes.size())
        {
            g->newGame();
        }
        positive_votes.clear();
        negative_votes.clear();
    }).detach();
}

nlohmann::json NewGamePoll::toJSON()
{
    std::lock_guard<std::mutex> l(set_mutex);
    nlohmann::json result;
    result["type"] = "poll";
    result["positives"] = positive_votes.size();
    result["negatives"] = negative_votes.size();
    result["time_left"] = time_left;
    return result;
}