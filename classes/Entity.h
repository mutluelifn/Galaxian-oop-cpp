#ifndef ENTITY_H
#define ENTITY_H

#include "Image.h"
#include "Rect.h"
#include "Surface.h"

const int MOVE_LEFT = -3;
const int MOVE_RIGHT = 3;

const int SHIP = 0;
const int FLAG_SHIP = 1;
const int RED_SHIP = 2;
const int AQUA_SHIP = 3;
const int PURPLE_SHIP = 4;

class Entity
{
  public:
    Entity();
    Entity(int i);
    ~Entity();
    void set_x(int i);
    void set_y(int i);
    void set_color(int, int, int);
    void set_dx(int);
    void set_dy(int);
    int get_x() const;
    int get_y() const;
    void move();
    void draw(Surface & surface);
    void move_left();
    void move_right();
    int get_w() const;
    int get_h() const;
    void set_rect(int x0, int y0, int h0, int w0,
                  int r0, int g0, int b0);
    void die(Entity & entity);
    bool is_alive();
    bool is_alive() const;
    bool is_collide;
    void revive();
    bool is_colliding(Entity & entity);
    
  private:
    bool alive;
    int dx,dy;
    Image * image; 
    bool is_image;
    Rect rect;
    int r,g,b;
    static Image * images[5];
};



#endif
