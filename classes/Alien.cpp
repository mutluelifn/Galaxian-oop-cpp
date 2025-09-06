#include "Alien.h"
#include "Entity.h"
#include "Constants.h"

Alien::Alien(int i, int x, int y)
    : Entity(i), attack(false), coming_back(false),
      x0(x), y0(y), home(NULL), mother(NULL), timer(0)
{
    set_dx(MOVE_RIGHT);
}

Alien * Alien::MAX = NULL;
Alien * Alien::MIN = NULL;

void Alien::move_curve(int displacement)
{
        double period = 3.141;
        static int amplitude = 6;
        set_dy(1);
        set_dx(amplitude  * sin(period * get_y()/ 100));

//.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:COMING BACK｡.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:✿
        if(get_y() >= H)
        {
            coming_back = true;
            set_y(0);
            
        }
        
        move();      
}

void Alien::move_returning(int displacement)
{
    set_dy(2);
    set_x(30  * sin(3 * get_y()) + (x0 + displacement));
    move();
    if(get_y() > y0)
    {
        set_x(x0 + displacement);
        set_y(y0);
        attack = false;
        coming_back = false;
    }
}

void Alien::move_together(bool LEFT, bool RIGHT)
{
    set_dy(0);
    if(LEFT)
        move_left();
    else if(RIGHT)
        move_right();
    
} 

void Alien::move_follow()
{
    static int x = home->get_x();
    static int y = home->get_y();
    
    if(home != NULL && home->is_alive())
    {
        // In every 10n seconds, it updates the
        // cordination of galaxian so it can
        // create a delay
        if(timer >= 15)
        {
            x = home->get_x();
            timer = 0;
        }
      
        
        
        if(x > get_x())
            set_dx(MOVE_RIGHT);
        if(x < get_x())
            set_dx(MOVE_LEFT);
        if(abs(x - get_x()) <= 10)
            set_dx(0);

        if(y > get_y())
            set_dy(3);
        
        // int speed = rand() % 2 + 2;
        // set_dy(speed);

//.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:COMING BACK｡.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:✿
        if(get_y() >= H)
        {
            
            set_y(0);
            coming_back = true;
        }

        timer++;
        move();
    }
    else if(home != NULL && (!(home->is_alive())))
    {
        set_dy(3);
        move();
    }
}


void Alien::move_protect()
{
    if(mother != NULL && mother->is_alive())
    {
        int distance_x = (x0 - mother->x0);
        set_x(mother->get_x() + distance_x);
        
        int distance_y = (y0 - mother->y0);
        set_y(mother->get_y() + distance_y);
        attack = mother->attack;
    }
    move();
}


void Alien::condition(bool condt)
{
    attack =  condt;
}

bool Alien::attack_mode()
{
    return attack;
}
