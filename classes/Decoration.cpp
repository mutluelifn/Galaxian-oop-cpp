#include "Image.h"
#include "Rect.h"
#include "Surface.h"
#include "Decoration.h"
#include "Constants.h"

Image * Decoration::images[8] =
{
    new Image("images/galaxian/Planet9.png"),
    new Image("images/galaxian/Moon3.png"),
    new Image("images/galaxian/Planet4.png"),
    new Image("images/galaxian/Tulip.png"),
    new Image("images/galaxian/Sunflower.png"),
    new Image("images/galaxian/Tulip.png"),
    new Image("images/galaxian/Earth.png"),
    new Image("images/galaxian/WhiteCat11.png")
};


Decoration::Decoration(int i)
    : image(images[i]), select(i),
      rect(images[select]->getRect())
{
    switch(i)
    {
        case 0:
            rect.x = 45;
            rect.y = 75;
            break;
    
        case 1:
            rect.x = 500;
            rect.y = 50;
            break;
            
        case 2:
            rect.x = 450;
            rect.y = 400;
            break;
           
        case 3:
            rect.x = 457;
            rect.y = 260;
            break;
            
        case 4: 
            rect.x = 220;
            rect.y = 110;
            break;
            
        case 5:
            rect.x = 143;
            rect.y = 260;
            break;
        case 6:
            rect.x = 50;
            rect.y = 500;
            break;
        case 7:
            rect.x = W/2;
            rect.y = 600 - 32;
    }
}

void Decoration::draw(Surface & surface)
{
    surface.put_image(*(images[select]), rect);
}



