#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <map>
#include <memory>
#include "field.h"
#include "dot.h"
#include "position_type.h"
#include "nlohmann/json.hpp"
#include "gamechange.h"

using json = nlohmann::json;

class GameState
{
private:

    unsigned int x_size, y_size;
    
    std::vector< std::vector< std::shared_ptr<Field> > > fields;
    std::map<pos_type, std::shared_ptr<Dot> > dots;
    
    void generateRandomDots();

public:
    GameState(unsigned int x_size, unsigned int y_size);
    json toJson();
    
    void applyGameChange(const GameChange &change);
    
};

#endif // GAMESTATE_H
