#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <iterator>
#include <list>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    //Actor getIntersectActor();
    bool isIntersectingSolid(int x, int y);
    bool isIntersecting(int x, int y, Actor* it);
    int randDirection();
    void peachBonk( int x, int y);
    void addToVector( Actor* it);
    int peachX();
    int peachY();
    void damagePeach();
   // void setUp();

private:
    char board[32][32];
    std::vector<Actor*> actors;
    Peach *peach;
    
};

#endif // STUDENTWORLD_H_


// What i need to do for init
// read data
// create data structure to keep track of objects: enemies(goombas, koopas, piranaha, enemyprojectiles( piranaha fire, shell), powerups(flower, mushroom, star), structures(boxes, pipes, flags), peach


// keep track of attributes of each of these objects

// Each object must have the following base properties
// alive/dead status, damageable, whether something can move into its space




/*Actor.h // contains base, Peach, and Block class declarations
 // as well as constants required by these classes
 Actor.cpp // contains the implementation of these classes
 StudentWorld.h // contains your StudentWorld class declaration
 StudentWorld.cpp // contains your StudentWorld class implementation*/



/*Your StudentWorld’s init() member function must:
 1. Initialize the data structures used to keep track of your game’s world.
 2. Allocate and insert a Peach object into the game world. Every time a level starts
 or restarts, Peach starts out fully initialized (with the no special powers active,
 etc.) in her initial location as specified by the current level data file.
 3. Allocate and insert all of the blocks, pipes, flags, enemies and Mario into the
 game world as described below.
 18
 Your init() method must construct a representation of your world and store this in a
 StudentWorld object. It is required that you keep track of all of the actors (Peach,
 enemies, blocks, flags, goodies, etc.) in a single STL collection such as a list, map or
 vector. (To do so, we recommend using a container of pointers to the actors). If you like,
 your StudentWorld object may keep a separate pointer to the Peach object rather than
 keeping a pointer to that object in the container with the other actor pointers; Peach is the
 only actor pointer allowed to not be stored in the single actor container. The init() method
 may also initialize any other StudentWorld member variables it needs, such as the number
 of remaining actors that need to be destroyed on this level before Peach can advance to
 the next level.
 The init() method must load information from a level data file for the current level into a
 Level object, and use this to populate the current level with objects at the proper
 locations. (Details appear later in the Level Data File section.) The following types of
 objects must be populated:
 Blocks and pipes, including special blocks that produce goodies when bonked
 ● Peach
 ● Flags
 ● Mario
 ● Goombas, koopas and piranhas
 A level of the game is a 32x32 grid, each spot possibly occupied by an object. If the
 Level object specifies that a given object is at position lx,ly in the grid (where 0 <= lx <
 32, and 0 <= ly < 32), then the actual object must be placed at location (x,y) on the
 screen, where x = lx * SPRITE_WIDTH and y = ly * SPRITE_HEIGHT. (Notice that 32
 comes from VIEW_WIDTH (i.e., 256) / SPRITE_WIDTH (i.e., 8), and similarly for the
 heights.)
 The init() method returns GWSTATUS_LEVEL_ERROR if no level data file exists for the current
 level or if the file is improperly formatted. Otherwise, init() returns
 GWSTATUS_CONTINUE_GAME. These constants are defined in GameConstants.h.
 You must not call the init() method yourself. Instead, this method will be called by our
 framework code when it’s time for a new game to start (or when the player completes a
 level or needs to restart a level).*/
