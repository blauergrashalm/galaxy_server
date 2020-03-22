#ifndef DOT_H
#define DOT_H

#include "position_type.h"
#include <set>
#include <memory>
/**
 * @todo write docs
 */
class Dot
{

private:
    std::set< std::shared_ptr<Field> > fields;
    pos_type position;
    
    bool areFieldsSymetrical();
    bool isValid();
    
public:
    Dot(unsigned int x, unsigned int y) : position{x,y} {};
};

#endif // DOT_H
