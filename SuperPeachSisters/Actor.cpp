#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


//ACTOR CLASS
Actor::Actor( bool status, bool canBeDamaged, bool canShareSpace, int imageID, int startX ,int startY, int direction, int depth, double size, StudentWorld* world): GraphObject( imageID,  startX,  startY, direction, depth, size)
{
    m_status= status;
    m_canBeDamaged= canBeDamaged;
    m_canShareSpace= canShareSpace;
    m_world= world;
    m_firing_delay= 0;
    m_falling= false;
    
}

//Destructor
Actor::~Actor()
{
    
}

//Properties of Actor
bool Actor::canGetBonked()
{
    return true; 
}
bool  Actor::getStatus()
{
    return m_status;
}

bool Actor::canFire()
{
    return false;
}
bool Actor::isProjectile()
{
    return false;
}

bool Actor::damagable()
{
    return m_canBeDamaged;
}
bool Actor::shareSpace()
{
    return m_canShareSpace;
}

bool Actor::isFalling()
{
    return m_falling;
}

int Actor::getFiringDelay()
{
    return m_firing_delay;
}
bool Actor::createsShell()
{
    return false;
}



//sets Actor properties
void Actor::setFalling( bool f)
{
    m_falling = f;
}

void Actor::setStatus(bool status)
{
    m_status= status;
}

void Actor::setFiringDelay(int x)
{
    m_firing_delay= m_firing_delay + x;
}




// Actor movement
void Actor::fall()
{
    if( !(getWorld()->isIntersectingSolid(getX(), getY()-2)))
    {
      //  std::cerr << "movedown" << std::endl;
        moveTo(getX(), getY()-2);
    }
     if( getDirection()== 0)
    {
        if(getWorld()->isIntersectingSolid(getX()+2, getY()))
        {
            setStatus(false);
            return;
        }
        else
        {
            moveTo(getX()+2, getY());
        }
    }
     else
     {
         if(getWorld()->isIntersectingSolid(getX()-2, getY()))
         {
            
             setStatus(false);
             return;
         }
         else
         {
             moveTo(getX()-2, getY());
         }
     }
}



// StudentWorld Pointer Accessor

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
    if(!getStatus())
    {
        return;
    }
    if(getWorld()->isIntersecting(getWorld()->peachX(), getWorld()->peachY(), this))
    {
        if( getWorld()->hasStarPower())
        {
            getWorld()->playSound(SOUND_PLAYER_KICK);
            setStatus(false);
            getWorld()->increaseScore(100);
            if (createsShell())
            {
                KoopaShell *s= new KoopaShell(getX(), getY(), getWorld(), getDirection() );
                getWorld()->addToVector(s);
            }
            return;
        }
        else
        {
            getWorld()->damagePeach();
            return;
        }
        
    }
  
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


//GOOMBA METHODS
Goomba::Goomba( int startX, int startY, StudentWorld* world, int imageID, int direction): Enemy(  startX, startY, world, imageID, direction)
{
    
}

Goomba::~Goomba()
{
    
}

void Goomba::doSomething()
{

    Enemy::doSomething();
}

//KOOPA METHODS
Koopa::Koopa( int startX, int startY, StudentWorld* world, int imageID, int direction): Enemy(  startX, startY, world, imageID, direction)
{
    
}

Koopa::~Koopa()
{
  
    
}

bool Koopa::createsShell()
{
    return true;
}

void Koopa::doSomething()
{
    Enemy::doSomething();
    if( getStatus()== false)
    {
        return;
    }
}


//PIRANHA METHODS
Piranha::Piranha(int startX, int startY, StudentWorld* world, int imageID, int direction):Enemy(  startX, startY, world, imageID, direction)
{
    m_firing_delay = 0;
}

Piranha::~Piranha()
{
    
}

void Piranha::doSomething()
{
   
    if (!getStatus())
    {
        return;
    }
    increaseAnimationNumber();
    if(getWorld()->isIntersecting(getWorld()->peachX(), getWorld()->peachY(), this))
    {
        if( getWorld()->hasStarPower())
        {
            getWorld()->playSound(SOUND_PLAYER_KICK);
            setStatus(false);
            return;
        }
        else
        {
            getWorld()->damagePeach();
            return;
        }
        
    }
    
    if( !(getWorld()->peachY() > (getY() - 1.5*SPRITE_HEIGHT)&&getWorld()->peachY() < (getY() + 1.5*SPRITE_HEIGHT)))
    {
        return;
    }
    if(getWorld()->peachX() > getX())
    {
        setDirection(0);
    }
    else
    {
        setDirection(180);
    }
    if(getFiringDelay()==0)
    {
    }
    if(getFiringDelay() >0)
    {
        setFiringDelay(-1);
        return;
    }
    else if( (getWorld()->peachX() > getX() - 8*SPRITE_WIDTH&&getWorld()->peachX() < getX() + 8*SPRITE_WIDTH))
    {
        PiranhaFireball *f = new PiranhaFireball (getX(), getY(), getWorld(), getDirection());
        getWorld()->addToVector(f);
        getWorld()->playSound(SOUND_PIRANHA_FIRE);
        setFiringDelay(40);
       
        
    }
     
}

bool Piranha::canFire()
{
    return true;
    
}


void Piranha::setFiringDelay(int x)
{
    m_firing_delay= m_firing_delay + x;
}

int Piranha::getFiringDelay()
{
    return m_firing_delay;
}



//GOODIE CLASS
Goodie::Goodie( int startX, int startY, StudentWorld* world, int imageID):Actor( true, false, true, imageID, startX, startY, 0,1,1,world)
{
    
}

Goodie::~Goodie()
{
    
}



void Goodie::doSomething()
{
    if( !(getWorld()->isIntersectingSolid(getX(), getY()-2)))
    {
      //  std::cerr << "movedown" << std::endl;
        moveTo(getX(), getY()-2);
    }
     if( getDirection()== 0)
    {
        if(getWorld()->isIntersectingSolid(getX()+2, getY()))
        {
            setDirection(180);
            //return;
        }
        else
        {
            moveTo(getX()+2, getY());
        }
       
        
        
    }
     else
     {
         if(getWorld()->isIntersectingSolid(getX()-2, getY()))
         {
            
             setDirection(0);
            // return;
         }
         else
         {
             moveTo(getX()-2, getY());
         }
     }
    }
    

//MUSHROOM METHODS
Mushroom::Mushroom(int startX, int startY, StudentWorld* world):Goodie(startX, startY, world, IID_MUSHROOM)
{
    
}

Mushroom::~Mushroom()
{
    
}

void Mushroom::bonk()
{

    setStatus(false);
    getWorld()->increaseScore(75);
    if( getWorld()->getHitPts()==1)
    {
        getWorld()->addHitPts(1);
    }
   
    getWorld()->setMushroomPower(true);
    
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
    
}


//FLOWER METHODS
Flower::Flower(int startX, int startY, StudentWorld* world):Goodie(startX, startY, world, IID_FLOWER)
{
    
}

Flower::~Flower()
{
    
}

void Flower::bonk()
{

    setStatus(false);
    getWorld()->increaseScore(50);
    if( getWorld()->getHitPts()==1)
    {
        getWorld()->addHitPts(1);
    }
    getWorld()->setFlowerPower(true);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
    
}
  
//STAR METHODS
Star::Star(int startX, int startY, StudentWorld* world):Goodie(startX, startY, world, IID_STAR)
{
        
}

Star::~Star()
{
        
}

void Star::bonk()
{
    setStatus(false);
    getWorld()->increaseScore(100);
    
    if( getWorld()->getHitPts()==1)
    {
        getWorld()->addHitPts(1);
    }
    getWorld()->setStarPower(true);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
    
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
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        setStatus(false);
        getWorld()->nextLevel();
       
       
    }
    
   
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
        getWorld()->playSound(SOUND_GAME_OVER);
       
    }
    
}
void Mario::doSomething()
{
    
}


//PROJECTILES

Projectiles::Projectiles( int startX, int startY, StudentWorld* world, int imageID, int direction):Actor( true, false, true, imageID, startX, startY, direction, 1,1, world)
{
    
}

Projectiles::~Projectiles()
{
    
}

void Projectiles::doSomething()
{
   
    Actor::fall();
     
}



bool Projectiles::isProjectile()
{
    return true;
}


PiranhaFireball::PiranhaFireball( int startX, int startY, StudentWorld* world, int direction):Projectiles( startX, startY, world, IID_PIRANHA_FIRE, direction)
{
    
}

PiranhaFireball::~PiranhaFireball()
{
    
}

void PiranhaFireball::bonk()
{
    
    
}

    void PiranhaFireball::doSomething()
    {
        
        if(!getStatus())
        {
            return;
        }
        if(getWorld()->isIntersecting(getWorld()->peachX(), getWorld()->peachY(), this))
        {
            getWorld()->damagePeach();
            setStatus(false);
            return;
        }
        
        Projectiles::doSomething();
    }

KoopaShell::KoopaShell(int startX, int startY, StudentWorld* world, int direction):Projectiles( startX, startY, world, IID_SHELL, direction)
{
    
}

KoopaShell::~KoopaShell()
{
    
}

void KoopaShell::doSomething()
{
    
    if(!getStatus())
    {
        return;
    }
    bool b= getWorld()->damageDamagable(getX(), getY());
    if(b)
    {//std::cerr << "created"<<std::endl;
       
        setStatus(false);
        return;
    }
    Projectiles::doSomething();
    
}

void KoopaShell::bonk()
{
    
}

PeachFireball::PeachFireball( int startX, int startY, StudentWorld* world, int direction):Projectiles( startX, startY,world, IID_PEACH_FIRE, direction)
{
    
}
PeachFireball::~PeachFireball()
{
    
}
void PeachFireball::doSomething()
{
    if(!getStatus())
    {
        return;
    }
    bool b= getWorld()->damageDamagable(getX(), getY());
    if(b)
    {
       
        setStatus(false);
        return;
    }
    Projectiles::doSomething();
}

void PeachFireball::bonk()
{
   
}



//STRUCTURES
Pipe::Pipe(int startX, int startY, StudentWorld* world ,int imageID):Actor(true, false, false, imageID, startX, startY,0,2,1.0, world )
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
   


        getWorld()->playSound(SOUND_PLAYER_BONK);
        
   
}




Block::Block( int startX, int startY, bool contains_power, char power, StudentWorld* world): Pipe(startX, startY, world, IID_BLOCK)
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
    if( m_contains_Power)
    {
        m_contains_Power= false;
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        if(m_power== 'm')
        {
            Mushroom *m= new Mushroom(getX(), getY()+8, getWorld());
            getWorld()->addToVector(m);
           
        }
        if(m_power== 's')
        {
            Star *s= new Star(getX(), getY()+8, getWorld());
            getWorld()->addToVector(s);
           
        }
        if(m_power== 'f')
        {
            Flower *f= new Flower(getX(),getY()+8, getWorld());
            getWorld()->addToVector(f);
            
           
        }
       
        
        
    }
    else
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
       
        
    }
   
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
    remaining_jump_distance= 300;
    m_falling= false;
    remaining_star_time= 0;
    m_finished= false;
    
    
    
}

Peach::~Peach()
{
  
}
void Peach::bonk()
{
    
}

 
bool Peach::isInvincible()
{
    return m_invincible;
}

bool Peach::hasStarPower()
{
    return m_star;
}

bool Peach::hasFlowerPower()
{
    return m_flower;
}

bool Peach:: hasMushroomPower()
{
    return m_mushroom;
}

void Peach::setMushroomPower( bool f)
{
    m_mushroom= f;
   
}

void Peach::setFlowerPower(bool f)
{
    m_flower= f;
}

void Peach::setStarPower(bool f)
{
    m_star= f;
    remaining_star_time= 150;
}

void Peach::setInvincibleTime( int n)
{
    invincible_time= n;
}
int Peach::getStarTime ()
{
    return remaining_star_time;
}

void Peach::setInvincible(bool f)
{
    if (f)
    {
        m_invincible = true;
        setInvincibleTime(10);
      
       
    }
    else
    {
        m_invincible= false;
        
    }
}

void Peach::addHitPts( int ht)
{
    m_hitPts += ht;
}
int Peach:: getHitPts()
{
    return m_hitPts;
}

bool Peach:: canFire()
{
    return true;
}

bool Peach:: finishedLevel()
{
    return m_finished;
}

void Peach::setFinishedLevel(bool b)
{
    m_finished= b;
}


void Peach::setFiringDelay( int x)
{
    time_to_recharge_before_next_fire= time_to_recharge_before_next_fire +x;
}

int Peach::getFiringDelay()
{
    return time_to_recharge_before_next_fire;
}

bool Peach::isProjectile()
{
    return false;
}



void Peach::doSomething()
{
    if(!getStatus())
    {
        return;
    }
    
    if( hasStarPower())
    {
        remaining_star_time--;
        if(remaining_star_time <= 0)
        {
            setStarPower(false);
        }
    }
    if ( getFiringDelay()>0)
    {

        setFiringDelay(-1);
    }
    
    //temporary invincibility
    if( m_invincible)
        
    {
       
        invincible_time--;
        if( invincible_time <= 0)
        {
            m_invincible= false;
        }
    }
    getWorld()->peachBonk(getX(), getY());
    
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
          getWorld()->peachBonk(getX(), getY()+4);
          remaining_jump_distance= 0;
      }
        else if( m_jumping)
        {
            moveTo(getX(), getY()+4);
            getWorld()->peachBonk(getX() , getY());
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
                 getWorld()->peachBonk(getX()-4 , getY());
                 
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
                 getWorld()->peachBonk(getX()+4 , getY());
                 break;
                 
             }
             if( !getWorld()->isIntersectingSolid(getX() +4, getY()-1)&&!m_jumping)
             {
                 m_falling = true;
             }
                moveTo(getX() +4, getY());
             break;
           
    case KEY_PRESS_UP:
             
           
             if( getWorld()->isIntersectingSolid(getX() , getY()-1))
             {
                 m_jumping = true;
                 if(m_mushroom)
                 {
                     remaining_jump_distance= 12;
                 }
                 else{
                     remaining_jump_distance= 8;
                 }
                 getWorld()->playSound(SOUND_PLAYER_JUMP);
                 if(getWorld()->isIntersectingSolid(getX() , getY()+4))
                 {
                    
                     getWorld()->peachBonk(getX() , getY()+4);
                     
                 }
        
             }
        
            
             
             break;
    case KEY_PRESS_SPACE:
             if(!hasFlowerPower())
             {
                 break;
             }
             if ( getFiringDelay()>0)
             {
                 
                 break;
             }
             else
             {
                 getWorld()->playSound( SOUND_PLAYER_FIRE);
                
                 
                 int spacing ;
                 if (getDirection()== 0)
                 {
                     spacing= 4;
                 }
                 else
                 {
                     spacing = -4;
                 }
                 PeachFireball *fp = new PeachFireball( getX()+spacing ,getY(), getWorld(), getDirection() );
                 getWorld()->addToVector(fp);
                 setFiringDelay(8);
                 
             }
             break;
             
            
             
     }
         
       
     }
    
    
}

