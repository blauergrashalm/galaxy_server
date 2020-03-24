#include "field.h"
#include "dot.h"

json Field::toJson(){
    json field;
    if(auto dot = assigned_dot.lock())
        field["dot"] = dot->id;
    else
        field["dot"] = nullptr;
    field["x"] = position.x;
    field["y"] = position.y;
    field["id"] = id;
    return field;
}
