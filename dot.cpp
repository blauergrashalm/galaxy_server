#include "dot.h"

json Dot::toJson()
{
    json dot;
    dot["x"] = position.x;
    dot["y"] = position.y;
    dot["fields"] = fields.size();
    dot["id"] = id;
    return dot;
}
