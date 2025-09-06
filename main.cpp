/****************************************************************************
 Yihsiang Liow
 Copyright

ʚ ═══･୨ ꕤ ୧･═══ ɞ
 ELIF NALAN MUTLU
 CISS245      P01
ʚ ═══･୨ ꕤ ୧･═══ ɞ

ALL THE DESIGN/FONT/SOUND REFERENCES
ARE PROVIDED AT THE REFERENCE DIRECTORY
****************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Sound.h"

// 。+❤ฺ·。❤ฺ·。+❤ฺ· +❤·。❤ฺ·。+❤ฺ·
// CLASSES THAT IMPLEMENTED BY ME
// 。+❤ฺ·。❤ฺ·。+❤ฺ· +❤·。❤ฺ·。+❤ฺ·
#include "Stars.h"
#include "Galaxian.h"
#include "Laser.h"
#include "Alien.h"
#include "Explosion.h"
#include "Decoration.h"

// ʚ ═══･୨ ꕤ ୧･═══ ɞ
// GLOBAL VARABLES
// ʚ ═══･୨ ꕤ ୧･═══ ɞ

int displacement = 0;
int milisec = 0;
bool welcome = true;

bool game_play = false;
bool game_ended = false;
bool wave = false;
bool quit = false;

bool drop = false;

int MAX_X;
int MIN_X;
int points = 0;

static Sound * sounds[3] = {new Sound("sounds/laser.wav"),
                            new Sound("sounds/explosion.wav"),
                            new Sound("sounds/game_over_sound.wav")};



//PROTOTYPES
void set_aliens(std::vector<Alien *> & aliens, Galaxian & galaxian);
void shooting_input(std::vector<Laser *> & Lasers, const Galaxian & galaxian, KeyPressed & keypressed, bool & space_pressed);
void draw_lasers(std::vector <Laser *> Lasers,Surface & surface);
void aliens_shooting(std::vector <Laser *>  & Lasers, Alien aliens);
void check_collision(std::vector <Laser *>  & Lasers, std::vector<Alien *> aliens);
void check_bump(Galaxian & galaxian, std::vector<Alien *> & aliens, std::vector < Explosion *> & explosions, int & lives);
void galaxian_die( std::vector <Laser *> & Lasers, Galaxian & galaxian, int & lives, std::vector < Explosion *> & explosions);
void game_over(Surface & surface);
void restart(std::vector<Laser *> & Lasers,  std::vector<Explosion *> & explosions, std::vector <Alien *> & aliens, Galaxian & galaxian, int & lives);
void print_points(char s[], Surface & surface);
void point_converter(Surface & surface);
void check_lives(Galaxian & galaxian, int lives, Surface & surface);
void MAX_MIN_computation(std::vector <Alien *> & aliens);
void run_aliens(std::vector<Alien *> & aliens, bool drop, int & MAX_X, int & MIN_X, int & displacement, std::vector < Laser * > & Lasers);
void draw_aliens(std::vector<Alien *> &  aliens, Surface & surface);
void aliens_collide(std::vector<Alien *> & aliens, std::vector<Explosion *> & explosions );
void new_wave(Surface & surface,std::vector<Laser *> & Lasers,  std::vector<Explosion *> & explosions,
              std::vector <Alien *> & aliens, Galaxian & galaxian);
int dead_alien_count(std::vector < Alien * > aliens);
void check_new_wave(std::vector <Alien * > & aliens, int & dead_aliens);
void draw_lives(Surface & surface, int lives);
void print_name(Surface & surface);
void welcome_screen(Surface & surface, std::vector <Decoration *> & decorations);
void draw_explosions(std::vector <Explosion *> & explosions, Surface & surface);


void welcome_screen(Surface & surface, std::vector <Decoration *> & decorations)
{
    Font font("fonts/PixelWriting.ttf", 100);
    Color c = {125,18,255};
    Image image(font.render("GALAXIAN", c));
    Rect rect = image.getRect();
    rect.x = 125;
    rect.y = 125;
    surface.put_image(image, rect);

    for(int i = 0; i < int(decorations.size()); ++i)
    {
        decorations[i] =  new Decoration(i);
    }

    for(int i = 0; i < int(decorations.size()); ++i)
    {
        decorations[i]->draw(surface);
    }

    Font font1("fonts/PixelWriting.ttf", 50);
    Color c1 = {238,130,238};
    Image image1(font1.render("Press p to play", c1));
    Rect rect1 = image1.getRect();
    rect1.x = 175;
    rect1.y = 400;
    surface.put_image(image1, rect1);
    
    
    print_name(surface);

//         .•°*”˜ƸӜƷ˜”*°•.•.
//    delocating memory for decorations  

    for(int i = 0; i < int(decorations.size()); ++i)
    {
        delete decorations[i];
    }   
}




void shooting_input(std::vector<Laser *> & Lasers, const Galaxian & galaxian,
                    KeyPressed & keypressed, bool & space_pressed)
{
    if(keypressed[SPACE] && !space_pressed && galaxian.is_alive())
    {
        int lasers_length = int(Lasers.size()) + 1;
        Lasers.resize(lasers_length);
        Lasers[lasers_length - 1] = new Laser(true, galaxian.get_x() + galaxian.get_w()/2, galaxian.get_y());
        // sounds laser
        sounds[0]->play();
        space_pressed = true;
    }
    if(!keypressed[SPACE])
        space_pressed = false;
}

void draw_lasers(std::vector <Laser *> Lasers,Surface & surface)
{
    for(int i = 0; i < int(Lasers.size()); ++i)
    {
        if(Lasers[i]->is_alive())
        {
            Lasers[i]->move();
            Lasers[i]->draw(surface);
        }
    }
    
}

void aliens_shooting(std::vector <Laser *>  & Lasers, Alien aliens)
{
    static int time = 0;
    int rand_time = rand() % 60 + 65;
    if(aliens.is_alive() && aliens.attack_mode())
    {
        if (time >= rand_time)
        {
            time = 0;
            int length = int(Lasers.size() + 1);
            Lasers.resize(length);

            Lasers[length - 1] = new Laser(false, aliens.get_x() + aliens.get_w()/2, aliens.get_y());

            //sound laser
            sounds[0]->play();
        }
    }
    time++;
    
}


void check_collision(std::vector <Laser *>  & Lasers, std::vector<Alien *> aliens)
{
    for(int j = 0; j < int(aliens.size()); ++j)
    {
        for(int i  = 0; i < int(Lasers.size()); ++i)
        {
            if(Lasers[i]->is_alive() && aliens[j]->is_alive() && !(Lasers[i]->is_enemy()))
            {
                aliens[j]->die(*(Lasers[i]));
                if(aliens[j]->is_colliding(*(Lasers[i])))
                {
                    points += aliens[j]->point;
                    sounds[1]->play();
                }
            }
        }
    }
}

void check_bump(Galaxian & galaxian, std::vector<Alien *> & aliens, std::vector < Explosion *> & explosions, int & lives)
{
    for(int j = 0; j < int(aliens.size()); ++j)
    {
        if(galaxian.is_alive() && aliens[j]->is_alive())
        {
            aliens[j]->die(galaxian);
            if (galaxian.is_collide)
            {
                lives--;
                explosions.resize(int(explosions.size()) + 1);
                explosions[int(explosions.size()) - 1] = new Explosion(galaxian);
                galaxian.is_collide = false;
                sounds[1]->play();
            }
        }
        
    }
}

void print_points(char s[], Surface & surface)
{
    Font font("fonts/Buycat.ttf", 20);
    Color c = {171,32,253};
    Image image(font.render(s, c));
    Rect rect = image.getRect();
    rect.x = 5;
    rect.y = 20;
    surface.put_image(image, rect);

    Image image1(font.render("SCORE", c));
    Rect rect1 = image.getRect();
    rect1.x = 5;
    rect1.y = 5;
    surface.put_image(image1, rect1);
    
}


void point_converter(Surface & surface)
{
    char s[10];
    int x = points;
    int digits = 0;
    while( x != 0 )
    {
        x /= 10;
        digits++;
    }
    if(points == 0)
        digits = 1;
    
    for(int i = 0; i < digits ; ++i)
    {
        s[i] = points / int(pow(10, digits - 1 - i)) % 10+ '0';
    }
    
    
    s[digits] = '\0';
    print_points(s, surface);
}


void galaxian_die( std::vector <Laser *> & Lasers,
                   Galaxian & galaxian, int & lives, std::vector < Explosion *> & explosions)
{
    for(int i = 0 ; i <  int(Lasers.size()); ++i)
    {
        if(Lasers[i]->is_alive() && galaxian.is_alive() && Lasers[i]->is_enemy())
        {
            galaxian.die(*Lasers[i]);
            if (galaxian.is_collide)
            {
                lives--;
                explosions.resize(int(explosions.size()) + 1);
                explosions[int(explosions.size()) - 1] = new Explosion(galaxian);
                galaxian.is_collide = false;
                sounds[1]->play();
            }
            
        }
    }
}


void game_over(Surface & surface)
{
    if(game_ended)
    {
    Font font("fonts/BleedingPixels.ttf", 50 );
    Color c = {220,20,60};
    Image image(font.render("GAME OVER", c));
    Rect rect = image.getRect();
    rect.x = 155;
    rect.y = 200;
    surface.put_image(image, rect);
    }
}

void restart(std::vector<Laser *> & Lasers,  std::vector<Explosion *> & explosions, std::vector <Alien *> & aliens, Galaxian & galaxian, int & lives)
{
   for(int i  = 0; i < int(Lasers.size()); ++i)
    {
        delete Lasers[i];
    }
   
    for (int i = 0; i < int(explosions.size()); ++i)
    {
        delete explosions[i];
    }
    
    for(int i = 0; i < int(aliens.size()); ++i)
    {
        delete aliens[i];
    }
    
    lives = 3;
    galaxian.revive();
    Lasers.resize(0);
    explosions.resize(0);
    displacement = 0;
    set_aliens(aliens, galaxian);
}


void check_lives(Galaxian & galaxian, int lives, Surface & surface)
{
    static int time = 0;
    if(lives > 0 && !(galaxian.is_alive()))
    {
        if(time == 60)
        {
            galaxian.revive();
            galaxian.set_x(W/2);
            galaxian.set_y(H - 32);
            time = 0;
        }
        time++;
    }
    else if(lives == 0)
    {
        game_ended = true;
        game_play = false;
    }
}

void set_aliens(std::vector<Alien *> & aliens, Galaxian & galaxian)
{
    int flag = 256, red = 224, purple = 192, aqua = 160;
    for(int i = 0; i < int(aliens.size()); ++i)
    {
        if(i < 2)
            aliens[i] = new FlagShip(flag + 96 * i, 75);

        else if(i < 5)
        {
            aliens[i] =  new RedAlien(red + 32 * (i - 2), 107);
            aliens[i]->mother = aliens[0];
        }            
        else if(i <= 7)
        {
            aliens[i] =  new RedAlien(red + 32 * (i - 2), 107);
            aliens[i]->mother = aliens[1];
        }
        else if(i < 16)
            aliens[i] = new PurpleAlien(purple + 32 * (i - 8), 139);
     
        else if(i < 26)
        {
            aliens[i] = new AquaAlien(aqua + 32 * (i - 16) ,171);
            aliens[i]->home = &galaxian;
        }
        else if(i < 36)
        {
            aliens[i] = new AquaAlien(aqua + 32 * (i - 26) ,203);
            aliens[i]->home = &galaxian;
        }
        else
        {
            aliens[i] = new AquaAlien(aqua + 32 * (i - 36) ,235);
            aliens[i]->home = &galaxian;
        }

    }

    Alien::MAX = aliens[45];
    Alien::MIN = aliens[36];
    MAX_X = Alien::MAX->get_x();
    MIN_X = Alien::MIN->get_x();
}



//✧ ‧˚₊ ❆ ‧ ₊ ⊹˚✧ ‧˚₊ ❆ ‧ MAKING ALIENS GO MAX-MIN USING POINTERS  ₊ ⊹˚✧ ‧˚₊ ❆ ‧ ₊ ⊹˚✧ ‧˚₊ ❆ ‧ ₊ ⊹˚
void MAX_MIN_computation(std::vector <Alien *> & aliens)
{
    if(!(Alien::MAX->is_alive()))
    {
        Alien::MAX = NULL;
        
        for(int i = 0; i < aliens.size(); ++i)
        {
            if(aliens[i]->is_alive())
            {
                if(Alien::MAX == NULL)
                    Alien::MAX = aliens[i];
                else if(aliens[i]->x0 > Alien::MAX->x0)
                {
                    Alien::MAX = aliens[i];
                    MAX_X = Alien::MAX->x0 + displacement;
                }
            }
        }
    }


    if(!(Alien::MIN->is_alive()))
    {
        Alien::MIN = NULL;
        
        for(int i = 0; i < aliens.size(); ++i)
        {
            if(aliens[i]->is_alive())
            {
                if(Alien::MIN == NULL)
                    Alien::MIN = aliens[i];
                else if(aliens[i]->x0 < Alien::MIN->x0)
                {
                    Alien::MIN = aliens[i];
                    MIN_X = Alien::MIN->x0 + displacement;
                }
            }
        }
    }
}



void run_aliens(std::vector<Alien *> & aliens, bool drop, int & MAX_X, int & MIN_X, int & displacement, std::vector < Laser * > & Lasers)
{
    static bool LEFT = false;
    static bool RIGHT = true;
   
    if(drop)
    {
        int k;
        while(1)
        {
            k = rand() % 46;
            if(aliens[k]->is_alive()) break;
        }
        
        if(!(aliens[k]->attack_mode()) && aliens[k]->is_alive())
            aliens[k]->condition(true);
    }


    
    if(MAX_X  >= W - 32)
    {
        LEFT = true;
        RIGHT = false;
    }
    else if(MIN_X <= 0)
    {
        LEFT = false;
        RIGHT = true;
    }
    if (LEFT)
    {
        MAX_X += MOVE_LEFT;
        MIN_X += MOVE_LEFT;
        displacement += MOVE_LEFT;
    }
    else
    {
        MIN_X += MOVE_RIGHT;
        MAX_X += MOVE_RIGHT;
        displacement += MOVE_RIGHT;
    }
        
    for(int i = 0; i < int(aliens.size()); ++i)
    {
        aliens[i]->run(LEFT, RIGHT, displacement);
        if(aliens[i]->attack_mode())
        aliens_shooting(Lasers, *(aliens[i]));
       
    }
    
    
}

void draw_aliens(std::vector<Alien *> &  aliens, Surface & surface)
{
    for(int i = 0; i < int(aliens.size()); ++i)
    {
        if(aliens[i]->is_alive())
        {
            aliens[i]->draw(surface);
        }
    }
}

void aliens_collide(std::vector<Alien *> & aliens, std::vector<Explosion *> & explosions )
{
    for(int i = 0; i < int(aliens.size()); ++i)
    {
        if (aliens[i]->is_collide)
        {
            explosions.resize(int(explosions.size()) + 1);
            explosions[int(explosions.size()) - 1] = new Explosion(*(aliens[i]));
            aliens[i]->is_collide = false;
        }
    }
}


void new_wave(Surface & surface,std::vector<Laser *> & Lasers,  std::vector<Explosion *> & explosions,
                    std::vector <Alien *> & aliens, Galaxian & galaxian)
{
    static int time = 0;
    
    if(time <= 120)
    {
        Font font("fonts/JingleStar.ttf", 60);
        Color c = {240,0,255};
        Image image(font.render("NEW WAVE", c));
        Rect rect = image.getRect();
        rect.x = 130;
        rect.y = 200;
        surface.put_image(image, rect);
    }
    else
    {
        wave = false;
        game_play = true;
        
        for(int i  = 0; i < int(Lasers.size()); ++i)
        {
            delete Lasers[i];
        }
        
        for (int i = 0; i < int(explosions.size()); ++i)
        {
            delete explosions[i];
        }
        
        for(int i = 0; i < int(aliens.size()); ++i)
        {
            delete aliens[i];
        }

        
        galaxian.set_x(W/2);
        Lasers.resize(0);
        explosions.resize(0);
        displacement = 0;
        set_aliens(aliens, galaxian);
    }
    time++;
}

void draw_explosions(std::vector <Explosion *> & explosions, Surface & surface)
{
    
    for (int i = 0; i < int(explosions.size()); i++)
    {
        explosions[i]->explode(surface);
    }
}

int dead_alien_count(std::vector < Alien * > aliens)
{
    int dead = 0;
    for(int i = 0; i < int(aliens.size()) ; ++i)
    {
        if(!(aliens[i]->is_alive()))
        {
            dead++;
        }
    }
    return dead;
}


void check_new_wave(std::vector <Alien * > & aliens, int & dead_aliens)
{
    
    if(dead_alien_count(aliens) == 46)
    {
        game_play = false;
        wave = true;
        for(int i = 0; i < int(aliens.size()); ++i)
        {
            aliens[i]->revive();
        }
    }
}

void draw_lives(Surface & surface, int lives)
{
    static Image live =  "images/galaxian/Heart.png";
    for(int i = 0; i < lives; ++i)
    {
        Rect rect = live.getRect();
        rect.x = W - 32 * (i + 1);
        rect.y = 0;
        surface.put_image(live, rect);
    }
}


void print_name(Surface & surface)
{
    Font font("fonts/Buycat.ttf", 36);
    Color c = {255,0,180};
    Image image(font.render("Elif Nalan Mutlu", c));
    Rect rect = image.getRect();
    rect.x = 170;
    rect.y = 265;
    surface.put_image(image, rect);
    
}



int main(int argc, char* argv[])
{
    int RATE = 1000 / 60;
    Surface surface(W, H);
    Event event;
    Stars stars[100];
    Music music("sounds/bckgr.ogg");
    music.play();
    
/*ஐ〰ฺ·:*:·✿ ஐ〰ฺ·:*:·✿ 
   Main Objects        *
ஐ〰ฺ·:*:·✿ ஐ〰ฺ·:*:·✿ */
    Galaxian galaxian;
    std::vector<Laser *> Lasers;
    bool space_pressed = false;
    std::vector<Explosion *> explosions;
    std::vector<Alien *> aliens(46);
    std::vector<Decoration *> decorations(8);
    
    set_aliens(aliens, galaxian);
    
    int lives = 3;
    int dead_aliens = 0;
    int sec = 0;
    
    while(1)
    {
        int START = getTicks();
        if (event.poll() && event.type() == QUIT) break;
        KeyPressed keypressed = get_keypressed();

        if (game_play){
            MAX_MIN_computation(aliens);
            galaxian.get_input(keypressed);
            shooting_input(Lasers,galaxian, keypressed, space_pressed);
        }
        surface.lock();
        surface.fill(BLACK);
        
        
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // hello guys welcome back to my chanel.   *
        // Today we are making this galaxian       *
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        move_stars(stars, 100 ,surface);

//ฺ·。❤ฺ·。+❤ฺ·。❤ฺ·GAME STARTS WITH WELCOME MODE 。+❤ฺ·。❤ฺ·。+❤ฺ·。❤ฺ·。+❤ฺ·。❤ฺ·。+❤ฺ·。❤ฺ·
        if (welcome) 
        {
            welcome_screen(surface, decorations);
            if(keypressed[SDLK_p])
            {
                welcome = false;
                game_play = true;
                sec = 0;
                milisec = 0;
            }
            else if(keypressed[SDLK_x])
            {
                break;
            }
        }
        else if (game_play && !(game_ended) && !(wave))
        {
            
            point_converter(surface);
            draw_lives(surface, lives);
            run_aliens(aliens, drop, MAX_X, MIN_X, displacement, Lasers);
            if (sec == 0)
            {
                drop = false;
            }
            if (milisec % 60 == 0)
                sec++;
            
            if(sec == 2)
            {
                sec = 0;
                drop = true;
            }

 //。+❤ฺ·。❤ฺ·。+❤ฺ·。DRAWING FUNCTIONS·。+❤ฺ·。❤ฺ·。+❤ฺ·。❤ฺ·
            galaxian.draw(surface);
            draw_aliens(aliens, surface);
            draw_lasers(Lasers, surface);
            draw_explosions(explosions, surface);
            
            check_lives(galaxian,lives, surface);

// ♥･*:.｡ ｡.:*･ﾟ♡interraction between objects♥･*:.｡ ｡.:*･ﾟ♡
            check_collision(Lasers, aliens);
            check_bump(galaxian, aliens, explosions, lives);
            
            galaxian_die(Lasers, galaxian, lives, explosions);
            aliens_collide(aliens, explosions);
    
            check_new_wave(aliens,dead_aliens);
            
        }

        else if(wave)
        {
            new_wave(surface,Lasers, explosions, aliens, galaxian);
        }

        else if(game_ended)
        {
            game_over(surface);
            KeyPressed keypressed1 = get_keypressed();
            static int sound = 0;
            if(sound <= 15)
                sounds[2]->play();
            sound++;
            if(keypressed1[SDLK_p])
            {
                restart(Lasers, explosions, aliens, galaxian, lives);
                game_ended = false;
                game_play = false;
                welcome = true;
            }
            
        }
      
        surface.unlock();
        surface.flip();
        int END = getTicks();
        int dt = RATE - (START - END);
        milisec++;
       
        if (dt > 0) delay(dt);
    }



//｡.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:✿｡.
// DELOCAIONS     
// ｡.ﾟ+:✿｡.ﾟ+:✿｡.ﾟ+:✿
    
    for(int i  = 0; i < int(Lasers.size()); ++i)
    {
        delete Lasers[i];
    }

    int explosion_length = int(explosions.size());
    for (int i = 0; i < explosion_length; ++i)
    {
        delete explosions[i];
    }
    
    for(int i = 0; i < int(aliens.size()); ++i)
    {
        delete aliens[i];
    }

   
	return 0;
}
