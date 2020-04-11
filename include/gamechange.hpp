#ifndef GAMECHANGE_H
#define GAMECHANGE_H

#include "player.hpp"
#include "field.hpp"
#include "dot.hpp"

typedef std::weak_ptr<Player> p_ptr;
typedef std::shared_ptr<Field> f_ptr;
typedef std::shared_ptr<Dot> d_ptr;

class GameChange : public std::enable_shared_from_this<GameChange>
{
private:
    p_ptr player;
    f_ptr affected_field;
    d_ptr new_assoziation;
    d_ptr old_assoziation;

public:
    /**
     * Default constructor
     */
    GameChange(p_ptr p, f_ptr f) : player{p}, affected_field{f} {};

    GameChange(const GameChange &) = delete;
    GameChange &operator=(const GameChange &) = delete;
    GameChange(GameChange &&);
    GameChange &operator=(GameChange &&);
    /**
     * Destructor
     */
    ~GameChange();

    void set_dot(const d_ptr &);
    void apply();
    void revert();

    nlohmann::json toJson();
};

#endif // GAMECHANGE_H
