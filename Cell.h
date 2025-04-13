//
//  Cell.h
//  Project3
//
//  Created by Divya Sikka on 5/19/24.
//
#include "Actor.h"
#include "Objects.h"

#ifndef Cell_h
#define Cell_h

//Class to store the locations of all players and objects in the temple (type that the 2D array is)

class Cell{
public:
    //various functions that set the objects and actors, get them, and display if certain items/actors are at spots or not
    Cell();
    void setActor(Actor* actor);
    void setObject(Object*);
    Actor* getActor();
    Object* getObject();
    bool actor(); //displays IF there is an actor at that cell
    bool object(); //displays IF there is an object at that cell
    bool isWall();
    void setWall();
    void removeWall();
    bool isStaircase();
    void setStaircase();
    bool isIdol();
    void setIdol();
    bool isEmpty();
    char printCell();
//private variables to display objects/actors 
private:
    bool myWall;
    bool myStaircase;
    bool isActor;
    bool isObject;
    bool myIdol;
    Actor* myActor;
    Object* myObject;
};

#endif /* Cell_h */
