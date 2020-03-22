#ifndef GAMECHANGE_H
#define GAMECHANGE_H

#include "player.h"
#include "field.h"
#include "dot.h"
/**
 * @todo write docs
 */
class GameChange
{
private: 
    std::shared_ptr<Player> player;
    std::shared_ptr<Field> affected_field;
    std::shared_ptr<Dot> new_assoziation
    
public:
    /**
     * Default constructor
     */
    GameChange();

    /**
     * Destructor
     */
    ~GameChange();

};

#endif // GAMECHANGE_H
