#include <iostream>
#include "Entity.h"

Image * Entity::images[5] = {
    // new Image("images/galaxian/GalaxianGalaxip.gif")
    // new Image("images/galaxian/Pink_Galaxian.png")
     new Image("images/galaxian/CoquetteHamsterr.png")
    ,new Image("images/galaxian/GalaxianFlagship.gif"),
    //, new Image("images/galaxian/WhiteCat1.png"),
    new Image("images/galaxian/GalaxianRedAlien.gif"), new Image("images/galaxian/GalaxianAquaAlien.gif"),
    new Image("images/galaxian/GalaxianPurpleAlien.gif")
};

Entity::~Entity()
{
    //delete image;
}

Entity::Entity()
    :image(nullptr),alive(true), is_image(false),
     dx(0), dy(0), r(0), g(0), b(0), is_collide(false)
{}
    
Entity::Entity(int i)
    :image(images[i]), rect(image->getRect()),
     alive(true), is_image(true), dx(0), dy(0), is_collide(false)
     
{}

void Entity::set_x(int i)
{
    rect.x = i;
}

void Entity::set_y(int i)
{
    rect.y = i;
}

// When the entity does not have an image = Laser
void Entity::set_color(int r0, int g0, int b0)
{
    r = r0;
    g = g0;
    b = b0;
}

void Entity::set_dx(int i)
{
    dx = i;
}

void Entity::set_dy(int i)
{
    dy = i;
}

void Entity::move()
{
    rect.x += dx;
    rect.y += dy;
}

void Entity::draw(Surface & surface)
{
    if(alive)
    {
        if(is_image)
        {
            surface.put_image(*image, rect);
        }
        else
        {
        surface.put_rect(rect.x, rect.y, rect.w, rect.h, r , g , b);
        }
    }
}

// void Entity::move_left()
// {
//     dx = MOVE_LEFT;
//     dy = 0;
//     move();
// }

// void Entity::move_right()
// {
//     dx = MOVE_RIGHT;
//     dy = 0;
//     move();
// }

int Entity::get_x() const
{
    return rect.x;
}

int Entity::get_y() const
{
    return rect.y;
}

int Entity::get_w() const
{
    return rect.w;
}

int Entity::get_h() const
{
    return rect.h;
}

void Entity::set_rect(int x0, int y0, int w0, int h0, int r0, int g0, int b0)
{
    set_x(x0);
    set_y(y0);
    rect.h = h0;
    rect.w = w0;
    
    set_color(r0,g0,b0);
}

void Entity::die(Entity & entity)
{
    if(rect.x < entity.get_x() + entity.get_w()
       && entity.get_x() < rect.x + get_w()
       && rect.y <entity.get_y() + entity.get_h()
       && entity.get_y() < rect.y + get_h())
    {
        entity.alive = false;
        alive = false;
        is_collide = true;
        entity.is_collide = true;
    }
}

bool Entity::is_alive()
{
    return alive;
}

bool Entity::is_alive() const
{
    return alive;
}

void Entity::revive()
{
    alive = true;
    is_collide = false;
}
 
bool Entity::is_colliding(Entity & entity)
{
    return(rect.x < entity.get_x() + entity.get_w()
       && entity.get_x() < rect.x + get_w()
       && rect.y <entity.get_y() + entity.get_h()
           && entity.get_y() < rect.y + get_h());
}

void Entity::move_right()
{
    rect.x += MOVE_RIGHT;
}

void Entity::move_left()
{
    rect.x += MOVE_LEFT;
}
