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

class Galaxy;
class NewGamePoll
{

private:
    player_set positive_votes;
    player_set negative_votes;

    std::mutex set_mutex;
    std::condition_variable cv;

    std::shared_ptr<Galaxy> g;
    int amount;

public:
    bool active = false;

    NewGamePoll(const std::shared_ptr<Galaxy> &g) : g{g} {};

    void reset(const shared_player &, int);

    bool allVoted()
    {
        return positive_votes.size() + negative_votes.size() >= amount;
    };

    void registerPositiveVote(const shared_player &p);

    void registerNegativeVote(const shared_player &p);

    nlohmann::json toJSON();
};
#endif