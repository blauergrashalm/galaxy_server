#ifndef GAMECHANGE_H
#define GAMECHANGE_H

#include "player.hpp"
#include "field.hpp"
#include "dot.hpp"

typedef std::weak_ptr<Player> p_ptr;
typedef std::shared_ptr<Field> f_ptr;
typedef std::shared_ptr<Dot> d_ptr;

/**
 * @brief Represents an atomic change to the gamestate. Can be reverted, once applied
 * 
 */
class GameChange : public std::enable_shared_from_this<GameChange>
{
private:
    p_ptr player;
    f_ptr affected_field;
    /**
     * @brief the new dot the affected field belongs to
     * 
     */
    d_ptr new_assoziation;
    /**
     * @brief if field was attached to a different dot before this dot gets stored here.
     * 
     */
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

    /**
     * @brief Set the new assigned dot
     * 
     */
    void set_dot(const d_ptr &);
    /**
     * @brief apply this change
     * 
     */
    void apply();
    /**
     * @brief revert this change
     * 
     */
    void revert();

    /**
     * @brief serialization of the change
     * 
     * @return nlohmann::json 
     */
    nlohmann::json toJson();
};

#endif // GAMECHANGE_H
