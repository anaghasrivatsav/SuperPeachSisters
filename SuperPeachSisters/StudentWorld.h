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
    bool isIntersectingSolid(int x, int y);
    bool isIntersecting(int x, int y, Actor* it);
    int randDirection();
    void peachBonk( int x, int y);
    void addToVector( Actor* it);
    int peachX();
    int peachY();
    void damagePeach();
    bool hasStarPower();
    bool hasFlowerPower();
    bool hasMushroomPower();
    bool damageDamagable(int x, int y);
    void updateText();
    std::string levelString();
    void nextLevel();
    void addHitPts(int x);
    int getHitPts();
    void setMushroomPower(bool b);
    void setFlowerPower(bool b);
    void setStarPower(bool b);

private:
    std::vector<Actor*> actors;
    Peach *peach;
    
};

#endif // STUDENTWORLD_H_
