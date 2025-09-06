#ifndef DECORATION_H
#define DECORATION_H

#include "Image.h"
#include "Rect.h"
#include "Surface.h"

class Decoration
{
  public:
    Decoration(int i);
    void draw(Surface & surface);
    Image * image;
    int select;
    Rect rect;
    static Image * images[8];
private:   
};


#endif
