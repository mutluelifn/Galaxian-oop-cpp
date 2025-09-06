#ifndef STARS_H
#define STARS_H

#include "Surface.h"

class Stars
{
public:
    Stars();
    void draw(Surface & surface);
    void move();
    
private:
    int x, y;
    int R;
    int r_, g_, b_;
    int dx, dy;


};

void move_stars(Stars star[], int size, Surface &);


#endif
