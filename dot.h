#ifndef DOT_H
#define DOT_H

#include "position_type.h"

#include <set>
#include <map>
#include <memory>

//forward declarations:
class Field;

// typedefs
typedef std::shared_ptr<Field> field_ptr_t;

class Dot
{

private:
    std::set< field_ptr_t> fields;
    pos_type position;
    
public:
    Dot(unsigned int x, unsigned int y) : position{x,y} {};
    
    bool areFieldsSymetrical();
    bool isValid();
    
    void registerField(field_ptr_t);
    void removeField(field_ptr_t);
};

#endif // DOT_H
