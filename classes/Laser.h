#ifndef LASER_H
#define LASER_H

#include "Entity.h"

class Laser : public Entity
{
public:
    Laser(bool is_from_ship, int, int);
    bool is_enemy()
    {
        return !(is_from_ship);
    }
    
private:
    int x,y;
    bool is_from_ship;
    
};


#endif
