//
//  Actor.h
//  Project3
//
//  Created by Divya Sikka on 5/18/24.
//

#ifndef Actor_h
#define Actor_h
#include "Objects.h"
#include <iostream>
#include <list>

#define MAX_COLUMNS 70
#define MAX_ROWS 18
#define MAX_LEVELS 5
using namespace std;
class Game;

class Actor{
public:
    Actor(int posCol, int posRow, int hitPoints, Weapon current, int armorPoints, int strength, int dexterity, int sleeptime, char icon, string name); //constructor
    void setPos(int newCol, int newRow); //setting these is NOT diff for diff actors
    void getPos(int* actorCol, int* actorRow); //store variables, pass by reference
    char getIcon(); //returns icon for all actors
    void setHitPoints(int newPoints); //increased health
    int getHitPoints(); //returns number of hit points
    void increaseMaxHitPoints(int newPoints); //increases hit points up to max
    int getMaxHitPoints(); //returns max hit points
    void setArmorPoints(int newPoints); //increase armor points
    int getArmorPoints(); //returns armor points
    void setStrength(int newStrength); //increase strength points
    int getStrength(); //returns strength
    void setDexterity(int newDex); //increase dexterity
    int getDexterity(); //returns dexterity
    void setSleepTime(int newSleep); //increase sleep time
    int getSleepTime(); //returns sleep time of actor
    void decrementSleepTime(); //decrements sleep time by 1
    void cheatHitPoints(); //for the cheat implementation in the game class
    void cheatStrength(); //for cheat implementation in game class
    Weapon* getCurrentWeapon(); //returns the current weapon an actor is weilding
    void changeCurrentWeapon(Weapon* newCurr); //changes the weapon an actor is weilding
    string getName(); //returns the name of the actor
    virtual ~Actor() = default; //destructor
    
private:
    int myCol;
    int myRow;
    int myHitPoints;
    int maxHitPoints;
    Weapon myCurrent;
    int myArmorPoints;
    int myStrength;
    int myDexterity;
    int mySleepTime;
    char myIcon;
    string myName;
};

class Player : public Actor{
public:
    //Player functions for inventory (using private list)
    Player(int posCol, int posRow);
    bool addObjectToInventory(Object* obj);
    void removeObjectFromInventory(Object* obj);
    void displayInventory();
    bool hasObjectInInventory(char c);
    Object* getObjectFromInventory(char c);
private:
    //A player's inventory is an array of Object pointers
    list< Object* > Inventory;
};

//Abstract Base Class (can't create just a monster)
class Monster : public Actor{
public:
    Monster(int posCol, int posRow, int hitPoints, Weapon current, int armorPoints, int strength, int dexterity, int sleeptime, char icon, string name);
    virtual bool monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game) = 0;
    bool turnDone();
    void resetTurnDone();
    void setTurnDone();
private:
    bool turnDoneVar; //checks if the monster's turn has been completed, has public functions to change
};

//different types of monsters and their constructors + move functions
class Bogeymen : public Monster{
public:
    Bogeymen(int posCol, int posRow);
    virtual bool monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game);
};

class Snakewomen : public Monster{
public:
    Snakewomen(int posCol, int posRow);
    virtual bool monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game);
};

class Dragon : public Monster{
public:
    Dragon(int posCol, int posRow);
    virtual bool monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game);
};

class Goblin: public Monster{
public:
    Goblin(int posCol, int posRow, int maxSmellDistance);
    virtual bool monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game);
private:
    int maxSmellDist; //goblin also stores the max smell distance
    //helper function for Goblin's monsterMove
    int canGoblinSmell(int playerRow, int playerCol, int goblinRow, int goblinCol, int smellDist, Game* game, int* nextMoveRow, int* nextMoveCol, bool visited[MAX_ROWS][MAX_COLUMNS]);
};

#endif /* Actor_h */
