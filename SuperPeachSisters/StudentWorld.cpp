#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw


class Actor;

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    
    Level lev(assetPath());
    string level_file = levelString();
    std::cerr<< level_file;
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
    {
        cerr << "Could not find level01.txt data file" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }

    
    else if (result == Level::load_fail_bad_format)
    {
        cerr << "level01.txt is improperly formatted" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success)
    {
    cerr << "Successfully loaded level" << endl;
        for( int x= 0; x< GRID_WIDTH; x++)
        {
            for( int y= 0; y< GRID_HEIGHT; y++)
            {
                Level::GridEntry ge;
                ge = lev.getContentsOf(x, y); // x=5, y=10
              switch(ge)
                {
                    case Level::empty:{
                     
                        
                        break;
                        
                    }
                    case Level::peach:{
                        Peach *p= new Peach(x*SPRITE_WIDTH,y*SPRITE_HEIGHT, this);
                        peach= p;
                      
                       
                        
                        break;}
                   
                    case Level::block:
                    {
                        Block *b= new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,false,' ', this);
                        actors.push_back(b);
                       
                        break;
                        
                    }
                   
                case Level::koopa:
                    {
                        Koopa *k = new Koopa(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this, IID_KOOPA, randDirection() );
                        actors.push_back(k);
                      
                        break;
                    }
                case Level::goomba:
                    {
                        Goomba *g = new Goomba(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this, IID_GOOMBA, randDirection() );
                        actors.push_back(g);
                       
                        break;
                    }
                 
                case Level::star_goodie_block:
                    {
                        Block *b= new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,true,'s', this);
                        actors.push_back(b);
                       
                        break;
                    }
               case Level::piranha:
                    {
                        Piranha *p = new Piranha(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this, IID_PIRANHA, randDirection() );
                        actors.push_back(p);
                        
                        break;
                    }
               
                case Level::mushroom_goodie_block:
                    {
                        Block *b= new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,true,'m', this);
                        actors.push_back(b);
                   
                        break;
                    }
                case Level::flower_goodie_block:
                    {
                        Block *b= new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,true,'f', this);
                        actors.push_back(b);
                        break;
                       
                    }
                        
                 
                        
                case Level::pipe:
                    {
                        Pipe *p= new Pipe(x*SPRITE_WIDTH, y*SPRITE_HEIGHT,this, IID_PIPE );
                        actors.push_back(p);
                        
                        break;
                    }
               
                case Level::mario:
                    {
                        
                    
                        Mario *m= new Mario(x*SPRITE_WIDTH, y*SPRITE_HEIGHT,this );
                        actors.push_back(m);
                        
                        break;
                    }
                case Level::flag:
                        Flag *f= new Flag(x*SPRITE_WIDTH, y*SPRITE_HEIGHT,this , IID_FLAG);
                        actors.push_back(f);
                      
                        break;
                        
                
                        
            }
        }
   
            
        
    }
}


    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::updateText()
{
    ostringstream oss;
    string lives;
    string level;
    string score;
    string starPower;
    string flowerPower;
    string mushroomPower;
    
    lives= "Lives: ";
    
    level= "Level: ";
    
    score= "Score: ";
    
    starPower= "StarPower!";
    flowerPower= "ShootPower!";
    mushroomPower= "JumpPower!";
    
    
    
        
    oss << lives << getLives()<< "  "<< level;
    oss.fill('0');
    oss << setw(2)<< getLevel();
    oss << "  "<< score;
    oss.fill('0');
    oss << setw(6) << getScore();
    oss << "  ";
    //oss.fill('0');
    if( hasStarPower())
    {
        oss << setw(1) << starPower << " ";
    }
    if(hasFlowerPower())
    {
        oss << setw(1) << flowerPower << " ";
    }
    if( hasMushroomPower())
    {
        oss << setw(1) << mushroomPower << " ";
    }
    
   
    
    string s = oss.str();
    
    setGameStatText(s);
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
  
    
    /* The status line at the top of the screen must have the following format:
     Lives: 2 Level: 5 Points: 500 StarPower! ShootPower! JumpPower!
     Where the items in red are ALWAYS required, and the items in blue are required only if
     Peach has a particular power. For example, if Peach just has Jump Power, the line might
     look like this:
     Lives: 2 Level: 5 Points: 500 JumpPower!
     Each of the first three stats of the status line must be separated from each other by exactly
     two spaces. For example, between “Lives: 2” and “Level:” there must be two spaces. The
     powers (e.g., JumpPower!), if present, must each be separated by a single space, and are
     separated from the point count by a single space as well. You may find the Stringstreams
     writeup on the main class web site to be helpful.*/
    updateText();
    
    vector<Actor*>::iterator it;
    if((*peach).getStatus())
    {
        (*peach).doSomething();
    }
    for( it= actors.begin(); it!=actors.end(); it++)
    {
        if((*it)->getStatus())
        {
            (*it)->doSomething();
            if( !peach->getStatus())
            {
                playSound(SOUND_PLAYER_DIE);
                return GWSTATUS_PLAYER_DIED;
            }
            
        }
        else
        {
            delete *it;
            it= actors.erase(it);
            it--;
        }
    }
    if( peach->finishedLevel())
    {
        peach->setFinishedLevel(false);
        return GWSTATUS_FINISHED_LEVEL;

    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::peachBonk(int x, int y)
{
    vector<Actor*>::iterator it;
    // if shareSpace then call the function's doSomething method
    for( it= actors.begin(); it!=actors.end(); it++)
    {
        // used to pass in peach->getX() and peach-> getY() instead of x and y
        if(((*it)->canGetBonked() && isIntersecting(x, y, (*it))||(*it)->canFire()))
        {
             (*it)->bonk();
        }
    }
    
}

int StudentWorld::randDirection()
{
    int x= randInt(0,9);
    if( x%2== 0)
    {
        return 0;
    }
    else{
        
        return 180;
    }
        
}

void StudentWorld::nextLevel()
{
   
    peach->setFinishedLevel(true);
  
}

string StudentWorld::levelString()
{
    ostringstream oss;
    oss<<"level";
    oss.fill('0');
    oss << setw(2)<< getLevel();
    oss<<".txt";
    string s= oss.str();
    return s;
}

bool StudentWorld::isIntersecting( int x, int y,  Actor* it)
{
    
    int bigX= x+ SPRITE_WIDTH -1;
    int bigY= y+SPRITE_HEIGHT -1;
    
        if(((x+SPRITE_WIDTH/2)>= (*it).getX() && bigX <= (*it).getX()+SPRITE_WIDTH-1) && ((y+SPRITE_HEIGHT/2)>= (*it).getY() && bigY- SPRITE_HEIGHT/2 <= (*it).getY()+SPRITE_HEIGHT -1))
        {
            
         
        
                return true;
            
            
        }
    if(((x+SPRITE_WIDTH/2)>= (*it).getX() && bigX- SPRITE_WIDTH/2 <= (*it).getX()+SPRITE_WIDTH-1) && ((y+SPRITE_HEIGHT/2)>= (*it).getY() && bigY <= (*it).getY()+SPRITE_HEIGHT -1))
    {
        
      
        
            return true;
        
        
    }
    
    if(((x-SPRITE_WIDTH/2)<= (*it).getX() && bigX +SPRITE_WIDTH/2 >= (*it).getX()+SPRITE_WIDTH-1) && ((y-SPRITE_HEIGHT/2)<= (*it).getY() && bigY >= ((*it)).getY()+SPRITE_HEIGHT -1))
    {
      
        
            return true;
        
        
    }
    if(((x-SPRITE_WIDTH/2)<= (*it).getX() && bigX >= (*it).getX()+SPRITE_WIDTH-1) && ((y-SPRITE_HEIGHT/2)<= (*it).getY() && bigY +SPRITE_HEIGHT/2 >= ((*it)).getY()+SPRITE_HEIGHT -1))
    {
     
        
            return true;
        
        
    }
    return false;
   

     
}

bool StudentWorld::damageDamagable( int x, int y)
{
    vector<Actor*>::iterator it;
     
    bool b= false;
  
     
    // if shareSpace then call the function's doSomething method
    for( it= actors.begin(); it!=actors.end(); it++)
    {
        
        if (isIntersecting(x, y, (*it)) && (*it)->getStatus())
        {
            if((*it)->damagable())
            {
                (*it)->setStatus(false);
                b= true;
                increaseScore(100);
                if( (*it)->createsShell())
                {
                    KoopaShell *s= new KoopaShell((*it)->getX(), (*it)->getY(), this, (*it)->getDirection() );
                    addToVector(s);
                }
            }
        }
    }
    return b;
}

 bool StudentWorld::isIntersectingSolid(int x, int y)
    {
     
    vector<Actor*>::iterator it;
     
    // if shareSpace then call the function's doSomething method
    for( it= actors.begin(); it!=actors.end(); it++)
    {
        
        
        int x_max= x+ SPRITE_WIDTH -1;
        int y_max= y+SPRITE_HEIGHT -1;
        
        int x1= (*it)->getX();
        int y1= (*it)->getY();
        
        int x1_max= x1+ SPRITE_WIDTH -1;
        int y1_max= y1+SPRITE_HEIGHT -1;
      
        
        if(x<=x1 && x1<= x_max && y<= y1 && y1<= y_max)
        {
            if( !(*it)->shareSpace())
            {
                return true;
            }
            
        }
        
        
        if(x<=x1 && x1<= x_max && y<= y1_max && y1_max<= y_max)
        {
            if( !(*it)->shareSpace())
            {
                return true;
            }

        }
        
        if(x1<= x && x<= x1_max && y<= y1_max && y1_max<= y_max)
        {
            if( !(*it)->shareSpace())
            {
                return true;
            }

        }
         
        
        if(x1<= x && x<= x1_max && y<= y1 && y1<= y_max)
        {
            if( !(*it)->shareSpace())
            {
                return true;
            }

        }
    
    }
     return false;
 }

bool StudentWorld:: hasStarPower()
{
    return( peach->hasStarPower());
}
bool StudentWorld::hasFlowerPower()
{
    return ( peach->hasFlowerPower());
}
bool StudentWorld::hasMushroomPower()
{
    return( peach->hasMushroomPower());
}


void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
    for( it= actors.begin(); it!=actors.end();)
    {
        delete *it;
        it= actors.erase(it);
    }
    delete peach;
}

void StudentWorld::addToVector( Actor* it)
{
    actors.push_back (it);
}

int StudentWorld::peachX()
{
    return peach->getX();
}

int StudentWorld::peachY()
{
    return peach->getY();
}

void StudentWorld::addHitPts(int x)
{
    peach->addHitPts(x);
}
int StudentWorld::getHitPts()
{
    return peach->getHitPts();
}
void StudentWorld::setMushroomPower(bool b)
{
    peach->setMushroomPower(b);
}
void StudentWorld::setFlowerPower(bool b)
{
    peach->setFlowerPower( b);
}
void StudentWorld::setStarPower(bool b)
{
    peach->setStarPower(b);
}

void StudentWorld::damagePeach()
{
    if(!peach->isInvincible()&&!peach->hasStarPower())
    {
        peach->addHitPts(-1);
    }
   
    if( !peach->isInvincible() && !peach->hasStarPower())
    {
        if( peach->hasMushroomPower() || peach->hasFlowerPower())
        {
            peach->setMushroomPower(false);
            peach->setFlowerPower(false);
            peach->setInvincible(true);
            //std::cerr <<"run once"<<std::endl;
            return;
        }
        
    }
    if(peach->hasStarPower())
    {
        return;
    }
    
    else if( peach->getHitPts()>0 &&!peach->hasStarPower() )
    {
        playSound(SOUND_PLAYER_HURT);
    }
  
    else
    {
        playSound(SOUND_PLAYER_DIE);
        peach->setStatus(false);
        decLives();
        //std::cerr<<getLives() <<"NUMBER OF LIVES"<< std::endl;
        if( !(getLives() > 0))
        {
            
        }
    }
}



