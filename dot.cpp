#include "dot.h"
#include "field.h"
json Dot::toJson()
{
    json dot;
    dot["x"] = position.x;
    dot["y"] = position.y;
    for(auto it = fields.begin(); it!=fields.end(); it++){
        dot["fields"].push_back((*it)->id);
    }
    dot["id"] = id;
    return dot;
}
