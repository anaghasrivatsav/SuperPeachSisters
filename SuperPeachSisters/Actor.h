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
    
    StudentWorld* getWorld();

    
private:
    bool m_status; // alive is true
    bool m_canBeDamaged;
    bool m_canShareSpace;
    StudentWorld *m_world;
    
    
    
    
};

class Peach: public Actor
{
public:
    Peach(int startX ,int startY, StudentWorld *world);
    ~Peach();
    void bonk();
    void doSomething();
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

class Block: public Actor
{
public:
    Block( int startX, int startY, bool contains_power, char power, StudentWorld* world);
    ~Block();
    void doSomething();
    void bonk();
    bool isStructure();
private:
    bool m_contains_Power;
    char m_power;
};

class Pipe: public Actor
{
public:
    Pipe(int startX, int startY, StudentWorld* world);
    ~Pipe();
    void doSomething();
    void bonk();
    bool isStructure();
};

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
    ~Mario();
    void doSomething();
    void bonk();
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
    void doSomething();
    void bonk();


};

class Goomba:public Enemy
{
public:
    Goomba( int startX, int startY, StudentWorld* world, int imageID, int direction);
    ~Goomba();
    //void doSomething();
    //void bonk();
    
};

class Koopa:public Enemy
{
public:
    Koopa( int startX, int startY, StudentWorld* world, int imageID, int direction);
    ~Koopa();
    //void doSomething();
    //void bonk();
    
};


// keep track of attributes of each of these objects

// Each object must have the following base properties
// alive/dead status, damageable, whether something can move into its space

// doSomething function

#endif // ACTOR_H_
