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
    virtual int bonk()=0;
    void setStatus( bool status);
    virtual bool canGetBonked();
    virtual bool canFire();
    int getFiringDelay();
    void setFiringDelay(int x);
    virtual bool isProjectile();

    
    StudentWorld* getWorld();

    
private:
    bool m_status; // alive is true
    bool m_canBeDamaged;
    bool m_canShareSpace;
    int m_firing_delay;
    StudentWorld *m_world;
    
    
    
    
};

class Peach: public Actor
{
public:
    Peach(int startX ,int startY, StudentWorld *world);
    ~Peach();
     int bonk();
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
    //void bonk();
    //StudentWorld* getWorld();
    
    
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
    
   
    
    
    
};



class Pipe: public Actor
{
public:
    Pipe(int startX, int startY, StudentWorld* world, int imageID);
    ~Pipe();
    void doSomething();
    virtual int bonk();
    bool isStructure();
};

class Block: public Pipe
{
public:
    Block( int startX, int startY, bool contains_power, char power, StudentWorld* world);
    ~Block();
    void doSomething();
    int bonk();
    bool isStructure();
private:
    bool m_contains_Power;
    char m_power;
};

class Flag: public Actor
{
public:
    Flag( int startX, int startY, StudentWorld* world ,int imageId);
    virtual ~Flag();
    void doSomething();
    int bonk();
    bool isFlag();

    
};

class Mario:public Flag
{
public:
    Mario(int startX, int startY, StudentWorld* world);
    ~Mario();
    void doSomething();
    int bonk();
};

    
    // peach properties
    // hit points
    //

//Enemies
 class Enemy:public Actor
{
public:
    Enemy( int startX, int startY, StudentWorld* world, int imageID, int direction);
    ~Enemy();
    virtual void doSomething();
    virtual int bonk();
    
private:
    int m_direction;


};

class Goomba:public Enemy
{
public:
    Goomba( int startX, int startY, StudentWorld* world, int imageID, int direction);
    ~Goomba();
    void doSomething();
   
    //void bonk();
    
};

class Koopa:public Enemy
{
public:
    Koopa( int startX, int startY, StudentWorld* world, int imageID, int direction);
    ~Koopa();
    void doSomething();

    //void bonk();
    
};

class Piranha:public Enemy
{
public:
    Piranha(int startX, int startY, StudentWorld* world, int imageID, int direction);
    ~Piranha();
    void doSomething();
    int getFiringDelay();
    void setFiringDelay(int x);
    int bonk();
    bool canFire();
    
private:
    int m_firing_delay;
};


//PROJECTILES

class Projectiles:public Actor
{
public:
    Projectiles(int startX, int startY, StudentWorld* world, int imageID, int direction);
    ~Projectiles();
    void doSomething();
    virtual int bonk()= 0;
    bool isProjectile();
    
    
    
};

class PiranhaFireball:public Projectiles
{
public:
    PiranhaFireball(int startX, int startY, StudentWorld* world, int direction);
    ~PiranhaFireball();
   //void doSomething();
    virtual int bonk();
   
};





// keep track of attributes of each of these objects

// Each object must have the following base properties
// alive/dead status, damageable, whether something can move into its space

// doSomething function

#endif // ACTOR_H_
