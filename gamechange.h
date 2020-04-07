#ifndef GAMECHANGE_H
#define GAMECHANGE_H

#include "player.h"
#include "field.h"
#include "dot.h"

typedef std::shared_ptr<Player> p_ptr;
typedef std::shared_ptr<Field> f_ptr;
typedef std::shared_ptr<Dot> d_ptr;


class GameChange
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
    GameChange(p_ptr p, f_ptr f, d_ptr d):player{p},affected_field{f},new_assoziation{d}{};

    /**
     * Destructor
     */
    ~GameChange();
    
    void apply(std::shared_ptr<GameChange> self);
    void revert();
    
    nlohmann::json toJson();

};

#endif // GAMECHANGE_H