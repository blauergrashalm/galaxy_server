#ifndef FIELD_H
#define FIELD_H

#include "position_type.h"

#include "nlohmann/json.hpp"

#include <memory>

using json = nlohmann::json;

class GameChange;
class Dot;

static unsigned int f_id;

class Field
{
private:
    pos_type position;
public:
    
    std::weak_ptr<GameChange> last_change;
    std::weak_ptr<Dot> assigned_dot;
    const unsigned int id;
   
    Field(unsigned int x, unsigned int y): position{x,y},id{f_id++}{};

    json toJson();
};

#endif // FIELD_H
