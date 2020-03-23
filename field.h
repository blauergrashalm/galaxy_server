#ifndef FIELD_H
#define FIELD_H

#include "position_type.h"

#include "nlohmann/json.hpp"

#include <memory>

using json = nlohmann::json;

class GameChange;
class Dot;

class Field
{
private:
    pos_type position;
    std::weak_ptr<Dot> asigned_dot;
    std::weak_ptr<GameChange> last_change;
    
    
public:
   
    Field(unsigned int x, unsigned int y) : position{x,y} {};

    json toJson();
};

#endif // FIELD_H
