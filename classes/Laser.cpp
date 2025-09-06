#include <iostream>
#include "Entity.h"
#include "Laser.h"

Laser::Laser(bool is_from_ship0, int x0, int y0)
    : is_from_ship(is_from_ship0)
{
    if(is_from_ship)
    {
        set_rect(x0, y0 , 2, 15, 255, 105, 180);
        set_dy(-5);
    }
    else
    {
        set_rect(x0, y0, 2, 10, 225,196,255);
        set_dy(5);
    }
}

  
 
