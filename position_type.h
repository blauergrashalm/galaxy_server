#ifndef POS_TYPE_H
#define POS_TYPE_H

struct pos_type{

    unsigned int x;
    unsigned int y;
    
    bool operator<(const pos_type &right){
        if(this->x < right.x) return true;
        if(this->x == right.x && this->y < right.y) return true;
        return false;
    }
    
}

#endif
