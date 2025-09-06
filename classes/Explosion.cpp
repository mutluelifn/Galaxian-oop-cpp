#include "Explosion.h"
#include "Surface.h"

Image * Explosion::images[FRAMES] = {
    new Image("images/galaxian/Explosion1.png"),
    new Image("images/galaxian/Explosion1.png"),
    new Image("images/galaxian/Explosion2.png"),
    new Image("images/galaxian/Explosion2.png"),
    new Image("images/galaxian/Explosion3.png"),
    new Image("images/galaxian/Explosion3.png"),
    new Image("images/galaxian/Explosion4.png"),
    new Image("images/galaxian/Explosion4.png"),
    new Image("images/galaxian/Explosion5.png"),
    new Image("images/galaxian/Explosion5.png"),
    new Image("images/galaxian/Explosion6.png"),
    new Image("images/galaxian/Explosion6.png"),

};


Explosion::Explosion(const Entity & entity)
    : image(images[0]), rect(images[0]->getRect()),
     finished(false), frames(0)
{
    rect.x = entity.get_x();
    rect.y = entity.get_y();
}

void Explosion::explode(Surface & surface)
{
    if (!finished)
    {
        if(frames < FRAMES - 1)
            frames++;
        else
            finished = true;
        surface.put_image(*(images[frames]), rect);
    }
    
}
