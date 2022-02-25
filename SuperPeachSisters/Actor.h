#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject
{
public:
    
    Actor(  bool status, bool canBeDamaged, bool canShareSpace, int imageID, int startX ,int startY, int direction, int depth, double size,StudentWorld *world);
    virtual ~Actor();
    bool getStatus();
    bool damagable();
    bool shareSpace();
    virtual void doSomething()=0;
    virtual void bonk()=0;
    void setStatus( bool status);
    virtual bool canGetBonked();
    virtual bool canFire();
    virtual int getFiringDelay();
    virtual void setFiringDelay(int x);
    virtual bool isProjectile();
    void fall();
    bool isFalling();
    void setFalling(bool f);
    virtual bool createsShell();
    
    

    
    StudentWorld* getWorld();

    
private:
    bool m_status; // alive is true
    bool m_canBeDamaged;
    bool m_canShareSpace;
    int m_firing_delay;
    StudentWorld *m_world;
    bool m_falling;
    
    
    
    
};


//Enemies
 class Enemy:public Actor
{
public:
    Enemy( int startX, int startY, StudentWorld* world, int imageID, int direction);
    virtual~Enemy();
    virtual void doSomething();
    virtual void bonk();
    
private:
    int m_direction;


};

class Goomba:public Enemy
{
public:
    Goomba( int startX, int startY, StudentWorld* world, int imageID, int direction);
    virtual~Goomba();
    void doSomething();
   
    //void bonk();
    
};

class Koopa:public Enemy
{
public:
    Koopa( int startX, int startY, StudentWorld* world, int imageID, int direction);
    virtual~Koopa();
    void doSomething();
    bool createsShell();

    //void bonk();
    
};

class Piranha:public Enemy
{
public:
    Piranha(int startX, int startY, StudentWorld* world, int imageID, int direction);
    virtual~Piranha();
    void doSomething();
    int getFiringDelay();
    void setFiringDelay(int x);
    bool canFire();
    
private:
    int m_firing_delay;
};

//GOODIES
class Goodie:public Actor
{
public:
    Goodie(int startX, int startY, StudentWorld* world,  int imageID);
    virtual~Goodie();
    virtual void bonk()= 0;
    void doSomething();
    
};


class Mushroom: public Goodie
{
public:
    Mushroom(int startX, int startY, StudentWorld* world);
    virtual~Mushroom();
    void bonk();
};

class Flower: public Goodie
{
public:
    Flower(int startX, int startY, StudentWorld* world);
    virtual~Flower();
    void bonk();
};

class Star: public Goodie
{
public:
    Star( int startX, int startY, StudentWorld* world);
    virtual~Star();
    void bonk();
};


//Goals
class Flag: public Actor
{
public:
    Flag( int startX, int startY, StudentWorld* world ,int imageId);
    virtual ~Flag();
    void doSomething();
    void bonk();
    bool isFlag();
};

class Mario:public Flag
{
public:
    Mario(int startX, int startY, StudentWorld* world);
    virtual~Mario();
    void doSomething();
    void bonk();
};


//Structures
class Pipe: public Actor
{
public:
    Pipe(int startX, int startY, StudentWorld* world, int imageID);
    virtual~Pipe();
    void doSomething();
    virtual void bonk();
    bool isStructure();
    
};

class Block: public Pipe
{
public:
    Block( int startX, int startY, bool contains_power, char power, StudentWorld* world);
    virtual~Block();
    void doSomething();
    void bonk();
    bool isStructure();
private:
    bool m_contains_Power;
    char m_power;
};


//PROJECTILES

class Projectiles:public Actor
{
public:
    Projectiles(int startX, int startY, StudentWorld* world, int imageID, int direction);
    virtual~Projectiles();
    void doSomething();
    virtual void bonk()= 0;
    bool isProjectile();
    
};

class PiranhaFireball:public Projectiles
{
public:
    PiranhaFireball(int startX, int startY, StudentWorld* world, int direction);
    virtual~PiranhaFireball();
   void doSomething();
    virtual void bonk();
   
};

class KoopaShell: public Projectiles
{
public:
    KoopaShell(int startX, int startY, StudentWorld* world, int direction);
    virtual~KoopaShell();
    void doSomething();
    virtual void bonk();
};

class PeachFireball: public Projectiles
{
public:
    PeachFireball(int startX, int startY, StudentWorld* world, int direction);
    virtual~PeachFireball();
    void doSomething();
    virtual void bonk();
};




class Peach: public Actor
{
public:
    Peach(int startX ,int startY, StudentWorld *world);
    ~Peach();
     void bonk();
    void doSomething();
    bool isInvincible();
    bool hasStarPower();
    bool hasMushroomPower();
    bool hasFlowerPower();
    void setMushroomPower(bool f);
    void setFlowerPower(bool f);
    void setStarPower(bool f);
    void setInvincible(bool f);
    void addHitPts( int ht);
    int getHitPts();
    bool canFire();
    void damagePeach();
    void setInvincibleTime(int n);
    int getStarTime( );
    void setFiringDelay(int x);
    int getFiringDelay();
    bool isProjectile();
    bool finishedLevel();
    void setFinishedLevel(bool b);
    
    
private:
    int m_hitPts;
    bool m_invincible;
    bool m_flower;
    bool m_star;
    bool m_mushroom;
    int invincible_time;
    int time_to_recharge_before_next_fire;
    bool m_jumping;
    bool m_falling;
    int remaining_jump_distance;
    int remaining_star_time;
    bool m_finished;
};


#endif // ACTOR_H_
