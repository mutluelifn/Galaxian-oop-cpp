#include <iostream>
#include "Galaxian.h"

void Galaxian::get_input(KeyPressed & keypressed)
{
    
    if(keypressed[LEFTARROW])
    {
        if(get_x() >= 0)
            move_left();
    }  
    if(keypressed[RIGHTARROW])
    {
        if(get_x() <= W - get_w())
            move_right();
    }
    
}
  
