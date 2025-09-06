#ifndef ALIEN_H
#define ALIEN_H

#include "Entity.h"
#include "Galaxian.h"

class Alien : public Entity
{
public:
    Alien(int i, int x, int y);
    //~Alien();
    virtual void run(bool LEFT, bool RIGHT, int displacement)
    {
        std::cout << "if this doesnt work imma kill you robert\n";
    }
    void condition(bool condt);
    bool attack_mode();


    /*   ♥･*:.｡ ｡.:*･ﾟ♡･*:.｡ ｡.:*･ﾟ♥  
               MOVEMENTS <3          
        ♥･*:.｡ ｡.:*･ﾟ♡･*:.｡ ｡.:*･ﾟ♥ */
    void move_curve(int displacement);
    void move_returning(int displacement);
    void move_together(bool LEFT, bool RIGHT);
    void move_follow();
    void move_protect();
    
    
    bool coming_back;
    const int x0, y0;
    bool attack;
    int point;
    Galaxian * home;
    Alien * mother;
    int timer;

    static Alien * MAX;
    static Alien * MIN;
    
private:
};

class FlagShip : public Alien
{ 
public:
    FlagShip(int x, int y)
        : Alien(1, x, y)
    {
        set_x(x);
        set_y(y);
        point = 60;
    }


    virtual void run(bool LEFT, bool RIGHT, int displacement)
    {
        if (!(attack_mode()))
            move_together(LEFT, RIGHT);
        else if(attack_mode() && !(coming_back))
            move_curve(displacement);
        else if(coming_back)
            move_returning(displacement);
       
    }
    
private:   
};

class RedAlien : public Alien
{
public:
    RedAlien(int x, int y)
        : Alien(2,x,y)
    {
        set_x(x);
        set_y(y);
        point = 50;
    }

    virtual void run(bool LEFT, bool RIGHT, int displacement)
    {
        if (mother->is_alive())
            move_protect();
        else if (!(attack_mode()))
            move_together(LEFT, RIGHT);
        else if(!(mother->is_alive()) && !coming_back)
            move_curve(displacement);
        else
            move_returning(displacement);
    }
    
private:
};

class AquaAlien : public Alien
{
public:
    AquaAlien(int x, int y)
        : Alien(3,x,y)
    {
        set_x(x);
        set_y(y);
        point = 40;
    }

    virtual void run(bool LEFT, bool RIGHT, int displacement)
    {
        if (!(attack_mode()))
              move_together(LEFT, RIGHT);
        else if(attack_mode() && !(coming_back))
            move_follow();
        else if(coming_back)
           move_returning(displacement);
    }
    
private:
};

class PurpleAlien : public Alien
{
public:
    PurpleAlien(int x, int y)
        : Alien(4, x, y)
    {
        set_x(x);
        set_y(y);
        point = 40;
    }

    virtual void run(bool LEFT, bool RIGHT, int displacement)
    {
        if (!(attack_mode()))
            move_together(LEFT, RIGHT);
        else if(attack_mode() && !(coming_back))
            move_curve(displacement);
        else if(coming_back)
            move_returning(displacement);
    }
    
private:
};


#endif
