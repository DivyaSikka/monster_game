//
//  Actor.cpp
//  Project3
//
//  Created by Divya Sikka on 5/18/24.
//

#include <stdio.h>
#include <iostream>
#include "Actor.h"
#include "Game.h"
#include "utilities.h"
using namespace std;

//constructor for all actors, initializes all vars
Actor::Actor(int posCol, int posRow, int hitPoints, Weapon current, int armorPoints, int strength, int dexterity, int sleeptime, char icon, string name): myCol(posCol), myRow(posRow), myHitPoints(hitPoints), maxHitPoints(99), myCurrent(current), myArmorPoints(armorPoints), myStrength(strength), myDexterity(dexterity), mySleepTime(sleeptime), myIcon(icon), myName(name)
{}

void Actor::setPos(int newCol, int newRow){
    myCol = newCol;
    myRow = newRow;
}

void Actor::getPos(int* newCol, int* newRow){
    *newCol = myCol; 
    *newRow = myRow;
}

char Actor::getIcon(){
    return myIcon;
}

void Actor::setHitPoints(int newPoints){
    if((myHitPoints + newPoints) <= maxHitPoints){
        myHitPoints+=newPoints;
    }
    else{
        myHitPoints = maxHitPoints;
    }
}

int Actor::getHitPoints(){
    return myHitPoints;
}

void Actor::increaseMaxHitPoints(int newPoints){
    maxHitPoints += newPoints;
}

int Actor::getMaxHitPoints(){
    return maxHitPoints;
}

void Actor::setArmorPoints(int newPoints){
    if ((myArmorPoints + newPoints) <= 99){ //ensures it doesn't exceed the max
        myArmorPoints+=newPoints;
    }
    else{
        myArmorPoints = 99;
    }
}

int Actor::getArmorPoints(){
    return myArmorPoints;
}

void Actor::setStrength(int newStrength){
    if ((myStrength + newStrength) <= 99){ //ensures it doesn't exceed the max
        myStrength+=newStrength;
    }
    else{
        myStrength = 99;
    }
}

int Actor::getStrength(){
    return myStrength;
}

void Actor::setDexterity(int newDex){
    if ((myDexterity + newDex) <= 99){ //ensures it doesn't exceed the max
        myDexterity+=newDex;
    }
    else{
        myDexterity = 99;
    }
}

int Actor::getDexterity(){
    return myDexterity;
}

void Actor::setSleepTime(int newSleep){
    mySleepTime = newSleep;
}

int Actor::getSleepTime(){
    return mySleepTime;
}

void Actor::decrementSleepTime(){
    if (mySleepTime > 0){
        mySleepTime--;
    }
    else{
        mySleepTime = 0; //make sure that it doesn't go below 0
    }
}

//functions for the cheat implementation in the game class
void Actor::cheatHitPoints(){
    maxHitPoints = 50;
}
void Actor::cheatStrength(){
    myStrength = 9;
}

Weapon* Actor::getCurrentWeapon(){
    return &myCurrent;
}

void Actor::changeCurrentWeapon(Weapon* newCurr){
    myCurrent = (*newCurr);
}

string Actor::getName(){
    return myName;
}

//Constructor for Player
Player:: Player(int posCol, int posRow): Actor(posCol, posRow, 20, shortSword(), 2, 2, 2, 0, '@', "Player")
{
    shortSword *myShortSword = new shortSword();
    Inventory.push_back(myShortSword); //starts with a Short Sword in their inventory
}

bool Player::addObjectToInventory(Object *obj){
    if (Inventory.size() < 25){
        Inventory.push_back(obj);
        return true; //return true if added
    }
    return false; //return false if inventory full
}

void Player::removeObjectFromInventory(Object* obj){
    Inventory.remove(obj); //removes an object (like a scroll when it destructs)
}

void Player::displayInventory(){
    char label = 'a';
    cout << "Inventory:" << endl;
    for (list<Object*>::iterator p = Inventory.begin(); p != Inventory.end(); p++){
        cout << label << ". " << (*p)->getName() << endl;
        label++; //increments the label to 'b', etc.
    }
    cout << endl;
}

bool Player::hasObjectInInventory(char c){
    int index = c - 'a'; //0-based, size is 1+ index
    if (Inventory.size() <= index){ //if the size of the array is less/equal to index, there is no object at that spot
        return false;
    }
    else{
        return true; //if the above condition is false, there is something there 
    }
}

Object* Player::getObjectFromInventory(char c){
    int index = c - 'a';
    auto iterator = Inventory.begin();
    advance(iterator, index);
    return *iterator; //when it finds the object, it returns a pointer to that object
}


//Constructor for Monster
Monster::Monster(int posCol, int posRow, int hitPoints, Weapon current, int armorPoints, int strength, int dexterity, int sleeptime, char icon, string name): Actor(posCol, posRow, hitPoints, current, armorPoints, strength, dexterity, sleeptime, icon, name), turnDoneVar(false)
{}

//the following functions help to make sure that the monster does not take its turn more than once
bool Monster::turnDone(){
    return turnDoneVar;
}

void Monster::resetTurnDone(){
    turnDoneVar = false;
}

void Monster::setTurnDone(){
    turnDoneVar = true;
}

//Constructor for Bogeymen
Bogeymen::Bogeymen(int posCol, int posRow) : Monster(posCol, posRow, randInt(5,10), shortSword(), 2, randInt(2, 3), randInt(2, 3), 0, 'B', "Bogeymen")
{}

//move function for Bogeymen
bool Bogeymen::monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game){
    int bogeyRow;
    int bogeyCol;
    getPos(&bogeyCol, &bogeyRow); //get the position of the bogeyman
    int rowDistance = playerRow - bogeyRow; //find the difference between rows
    if (rowDistance < 0){ //find the abs value
        rowDistance = (rowDistance * -1);
    }
    int colDistance = playerCol - bogeyCol; //find the difference between cols
    if (colDistance < 0){ //find the abs value
        colDistance = (colDistance * -1);
    }
    //if can smell (reach in 5 steps or less)
    if ((rowDistance + colDistance) <= 5){
        //if you can move in that direction, make a move (doesn't matter row/col)
        //if the player row is less than the bogeyman's, move up
        if (playerRow < bogeyRow){
            //check if empty
            if(game->isEmptyForMove(bogeyRow-1, bogeyCol)){
                *finalMoveRow = bogeyRow-1;
                *finalMoveCol = bogeyCol;
                return true;
            }
        }
        //if the row is more, then go down
        if (playerRow > bogeyRow){
            //check if empty
            if(game->isEmptyForMove(bogeyRow+1, bogeyCol)){
                *finalMoveRow = bogeyRow+1;
                *finalMoveCol = bogeyCol;
                return true;
            }
        }
        //if the col is less, move left
        if (playerCol < bogeyCol){
            //check if empty
            if(game->isEmptyForMove(bogeyRow, bogeyCol-1)){
                *finalMoveRow = bogeyRow;
                *finalMoveCol = bogeyCol-1;
                return true;
            }
        }
        //if the col is more, move right
        if (playerCol > bogeyCol){
            //check if empty
            if(game->isEmptyForMove(bogeyRow, bogeyCol+1)){
                *finalMoveRow = bogeyRow;
                *finalMoveCol = bogeyCol+1;
                return true;
            }
        }
    }
    return false; //don't move
}

//Constructor for Snakewomen
Snakewomen::Snakewomen(int posCol, int posRow) : Monster(posCol, posRow, randInt(3, 6), magicFang(), 3, 2, 3, 0, 'S', "Snakewomen")
{}

bool Snakewomen::monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game){
    int snakeRow;
    int snakeCol;
    getPos(&snakeCol, &snakeRow); //get the position of the snakewoman
    int rowDistance = playerRow - snakeRow; //find the difference between rows
    if (rowDistance < 0){ //find the abs value
        rowDistance = (rowDistance * -1);
    }
    int colDistance = playerCol - snakeCol; //find the difference between cols
    if (colDistance < 0){ //find the abs value
        colDistance = (colDistance * -1);
    }
    //if can smell (reach in 3 steps or less)
    if ((rowDistance + colDistance) <= 3){
    //if you can move in that direction, make a move (doesn't matter row/col)
    //if the player row is less than the snakewoman's, move up
        if (playerRow < snakeRow){
            //check if empty
            if(game->isEmptyForMove(snakeRow-1, snakeCol)){
                *finalMoveRow = snakeRow-1;
                *finalMoveCol = snakeCol;
                return true;
            }
        }
        //if the row is more, then go down
        if (playerRow > snakeRow){
            //check if empty
            if(game->isEmptyForMove(snakeRow+1, snakeCol)){
                *finalMoveRow = snakeRow+1;
                *finalMoveCol = snakeCol;
                return true;
            }
        }
        //if the col is less, move left
        if (playerCol < snakeCol){
            //check if empty
            if(game->isEmptyForMove(snakeRow, snakeCol-1)){
                *finalMoveRow = snakeRow;
                *finalMoveCol = snakeCol-1;
                return true;
            }
        }
        //if the col is more, move right
        if (playerCol > snakeCol){
            //check if empty
            if(game->isEmptyForMove(snakeRow, snakeCol+1)){
                *finalMoveRow = snakeRow;
                *finalMoveCol = snakeCol+1;
                return true;
            }
        }
    }
    return false; //don't move
}

//Constructor for Dragon
Dragon::Dragon(int posCol, int posRow) : Monster(posCol, posRow, randInt(20, 25), longSword(), 4, 4, 4, 0, 'D', "Dragon")
{}

bool Dragon::monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game){
    return false; //Dragondoesn't move
}

//Constructor for Goblin, initializes the maxSmellDistance
Goblin::Goblin(int posCol, int posRow, int maxSmellDistance) : Monster(posCol, posRow, randInt(15, 20), shortSword(), 1, 3, 1, 0, 'G', "Goblin"), maxSmellDist(maxSmellDistance)
{}

int Goblin::canGoblinSmell(int playerRow, int playerCol, int goblinRow, int goblinCol, int smellDist, Game* game, int* nextMoveRow, int* nextMoveCol, bool visited[MAX_ROWS][MAX_COLUMNS]){
    if (visited[goblinRow][goblinCol]){
        return 1000; //if the path has been visited, it is not valid (return a high number)
    }
    int localNextMoveRow, localNextMoveCol; //so that the value is not overwritten by each call
    //if smellDist becomes greater than the max, the goblin ran out of moves (counts moves)
    if (smellDist > maxSmellDist){
        return 1000; //means that this move is not possible
    }
    //if the goblin reaches the player, return the steps it took for them to get there
    if ((playerRow == goblinRow) && (playerCol == goblinCol)){
        return smellDist;
    }
    //if not a valid move, return false, only want this on second call onwards
    if (smellDist != 0){
        if (!(game->isEmptyForMove(goblinRow, goblinCol))){
            return 1000; //means that this move is not possible
        }
    }
    visited[goblinRow][goblinCol] = true;
    //find the smallest path possible (where smellDistance is the smallest)
    int min = canGoblinSmell(playerRow, playerCol, goblinRow-1, goblinCol, smellDist+1, game, nextMoveRow, nextMoveCol, visited);
    //change the local variables for the next move after each call, so that it ends up with the optimal next move
    localNextMoveRow = goblinRow-1;
    localNextMoveCol = goblinCol;
    int next = canGoblinSmell(playerRow, playerCol, goblinRow+1, goblinCol, smellDist+1, game, nextMoveRow, nextMoveCol, visited);
    if (next < min){
        min = next;
        localNextMoveRow = goblinRow+1;
        localNextMoveCol = goblinCol;
    }
    next = canGoblinSmell(playerRow, playerCol, goblinRow, goblinCol-1, smellDist+1, game, nextMoveRow, nextMoveCol, visited);
    if (next < min){
        min = next;
        localNextMoveRow = goblinRow;
        localNextMoveCol = goblinCol-1;
    }
    next = canGoblinSmell(playerRow, playerCol, goblinRow, goblinCol+1, smellDist+1, game, nextMoveRow, nextMoveCol, visited);
    if (next < min){
        min = next;
        localNextMoveRow = goblinRow;
        localNextMoveCol = goblinCol+1;
    }
    //check all possible paths to the player and return the smallest
    //set the nextMoveRow and nextMoveCol variables to the local variables (to return)
    *nextMoveRow = localNextMoveRow;
    *nextMoveCol = localNextMoveCol;
    visited[goblinRow][goblinCol] = false;
    return min; //return the smallest path (least steps taken)
}

bool Goblin::monsterMove(int playerRow, int playerCol, int* finalMoveRow, int* finalMoveCol, Game* game){
    //get the position of the goblin
    int gobRow, gobCol;
    getPos(&gobCol, &gobRow);
    bool visited[MAX_ROWS][MAX_COLUMNS];
    for (int i = 0; i < MAX_ROWS; i++){
        for (int j = 0; j < MAX_COLUMNS; j++){
            visited[i][j] = false; //always reset the visited grid to false before calling recursive function
        }
    }
    //check if the smallest is within the allowed steps, return true
    //pass in smellDist as 0, check if it is smaller than the max allowed
    if (canGoblinSmell(playerRow, playerCol, gobRow, gobCol, 0, game, finalMoveRow, finalMoveCol, visited) <= maxSmellDist){
        return true; //if the goblin smells, return true
    }
    return false; //else, return false 
}
