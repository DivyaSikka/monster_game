//
//  Cell.cpp
//  Project3
//
//  Created by Divya Sikka on 5/19/24.
//

#include <stdio.h>
#include "Cell.h"
using namespace std;

//constructor sets all bool values to false and the actors/objects to nullptrs
Cell::Cell(){
    myWall = false;
    myStaircase = false;
    isActor = false;
    isObject = false;
    myIdol = false;
    myActor = nullptr;
    myObject = nullptr;
}

//created so that if I set actor to nullptr, it removes the actor from that cell, else sets the actor
void Cell::setActor(Actor* actor){
    if (actor != nullptr){
        myActor = actor;
        isActor = true;
    }
    else{
        myActor = nullptr;
        isActor = false;
    }
}

//created so that if I set obj to nullptr, it removes the actor from that cell, else sets the obj
void Cell::setObject(Object* object){
    if (object != nullptr){
        myObject = object;
        isObject = true;
    }
    else{
        myObject = nullptr;
        isObject = false;
    }
}

//functions that return an actor, object, or bool value indicating what is in that cell
//also functions that can set/remove walls, and/or tell if a cell is empty
Actor* Cell::getActor(){
    return myActor;
}

Object* Cell::getObject(){
    return myObject;
}

bool Cell::actor(){
    return isActor;
}

bool Cell::object(){
    return isObject;
}

bool Cell::isWall(){
    return myWall;
}
void Cell::setWall(){
    myWall = true;
}

void Cell::removeWall(){
    myWall = false;
}

bool Cell::isStaircase(){
    return myStaircase;
}

void Cell::setStaircase(){
    myStaircase = true;
}

bool Cell::isIdol(){
    return myIdol;
}

void Cell::setIdol(){
    myIdol = true;
}

bool Cell::isEmpty(){
    if (isWall() || actor() || object() || isStaircase() || isIdol()){
        return false;
    }
    return true;
}


//print the cell (for the display function)
char Cell::printCell(){
    //check for Actor
    if (isActor){
        return (*myActor).getIcon();
    }
    //check for staircase
    if (isStaircase()){
        return '>';
    }
    //check for wall
    if (isWall()){
        return '#';
    }
    //check for Idol
    if (isIdol()){
        return '&';
    }
    //check for object
    if (isObject){
        return (*myObject).getIcon();
    }
    //if not any of these, return a blank space 
    return ' ';
}
