#ifndef GALAXIAN_H
#define GALAXIAN_H

#include "Entity.h"
#include "Includes.h"
#include "Constants.h"

class Galaxian: public Entity
{
  public:
    Galaxian()
        :Entity(SHIP)
    {
        set_x(W / 2);
        set_y(H - get_h());
    }
    void get_input(KeyPressed & keypressed);
  private:
};




#endif

