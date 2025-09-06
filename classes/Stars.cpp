#include "Stars.h"
#include "Constants.h"

Stars::Stars()
    :x(rand() % W), y(rand() % H),
     r_(rand() % 256), g_(rand() % 256),
     b_(rand() % 256), R(1),  dx(0), dy(3)
{
}

void Stars::draw(Surface & surface)
{
    surface.put_circle(x, y, R, rand() % 256, rand() % 256, rand() % 256);
}

void Stars::move()
{
     y += dy;
    if(y > H)
    {
        *this = Stars();
        y = 0;
    }
}


void move_stars(Stars stars[], int size, Surface & surface)
{
    for(int i = 0; i < size; ++i)
    {
        stars[i].move();
        stars[i].draw(surface);
    }
}
