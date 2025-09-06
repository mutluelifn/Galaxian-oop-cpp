#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Surface.h"
#include "Entity.h"
#include "Image.h"
#include "Rect.h"

const int FRAMES = 12;

class Explosion
{
  public:
    Explosion(const Entity & entity);
    void explode(Surface & surface);
    bool finished;
  private:
    Rect rect;
    int x, y;
    Image * image;
    static Image * images[FRAMES];
    int frames;
  
};


#endif
