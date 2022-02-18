#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*   Actor( bool status, bool canDamage, bool canShareSpace);
 virtual ~Actor();
 bool getStatus();
 bool damagable();
 bool shareSpace();
 virtual void doSomething()=0;
 virtual void bonk()=0;
 
private:
 bool m_status; // alive is true
 bool m_canDamage;*/


//ACTOR CLASS
Actor::Actor( bool status, bool canBeDamaged, bool canShareSpace, int imageID, int startX ,int startY, int direction, int depth, double size, StudentWorld* world): GraphObject( imageID,  startX,  startY, direction, depth, size)
{
    m_status= status;
    m_canBeDamaged= canBeDamaged;
    m_canShareSpace= canShareSpace;
    m_world= world;
    
}
Actor::~Actor()
{
    
}

bool Actor::canGetBonked()
{
    return true; 
}
bool  Actor::getStatus()
{
    return m_status;
}

bool Actor::damagable()
{
    return m_canBeDamaged;
}
bool Actor::shareSpace()
{
    return m_canShareSpace;
}

void Actor::setStatus(bool status)
{
    m_status= status;
}



StudentWorld* Actor::getWorld( )
{
    return m_world;
}





//ENEMY CLASS
Enemy::Enemy(int startX, int startY, StudentWorld* world, int imageID, int direction): Actor(true, true, true, imageID, startX, startY, direction, 0,1 , world)
{
    m_direction= direction;
}

Enemy::~Enemy()
{
    
}

void Enemy::doSomething()
{
    if(m_direction==0)
    {
        if( getWorld()->isIntersectingSolid(getX()+1, getY()))
        {
            m_direction = 180;
            setDirection(180);
        }
        else if( !getWorld()->isIntersectingSolid(getX()+SPRITE_WIDTH, getY()-1))
        {
            m_direction= 180;
            setDirection(180);
            
        }
        else
        {
            moveTo(getX()+1, getY());
        }
    }
    else if( m_direction == 180)
        {
            if( getWorld()->isIntersectingSolid(getX()-1, getY()))
            {
                m_direction = 0;
                setDirection(0);
            }
            else if( !getWorld()->isIntersectingSolid(getX()-SPRITE_WIDTH, getY()-1))
            {
                m_direction= 0;
                setDirection(0);
                
            }
            else
            {
                moveTo(getX()-1, getY());
            }
            
        }
                
   
    
}

void Enemy::bonk()
{
    
    
}


Goomba::Goomba( int startX, int startY, StudentWorld* world, int imageID, int direction): Enemy(  startX, startY, world, imageID, direction)
{
    
}

Goomba::~Goomba()
{
    
}

void Goomba::doSomething()
{

    Enemy::doSomething();
    //std::cerr<< "DOES SOMETHING"<< std::endl;
}


Koopa::Koopa( int startX, int startY, StudentWorld* world, int imageID, int direction): Enemy(  startX, startY, world, imageID, direction)
{
    
}

Koopa::~Koopa()
{
    
}






//FLAG CLASS
Flag::Flag( int startX, int startY, StudentWorld* world ,int imageID):Actor(true,false, true, imageID, startX, startY, 0,1,1, world)
{
    
}



Flag::~Flag()
{
    
}
void Flag::doSomething()
{
    
}

void Flag::bonk()
{
    if(getStatus())
    {
        getWorld()->increaseScore(1000);
        setStatus(false);
       
    }
    std::cerr << getWorld()->getScore() << std::endl;
   
}

Mario::Mario(int startX, int startY, StudentWorld* world):Flag(startX, startY, world, IID_MARIO)
{
    
}
Mario::~Mario()
{
    
}

void Mario::bonk()
{
    if(getStatus())
    {
        getWorld()->increaseScore(1000);
        setStatus(false);
       
    }
}
void Mario::doSomething()
{
    
}




//STRUCTURES
Pipe::Pipe(int startX, int startY, StudentWorld* world):Actor(true, false, false, IID_PIPE, startX, startY,0,2,1.0, world )
{
    
}

Pipe::~Pipe()
{
    
}

void Pipe::doSomething()
{
    
}

void Pipe::bonk()
{
    
}




Block::Block( int startX, int startY, bool contains_power, char power, StudentWorld* world): Actor(true, false, false, IID_BLOCK,  startX, startY, 0,2,1.0, world)
{
    m_contains_Power= contains_power;
    m_power= power;
}

Block::~Block()
{
    
}


void Block::doSomething()
{
    
}

void Block::bonk()
{
    
}
    


//PEACH
Peach::Peach( int startX, int startY, StudentWorld* world): Actor(true, true, true, IID_PEACH,  startX, startY, 0,0,1.0, world)
{
    
    m_hitPts= 1;
    /*m_powers[0]= 0;
    m_powers[1]= 0;
    m_powers[2]= 0;*/
    
    m_flower= false;
    m_mushroom= false;
    m_star= false;
    m_invincible= false;
    time_to_recharge_before_next_fire= 0;
    m_jumping= false;
    remaining_jump_distance= 8;
    m_falling= false;
    
    
    
}

Peach::~Peach()
{
    //delete [] m_powers;
}
void Peach::bonk()
{
    
}

 


void Peach::doSomething()
{
    if(!getStatus())
    {
        return;
    }
    
    if( m_invincible)
    {
        invincible_time--;
        if( invincible_time <= 0)
        {
            m_invincible= false;
        }
    }
    
    
    if(m_jumping&& remaining_jump_distance >0)
    {
      if(getWorld()->isIntersectingSolid(getX(), getY()+4))
      {
          int jumpUp= 0;
          while(!getWorld()->isIntersectingSolid(getX(), getY()+jumpUp))
          {
              jumpUp++;
          }
          moveTo(getX(), getY()+jumpUp);
          getWorld()->playSound(SOUND_PLAYER_BONK);
          remaining_jump_distance= 0;
      }
        else if( m_jumping)
        {
            moveTo(getX(), getY()+4);
            remaining_jump_distance --;
        }
        if( remaining_jump_distance==0)
        {
            m_falling= true;
            m_jumping = false;
        }
    }
    
    if( m_falling)
    {
        if(getWorld()->isIntersectingSolid(getX(), getY()-3) )
        {
            int fallDown= 0;
            while(!getWorld()->isIntersectingSolid(getX(), getY()-fallDown))
            {
                fallDown++;
            }
            moveTo(getX(), getY()- fallDown+1);
            m_falling = false;
        }
        else{
            moveTo(getX(), getY()- 4);
            
        }
    }
    
     int ch;
     if (getWorld()->getKey(ch))
     {
     // user hit a key during this tick!
     switch (ch)
     {
     case KEY_PRESS_LEFT:
             setDirection(180);
             if(getWorld()->isIntersectingSolid(getX() -4, getY()))
             {
                 (*getWorld()).playSound(SOUND_PLAYER_BONK);
                 break;
                 
             }
             if( !getWorld()->isIntersectingSolid(getX() -4, getY()-1)&&!m_jumping)
             {
                 m_falling = true;
             }
                moveTo(getX() -4, getY());
             break;
     case KEY_PRESS_RIGHT:
             setDirection(0);
             if(getWorld()->isIntersectingSolid(getX() +4, getY()))
             {
                 (*getWorld()).playSound(SOUND_PLAYER_BONK);
                 break;
                 
             }
             if( !getWorld()->isIntersectingSolid(getX() +4, getY()-1)&&!m_jumping)
             {
                 m_falling = true;
             }
                moveTo(getX() +4, getY());
             break;
             break;
    case KEY_PRESS_UP:
             
             /*if(getWorld()->isIntersectingSolid(getX() , getY()+4))
             {
                 (*getWorld()).playSound(SOUND_PLAYER_BONK);
                break;
             }
             moveTo(getX(), getY()+4);
              */
             if( getWorld()->isIntersectingSolid(getX() , getY()-1))
             {
                 m_jumping = true;
                 if(m_mushroom)
                 {
                     remaining_jump_distance= 12;
                 }
                 else{
                     remaining_jump_distance= 12;
                 }
                 getWorld()->playSound(SOUND_PLAYER_JUMP);
             }
            
             
             break;
   /* case KEY_PRESS_DOWN:
             if(getWorld()->isIntersectingSolid(getX() , getY()-4))
             {
                break;
             }
             moveTo(getX(), getY()-4);
             break;*/
             
    
             
             
     }
         
         getWorld()->peachBonk(getX(), getY());
     }
    
    /*
    Peach must check to see if she is currently alive. If not, then Peach’s
    doSomething() method must return immediately – none of the following steps
    should be performed.
    2. Peach must check if she is currently invincible (Star Power), and if so, decrement
    the number of remaining game ticks before she loses this invincibility power. If
    this tick count reaches zero, Peach must set her invincibility status to off.
    3. Peach must check if she is currently temporarily invincible, and if so, decrement
    the number of remaining game ticks before she loses temporary invincibility. If
    this tick count reaches zero, Peach must set her temporary invincibility status to
    false. (Peach gains temporary invincibility if she overlaps with an enemy while
    she has Jump Power or Fire Power.)
    4. Peach must check if she is currently in “recharge” mode before she can fire again.
    If the number of time_to_recharge_before_next_fire ticks is greater than zero, she
    must decrement this tick count by one. If the tick count reaches zero, then Peach
    may again shoot a fireball (if she has Shoot Power).
    
    
    */
    
    
    
    
    /*
    if( !getStatus())
    {
        return;
    }
    if( m_invincible)
    {
        invincible_time--;
        if( invincible_time== 0)
        {
            m_invincible= false;
            m_powers[2]= 0;
        }
    }
    
     */
    
    
    
    
    
    
}

/*
 For the purposes of this project, to determine if two objects A and B overlap, simply
 check to see if their bounding squares overlap. Each object in the game (e.g., a block,
 koopa, Peach, goodies, pipes, fireballs) is represented by a rectangle that is
 SPRITE_WIDTH pixels wide and SPRITE_HEIGHT pixels high. Each object's location
 is denoted by the coordinates of the bottom-left corner of that rectangle. So if an object is
 at location (x,y), it will extend to (x+SPRITE_WIDTH−1, y+SPRITE_HEIGHT−1). It is
 therefore a pretty trivial problem to check if two boxes have any overlap with a few if
 statements. These constants are defined in GameConstants.h.
 */
/*
1. Peach must check to see if she is currently alive. If not, then Peach’s
doSomething() method must return immediately – none of the following steps
should be performed.
2. Peach must check if she is currently invincible (Star Power), and if so, decrement
the number of remaining game ticks before she loses this invincibility power. If
this tick count reaches zero, Peach must set her invincibility status to off.
3. Peach must check if she is currently temporarily invincible, and if so, decrement
the number of remaining game ticks before she loses temporary invincibility. If
this tick count reaches zero, Peach must set her temporary invincibility status to
false. (Peach gains temporary invincibility if she overlaps with an enemy while
she has Jump Power or Fire Power.)
4. Peach must check if she is currently in “recharge” mode before she can fire again.
If the number of time_to_recharge_before_next_fire ticks is greater than zero, she
must decrement this tick count by one. If the tick count reaches zero, then Peach
may again shoot a fireball (if she has Shoot Power)
5. Peach must check to see if she currently overlaps with any other game object1
(e.g., an enemy, a fireball, a flag, etc.) and if so, she must “bonk” the other object.
What happens when you bonk another object? It depends on what’s being bonked;
each class should have its own unique bonk() method that reacts appropriately.
6. If Peach had previously initiated a jump and her remaining_jump_distance is > 0,
then she will try to move upward by four pixels during the current tick:
a. Peach will calculate her target x,y position first (in this case, four pixels
greater than her current y position)
b. Peach will check to see if there is an object that blocks movement at this
destination position (before moving there). If so:
i. Peach will bonk the target object that is blocking her way (e.g.,
cause a bonk() method in the target object to be called)
ii. Peach will abort trying to move to the destination square since it is
blocked
iii. Peach will update her remaining_jump_distance to zero such that
the jump will be aborted and she will no longer try to move
upward on the next tick.
c. Otherwise if there is not a blocking object above Peach:
i. Peach will use the moveTo() function from GraphObject to update
her location 4 pixels upward.
ii. Peach must decrement her remaining_jump_distance by 1 to
indicate that she is now one step closer to reaching the top of her
jump.
7. Otherwise, if Peach was not actively jumping during the current tick, then she
must check to see if she is falling:
a. Peach must check if there is an object that blocks movement between 0
and 3 (inclusive) pixels directly below her.
b. If not, then Peach must update her y position by -4 pixels (so she is falling
downward) using GraphObject’s moveTo() function.
8. Next, Peach must check to see if the player pressed a keystroke using the
getKey() function.
9. If the user pressed a key:
a. If the pressed key was KEY_PRESS_LEFT then Peach must:
i. Set her direction to 180 degrees
ii. Peach will calculate a target x,y position first (4 pixels less than
her current x position)
iii. Peach will check to see if there is an object that blocks movement
at this destination position (before moving there). If so:
1. Peach will bonk the target object that is blocking her way
(e.g., cause a bonk() method in the target object to be
called)
2. Peach will abort trying to move to the destination square
since it is blocked
iv. Otherwise, Peach will update her location 4 pixels leftward.
b. If the pressed key was KEY_PRESS_RIGHT then Peach must:
i. Set her direction to 0 degrees
ii. Peach will calculate a target x,y position first (4 pixels greater than
her current x position)
iii. Peach will check to see if there is an object that blocks movement
at this destination position (before moving there). If so:
1. Peach will bonk the target object that is blocking her way
(e.g., cause a bonk() method in the target object to be
called)
2. Peach will abort trying to move to the destination square
since it is blocked
iv. Otherwise, Peach will update her location 4 pixels rightward.
c. If the pressed key was KEY_PRESS_UP then Peach must:
i. Check to see if there is an object that would block movement one
pixel below her. (Such an object gives her support to jump; she
doesn't actually move downward.) If so:
1. Peach must set her remaining_jump_distance to the
appropriate value:
a. If Peach does NOT have Jump Power, then set
remaining_jump_distance to 8.
b. If Peach DOES have Jump Power, then set
remaining_jump_distance to 12.
2. Peach must play the sound SOUND_PLAYER_JUMP
using the playSound() method in the GameWorld class.
d. If the pressed key was the KEY_PRESS_SPACE bar key, then:
i. If Peach doesn’t have Shoot Power, then do nothing
ii. Otherwise, if the time_to_recharge_before_next_fire is greater
than zero, then do nothing.
iii. Otherwise:
1. Play the sound SOUND_PLAYER_FIRE using the
playSound() method in the GameWorld class.
2. Set time_to_recharge_before_next_fire to 8, meaning that
Peach may not fire again for another 8 game ticks
3. Determine the x,y position directly in front of Peach that is
4 pixels away in the direction she’s facing.
4. Introduce a new fireball object at this location into your
StudentWorld. The fireball must have its direction set to the
same direction that Peach was facing when she fired.
 iv. Otherwise, Peach will update her location 4 pixels leftward.
 b. If the pressed key was KEY_PRESS_RIGHT then Peach must:
 i. Set her direction to 0 degrees
 ii. Peach will calculate a target x,y position first (4 pixels greater than
 her current x position)
 iii. Peach will check to see if there is an object that blocks movement
 at this destination position (before moving there). If so:
 1. Peach will bonk the target object that is blocking her way
 (e.g., cause a bonk() method in the target object to be
 called)
 2. Peach will abort trying to move to the destination square
 since it is blocked
 iv. Otherwise, Peach will update her location 4 pixels rightward.
 c. If the pressed key was KEY_PRESS_UP then Peach must:
 i. Check to see if there is an object that would block movement one
 pixel below her. (Such an object gives her support to jump; she
 doesn't actually move downward.) If so:
 1. Peach must set her remaining_jump_distance to the
 appropriate value:
 a. If Peach does NOT have Jump Power, then set
 remaining_jump_distance to 8.
 b. If Peach DOES have Jump Power, then set
 remaining_jump_distance to 12.
 2. Peach must play the sound SOUND_PLAYER_JUMP
 using the playSound() method in the GameWorld class.
 d. If the pressed key was the KEY_PRESS_SPACE bar key, then:
 i. If Peach doesn’t have Shoot Power, then do nothing
 ii. Otherwise, if the time_to_recharge_before_next_fire is greater
 than zero, then do nothing.
 iii. Otherwise:
 1. Play the sound SOUND_PLAYER_FIRE using the
 playSound() method in the GameWorld class.
 2. Set time_to_recharge_before_next_fire to 8, meaning that
 Peach may not fire again for another 8 game ticks
 3. Determine the x,y position directly in front of Peach that is
 4 pixels away in the direction she’s facing.
 4. Introduce a new fireball object at this location into your
 StudentWorld. The fireball must have its direction set to the
 same direction that Peach was facing when she fired.
*/
