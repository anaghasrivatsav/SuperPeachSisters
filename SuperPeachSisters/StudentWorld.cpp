#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"

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
    string level_file = "level01.txt";
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
                        board[x][y]= ' ';
                        
                        break;}
                    case Level::peach:{
                        Peach *p= new Peach(x*SPRITE_WIDTH,y*SPRITE_HEIGHT, this);
                        peach= p;
                       // actors.push_back(p);
                        board[x][y]= '@';
                        
                        break;}
                   
                    case Level::block:{
                        Block *b= new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,false,-1, this);
                        actors.push_back(b);
                        board[x][y]= '#';
                        break;}
                    default:{
                        break;}
                /*case Level::koopa:
                        cout << "Location 5,10 starts with a koopa" << endl;
                        break;
                case Level::goomba:
                        cout << "Location 5,10 starts with a goomba" << endl;
                        break;
                case Level::star_goodie_block:
                        cout << "Location 5,10 has a star goodie block" << endl;
                        break;
                case Level::piranha:
                        break;
                case Level::mushroom_goodie_block:
                        break;
                case Level::flower_goodie_block:
                        break;
                case Level::pipe:
                        break;
                case Level::mario:
                        break;
                case Level::flag:
                        cout << "Location 5,10 is where a flag is" << endl;
                        break;*/
                        
                
                        
            }
        }
   
            
        
    }
}

    

    //

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
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
    }
    

        
       /* int StudentWorld::move()
         {
        // The term "actors" refers to all actors, e.g., Peach, goodies,
        // enemies, flags, blocks, pipes, fireballs, etc.
        // Give each actor a chance to do something, incl. Peach
        for each of the actors in the game world
        {
         if (that actor is still active/alive)
         {
         // tell that actor to do something (e.g. move)
         that actor -> doSomething();
        if (Peach died during this tick) {
         play dying sound
        return GWSTATUS_PLAYER_DIED;
        }
        if (Peach reached Mario) {
         play game over sound
        return GWSTATUS_WON_GAME;
        }
        if (Peach competed the current level) {
        play completed level sound
        return GWSTATUS_FINISHED_LEVEL;
        }
         }
        }
        // Remove newly-dead actors after each tick
        remove dead game objects
        // Update the game status line
        update display text // update the score/lives/level text at screen top
        // the player hasn’t completed the current level and hasn’t died, so
        // continue playing the current level
        return GWSTATUS_CONTINUE_GAME;
         }
       
    }*/
    
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

 bool StudentWorld::isIntersecting(int x, int y, char direction)
    {
    vector<Actor*>::iterator it;
    for( it= actors.begin(); it!=actors.end(); it++)
    {
        if((*it)->shareSpace())
        {
            return false;
        }
    
        
        int newX= x+ SPRITE_WIDTH -1;
        int newY= y+SPRITE_HEIGHT -1;
        
            if(((x+SPRITE_WIDTH/2)>= (*it)->getX() && newX <= (*it)->getX()+SPRITE_WIDTH-1) && ((y+SPRITE_HEIGHT/2)>= (*it)->getY() && newY- SPRITE_HEIGHT/2 <= (*it)->getY()+SPRITE_HEIGHT -1))
            {
                
                if(direction=='r')
                {
                    return true;
                }
                
            }
        if(((x+SPRITE_WIDTH/2)>= (*it)->getX() && newX- SPRITE_WIDTH/2 <= (*it)->getX()+SPRITE_WIDTH-1) && ((y+SPRITE_HEIGHT/2)>= (*it)->getY() && newY <= (*it)->getY()+SPRITE_HEIGHT -1))
        {
            
            if(direction=='u')
            {
                return true;
            }
            
        }
        
        if(((x-SPRITE_WIDTH/2)<= (*it)->getX() && newX +SPRITE_WIDTH/2 >= (*it)->getX()+SPRITE_WIDTH-1) && ((y-SPRITE_HEIGHT/2)<= (*it)->getY() && newY >= ((*it))->getY()+SPRITE_HEIGHT -1))
        {
            if(direction=='d')
            {
                return true;
            }
            
        }
        if(((x-SPRITE_WIDTH/2)<= (*it)->getX() && newX >= (*it)->getX()+SPRITE_WIDTH-1) && ((y-SPRITE_HEIGHT/2)<= (*it)->getY() && newY +SPRITE_HEIGHT/2 >= ((*it))->getY()+SPRITE_HEIGHT -1))
        {
            if(direction=='l')
            {
                return true;
            }
            
        }
       /* if( (*peach).getX() >= SPRITE_WIDTH-1 && (*peach).getX() <= x &&( *peach).getY() >= y+SPRITE_HEIGHT-1 && (*peach).getY() <=y)
        {
            return true;
        }
       // it++;
        }*/
        
    
    }
     return false;
 }

    
        


/*For the purposes of this project, to determine if two objects A and B overlap, simply
 check to see if their bounding squares overlap. Each object in the game (e.g., a block,
 koopa, Peach, goodies, pipes, fireballs) is represented by a rectangle that is
 SPRITE_WIDTH pixels wide and SPRITE_HEIGHT pixels high. Each object's location
 is denoted by the coordinates of the bottom-left corner of that rectangle. So if an object is
 at location (x,y), it will extend to (x+SPRITE_WIDTH−1, y+SPRITE_HEIGHT−1). It is
 therefore a pretty trivial problem to check if two boxes have any overlap with a few if
 statements. These constants are defined in GameConstants.h.*/

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




/* #include "Level.h" // required to use our provided class
 void StudentWorld::someFunc()
 {
  Level lev(assetPath());
  string level_file = "level01.txt";
  Level::LoadResult result = lev.loadLevel(level_file);
  if (result == Level::load_fail_file_not_found)
  cerr << "Could not find level01.txt data file" << endl;
  else if (result == Level::load_fail_bad_format)
  cerr << "level01.txt is improperly formatted" << endl;
  else if (result == Level::load_success)
  {
  cerr << "Successfully loaded level" << endl;
  Level::GridEntry ge;
  ge = lev.getContentsOf(5, 10); // x=5, y=10
switch(ge)
  {
  case Level::empty:
  cout << "Location 5,10 is empty" << endl;
  break;
  case Level::koopa:
  cout << "Location 5,10 starts with a koopa" << endl;
  break;
  case Level::goomba:
  cout << "Location 5,10 starts with a goomba” << endl;
  break;
  case Level::peach:
  cout << "Location 5,10 is where Peach starts" << endl;
  break;
  case Level::flag:
  cout << "Location 5,10 is where a flag is" << endl;
  break;
  case Level::block:
  cout << "Location 5,10 holds a regular block" << endl;
  break;
  case Level::star_goodie_block:
  cout << "Location 5,10 has a star goodie block” << endl;
  break;
  // etc…
  }
  }
 }
*/
