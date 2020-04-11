#ifndef POS_TYPE_H
#define POS_TYPE_H

struct pos_type
{
    unsigned int x;
    unsigned int y;

    inline bool operator<(const pos_type &right) const
    {
        if (y < right.y)
            return true;
        if (y == right.y && x < right.x)
            return true;
        return false;
    }
};

#endif
