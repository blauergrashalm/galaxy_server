#ifndef NEW_GAME_POLL
#define NEW_GAME_POLL
#include "player.hpp"
#include <thread>
#include <mutex>
#include <unordered_set>
#include <functional>
#include "nlohmann/json.hpp"

typedef std::shared_ptr<Player> shared_player;
typedef std::unordered_set<shared_player> player_set;
typedef std::chrono::milliseconds millis;

class Galaxy;
class NewGamePoll
{

private:
    player_set positive_votes;
    player_set negative_votes;

    std::mutex set_mutex;

    std::shared_ptr<Galaxy> g;

public:
    bool active = false;
    int time_left = 0;

    NewGamePoll(const std::shared_ptr<Galaxy> &g) : g{g} {};

    void reset(const shared_player &, int);

    void registerPositiveVote(const shared_player &p)
    {
        std::lock_guard<std::mutex> l(set_mutex);
        if (active)
        {
            positive_votes.insert(p);
            negative_votes.erase(p);
        }
    };

    void registerNegativeVote(const shared_player &p)
    {
        std::lock_guard<std::mutex> l(set_mutex);
        if (active)
        {
            negative_votes.insert(p);
            positive_votes.erase(p);
        }
    };

    nlohmann::json toJSON();
};
#endif