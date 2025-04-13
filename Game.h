// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include "Cell.h"
#include "Actor.h"
#include "utilities.h"

//Class that brings the game together
class Game
{
public:
    Game(int goblinSmellDistance); //constructor
    void play();
    bool isEmptyForMove(int row, int col); //checks if a certain space is empty
private:
    Cell temple[MAX_LEVELS][MAX_ROWS][MAX_COLUMNS]; //temple variable, 2D array made of cells
    void createLevel(int lvl); //creates each level depending on the lvl passed in
    void findEmptySpaceNonActor(int* finalRow, int* finalCol); //finds the empty space for a nonactor
    void findEmptySpaceActor(int* finalRow, int* finalCol); //finds the empty space for an actor
    //functions for the player's turn
    void executeCommand(const char c);
    void moveIntoCell(int newRow, int newCol);
    void displayScreen(int lvl); //displays the level
    void scrollAction(Scroll* myScroll, Player* myPlayer); //function that carries out scroll magic
    void monsterMove(); //function for monster's move
    bool ifNextToPlayer(Monster* myMonster); //checks if a monster is next to the player
    //functions to create the rooms at execution
    bool createTunnel(int previousStartRow, int previousStartCol, int previousHeight, int previousWidth, int startRow, int startCol, int height, int width);
    void createRectangle(int topLeftRow, int topLeftCol, int width, int height);
    void createRooms();
    //function that is called when a monster dies
    void monsterDie(int newRow, int newCol, Monster* myMonster, Weapon* playerWeapon);
    //generates monsters for the creation of the levels 
    Monster* generateMonster(int monsterRow, int monsterCol);
    //private vars
    Player* myPlayer;
    int currentLvl;
    int gobSmell;
};
#endif // GAME_INCLUDED
