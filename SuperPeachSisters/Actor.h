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
    //StudentWorld* getWorld();
    
    
private:
    int m_hitPts;
    bool m_invincible;
    bool m_flower;
    bool m_star;
    bool m_mushroom;
    int invincible_time;
    int time_to_recharge_before_next_fire;
   
    
    
    
};

class Block: public Actor
{
public:
    Block( int startX, int startY, bool contains_power, int power, StudentWorld* world);
    ~Block();
    void doSomething();
private:
    bool m_contains_Power;
    int m_power;
};

    
    // peach properties
    // hit points
    //

 


// keep track of attributes of each of these objects

// Each object must have the following base properties
// alive/dead status, damageable, whether something can move into its space

// doSomething function

#endif // ACTOR_H_
