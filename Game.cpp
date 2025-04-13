// Game.cpp

#include "Game.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

//game constructor that sets the current level and the goblin smell distance
Game::Game(int goblinSmellDistance) : currentLvl(0), gobSmell(goblinSmellDistance)
{}

//helper function that checks if a space in the temple is empty for an actor to move
//ie. no other actor or wall is occupying the space
bool Game::isEmptyForMove(int row, int col){
    if ((temple[currentLvl][row][col]).actor() || (temple[currentLvl][row][col]).isWall()){
        return false;
    }
    return true;
}

//helper function to find an empty space in the maze from a starting point for a NONACTOR, returns the location of the row and col
void Game::findEmptySpaceNonActor(int* finalRow, int* finalCol){
    int randCol = randInt(MAX_COLUMNS);
    int randRow = randInt(MAX_ROWS);
    if ((temple[currentLvl][randRow][randCol].isEmpty()) || (temple[currentLvl][randRow][randCol].actor())){
        *finalRow = randRow;
        *finalCol = randCol;
    }
    else{
        //while there is something at that spot, keep regenerating random ints
        while ((temple[currentLvl][randRow][randCol].isWall()) || (temple[currentLvl][randRow][randCol].isStaircase()) || (temple[currentLvl][randRow][randCol].isIdol()) || (temple[currentLvl][randRow][randCol].object())){
            randCol = randInt(MAX_COLUMNS);
            randRow = randInt(MAX_ROWS);
        }
        *finalRow = randRow;
        *finalCol = randCol;
    }
}

//helper function to find an empty space in the maze from a starting point for an ACTOR, returns the location of the row and col
void Game::findEmptySpaceActor(int* finalRow, int* finalCol){
    int randCol = randInt(MAX_COLUMNS);
    int randRow = randInt(MAX_ROWS);
    if ((temple[currentLvl][randRow][randCol].isEmpty()) || (temple[currentLvl][randRow][randCol].object())){
        *finalRow = randRow;
        *finalCol = randCol;
    }
    else{
        //while there is something at that spot, keep regenerating random ints for the location
        while ((temple[currentLvl][randRow][randCol].actor()) || (temple[currentLvl][randRow][randCol].isWall())){
            randCol = randInt(MAX_COLUMNS);
            randRow = randInt(MAX_ROWS);
        }
        *finalRow = randRow;
        *finalCol = randCol;
    }
}

//helper function to place weapons on a level
Weapon* createRandomWeapon(){
    int weaponInt = randInt(1, 3); //3 weapons that can be randomly generated for lvls
    switch(weaponInt){
        case 1:
        {
            Mace* myMace = new Mace();
            return myMace;
            break;
        }
        case 2:
        {
            shortSword* myShort = new shortSword();
            return myShort;
            break;
        }
        case 3:
        {
            longSword* myLong = new longSword();
            return myLong;
            break;
        }
        default:
            return nullptr;
            break;
    }
}

Scroll* createRandomScroll(){
    int scrollInt = randInt(1, 4); //4 types of scrolls can be randomly placed on a lvl
    switch(scrollInt){
        case 1:
        {
            Scroll* armorScroll = new Scroll("Scroll of Enhance Armor");
            return armorScroll;
            break;
        }
        case 2:
        {
            Scroll* strengthScroll = new Scroll("Scroll of Strength");
            return strengthScroll;
            break;
        }
        case 3:
        {
            Scroll* healthScroll = new Scroll("Scroll of Enhance Health");
            return healthScroll;
            break;
        }
        case 4:
        {
            Scroll* dexScroll = new Scroll("Scroll of Dexterity");
            return dexScroll;
            break;
        }
        default:
            return nullptr;
            break;
    }
}

//a dragon can randomly drop ANY type of scroll, so this funciton includes the teleportation scroll
Scroll* createRandomScrollDragon(){
    int scrollInt = randInt(1, 5); //5 types of scrolls can be randomly dropped
    switch(scrollInt){
        case 1:
        {
            Scroll* armorScroll = new Scroll("Scroll of Enhance Armor");
            return armorScroll;
            break;
        }
        case 2:
        {
            Scroll* strengthScroll = new Scroll("Scroll of Strength");
            return strengthScroll;
            break;
        }
        case 3:
        {
            Scroll* healthScroll = new Scroll("Scroll of Enhance Health");
            return healthScroll;
            break;
        }
        case 4:
        {
            Scroll* dexScroll = new Scroll("Scroll of Dexterity");
            return dexScroll;
            break;
        }
        case 5:
        {
            Scroll* teleportationScroll = new Scroll("Scroll of Teleportation");
            return teleportationScroll;
            break;
        }
        default:
            return nullptr;
            break;
    }
}

Object* generateObject(){ //to generate random objects for the level creation
    int objInt = randInt(1, 2); //weapon is 1, scroll is 2
    if (objInt == 1){ //Generate a random type of weapon
        Weapon *myWeapon = createRandomWeapon();
        return myWeapon;
    }
    else{ //Generate a random type of scroll
        Scroll *myScroll = createRandomScroll();
        return myScroll;
    }
}

//This function randomly generates monsters depending on the current level
Monster* Game::generateMonster(int monsterRow, int monsterCol){
    int monInt = 0;
    if (currentLvl == 0 || currentLvl == 1){
        monInt = randInt(1, 2); //2 types of monsters on this lvl
    }
    if (currentLvl == 2){
        monInt = randInt(1, 3); //3 types of monsters on this lvl
    }
    if (currentLvl == 3 || currentLvl == 4){
        monInt = randInt(1, 4); //4 types of monsters on this lvl
    }
    switch (monInt) {
        case 1:
        {
            Goblin* myMon = new Goblin(monsterCol, monsterRow, gobSmell);
            return myMon;
            break;
        }
        case 2:
        {
            Snakewomen* myMon = new Snakewomen(monsterCol, monsterRow);
            return myMon;
            break;
        }
        case 3:
        {
            Bogeymen* myMon = new Bogeymen(monsterCol, monsterRow);
            return myMon;
            break;
        }
        case 4:
        {
            Dragon* myMon = new Dragon(monsterCol, monsterRow);
            return myMon;
            break;
        }
        default:
            return nullptr;
            break;
    }
}

bool Game::ifNextToPlayer(Monster* myMonster){ //checks if monster and player are next to each other, helps with the attack functionality
    int monsterRow;
    int monsterCol;
    myMonster->getPos(&monsterCol, &monsterRow);
    int playerRow;
    int playerCol;
    myPlayer->getPos(&playerCol, &playerRow);
    //check for same row diff column (next to each other)
    if ((monsterRow == playerRow) && (monsterCol == (playerCol-1))){
        return true;
    }
    if ((monsterRow == playerRow) && (monsterCol == (playerCol+1))){
        return true;
    }
    //check for diff row same column (next to each other)
    if ((monsterRow == (playerRow+1)) && (monsterCol == playerCol)){
        return true;
    }
    if ((monsterRow == (playerRow-1)) && (monsterCol == playerCol)){
        return true;
    }
    return false; //return false otherwise (not next to monster)
}

//this function is called whenevever it's the monster's turn to make a move
void Game::monsterMove(){
    //go through and reset all the monsters turnDone() function at the beginning of each turn
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            //check if an actor then check if it's a monster
            if ((temple[currentLvl][i][j]).actor()){
                Actor* myActor = (temple[currentLvl][i][j]).getActor();
                if (dynamic_cast<Monster*>(myActor)){ //check if monster
                    Monster* myMonster = dynamic_cast<Monster*>(myActor);
                    myMonster->resetTurnDone(); //reset
                }
            }
        }
    }
    //go through and find the first monster to take a turn
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            //check if an actor then check if it's a monster
            if ((temple[currentLvl][i][j]).actor()){
                Actor* myActor = (temple[currentLvl][i][j]).getActor();
                Monster* myMonster = dynamic_cast<Monster*>(myActor);
                if (myMonster && (!(myMonster->turnDone())) && (myMonster->getSleepTime() == 0)){
                    myMonster->setTurnDone(); //set their turn to done so they don't go again
                    //before each turn a dragon takes, it can regain one hit point
                    if (myMonster->getName() == "Dragon"){
                        if (trueWithProbability(0.1)){
                            myMonster->setHitPoints(1); //add a hit point
                        }
                    }
                    if (ifNextToPlayer(myMonster)){ //if next to the player, attack
                        Weapon* monsterWeapon = myMonster->getCurrentWeapon();
                        //calculate if the monster hits/doesn't
                        int monsterPoints = (myMonster->getDexterity()) + (monsterWeapon->getDexterityBonus());
                        int playerPoints = (myPlayer->getDexterity()) + (myPlayer->getArmorPoints());
                        if ((randInt(1, monsterPoints)) >= (randInt(1, playerPoints))){
                            //attacker (monster) hits defender (player)
                            //decrease player hit points
                            int damagePoints = randInt(0, (myMonster->getStrength() + monsterWeapon->getDamageAmount() - 1));
                            myPlayer->setHitPoints(-1*(damagePoints));
                            //if the player's hit points are <= 0, kill the player
                            if (myPlayer->getHitPoints() <= 0){
                                cout << myMonster->getName() << " " << monsterWeapon->getAction() << "player dealing a final blow." << endl;
                                //end the game
                                exit(0);
                            }
                            //if the weapon is a magic fang, there is a diff action and message
                            if (monsterWeapon->getName() == "Magic Fang"){
                                if (trueWithProbability(0.2)){
                                    if (myPlayer->getSleepTime() > 0){
                                        int current = myPlayer->getSleepTime();
                                        int newSleep = std::max(current, randInt(2, 6));
                                        myPlayer->setSleepTime(newSleep);
                                    }
                                    else{
                                        myPlayer->setSleepTime(randInt(2,6));
                                    }
                                    //if puts to sleep, display this message
                                    cout << myMonster->getName() << " " << monsterWeapon->getAction() << "player and hits, putting the player to sleep." << endl;
                                }
                                //else, just display that the fangs hit the player
                                else{
                                    cout << myMonster->getName() << " " << monsterWeapon->getAction() << "player and hits." << endl;
                                }
                            }
                            else{
                                cout << myMonster->getName() << " " << monsterWeapon->getAction() << "player and hits." << endl;
                            }
                        }
                        else{ //else, the monster misses
                            cout << myMonster->getName() << " " << monsterWeapon->getAction() << "player and misses." << endl;
                        }
                    }
                    //if not next to the player, make a move
                    else{
                        //get location of player
                        int playerRow;
                        int playerCol;
                        myPlayer->getPos(&playerCol, &playerRow);
                        int finalMoveRow, finalMoveCol;
                        //call the monster move function to get their final coordinates
                        if (myMonster->monsterMove(playerRow, playerCol, &finalMoveRow, &finalMoveCol, this)){
                            //move the monster to that location
                            (temple[currentLvl][finalMoveRow][finalMoveCol]).setActor(myActor);
                            (temple[currentLvl][i][j]).setActor(nullptr);
                            myActor->setPos(finalMoveCol, finalMoveRow);
                            clearScreen();
                            displayScreen(currentLvl);
                        }
                    }
                }
                else{
                    if (myMonster){
                        myMonster->decrementSleepTime();
                    }
                }
            }
        }
    }
}

//helper function to create rooms, removes walls at certain coordinates
void Game::createRectangle(int topLeftRow, int topLeftCol, int width, int height){
    for (int i = topLeftRow; i < height+topLeftRow; i++){
        for (int j = topLeftCol; j < width+topLeftCol; j++){
            temple[currentLvl][i][j].removeWall();
        }
    }
}

//helper function to create hallways between the rooms
bool Game::createTunnel(int previousStartRow, int previousStartCol, int previousHeight, int previousWidth, int startRow, int startCol, int height, int width){
    int previousEndRow = previousStartRow + previousHeight - 1;
    int endRow = startRow + height - 1;
    // Find the common row range
    int overlapStart = std::max(previousStartRow, startRow);
    int overlapEnd = std::min(previousEndRow, endRow);
    //find common row between the two rectangles
    if (overlapStart <= overlapEnd){
        int commonRow = randInt(overlapStart, overlapEnd);
        int tunnelStartCol = std::min(previousStartCol + previousWidth, startCol);
        int tunnelEndCol = std::max(previousStartCol + previousWidth, startCol);
        int tunnelWidth = tunnelEndCol - tunnelStartCol + 1;
        //create a rectangle for the hallway
        createRectangle(commonRow, tunnelStartCol, tunnelWidth, 1);
        return true;
    }
    //if no common row, return false
    return false;
}

//helper function that calls createRectangle() and createTunnel() to make the rooms
void Game::createRooms(){
    //create parameters for max height and width and generate random integers for starting
    int maxHeight = 15;
    int maxWidth = 20;
    int startRow = randInt(3, (MAX_ROWS-maxHeight - 2));
    int columnStepSize = 5;
    int startCol = randInt(2, columnStepSize);
    bool first = true; //set this to true for the first time (don't need a hallway)
    //initialize variables to pass to the createTunnel() function
    int previousStartRow = 0, previousStartCol = 0, previousWidth = 0, previousHeight = 0;
    //while it doesn't reach the end, keep creating rooms and connecting them
    while (startCol < (MAX_COLUMNS-columnStepSize - 2)){
        int width = randInt(3, maxWidth);
        int height = randInt(3, maxHeight);
        //check to make sure that it doesn't reach the end of the grid
        if ((startRow + height) >= MAX_ROWS-1){
            height = MAX_ROWS - startRow - 2;
        }
        if ((startCol + width) >= MAX_COLUMNS-1){
            width = MAX_COLUMNS - startCol - 2;
        }
        //first time, just create one rectangle
        if (first){
            createRectangle(startRow, startCol, width, height);
            previousStartRow = startRow;
            previousStartCol = startCol;
            previousWidth = width;
            previousHeight = height;
            startRow = randInt(3, (MAX_ROWS-maxHeight -2));
            startCol += (randInt(2, columnStepSize) + width);
        }
        //after, that, connect the two rectangles (if not possible, generate a new rectangle)
        if (!first){
            if (createTunnel(previousStartRow, previousStartCol, previousHeight, previousWidth, startRow, startCol, height, width)){
                createRectangle(startRow, startCol, width, height);
                previousStartRow = startRow;
                previousStartCol = startCol;
                previousWidth = width;
                previousHeight = height;
                startRow = randInt(3, (MAX_ROWS-maxHeight -1));
                startCol += (randInt(2, columnStepSize) + width);
            }
            else{
                startRow = randInt(3, (MAX_ROWS-maxHeight -1));
            }
        }
        first = false; //after the first rectangle created, set this to false
    }
}

//function to create all the levels, takes a parameter for the lvl
void Game::createLevel(int lvl){
    //intialize everything to 'X' and inside to spaces (for walls)
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            temple[lvl][i][j].setWall();
        }
    }
    //then create rooms, taking away the walls at these spots
    createRooms();
    //only create a new player if its the first level of the game
    if (lvl == 0){
        int myRow;
        int myCol;
        findEmptySpaceActor(&myRow, &myCol);
        myPlayer = new Player(myCol, myRow);
        temple[lvl][myRow][myCol].setActor(myPlayer); //add a NEW player
    }
    
    else{
        int myRow;
        int myCol;
        findEmptySpaceActor(&myRow, &myCol);
        myPlayer->setPos(myCol, myRow);
        temple[lvl][myRow][myCol].setActor(myPlayer); //else, add old player
    }
    
    if (lvl != 4){ //if the level is not 4, add a staircase
        int stairwayRow;
        int stairwayCol;
        findEmptySpaceNonActor(&stairwayRow, &stairwayCol);
        temple[lvl][stairwayRow][stairwayCol].setStaircase();
    }
    
    if (lvl == 4){ //place the golden idol if it is level 4
        int stairwayRow;
        int stairwayCol;
        findEmptySpaceNonActor(&stairwayRow, &stairwayCol);
        temple[lvl][stairwayRow][stairwayCol].setIdol();
    }
    
    int numObjects = randInt(2, 3);
    int objRow;
    int objCol;
    while (numObjects > 0){ //number is either 2 or 3
        findEmptySpaceNonActor(&objRow, &objCol); //generate the object
        Object* obj = generateObject();//find space for the object
        temple[lvl][objRow][objCol].setObject(obj); //place the object
        numObjects--;
    }
    
    int numMonsters = randInt(2, 5*(lvl+1)+1);
    int monRow;
    int monCol;
    while (numMonsters > 0){ //number is unknown
        findEmptySpaceActor(&monRow, &monCol); //find space for the monster
        Monster* mon = generateMonster(monRow, monCol); //generate the monster
        temple[lvl][monRow][monCol].setActor(mon); //place the monster
        numMonsters--;
    }
    
    displayScreen(lvl); //display the level
}

void Game::monsterDie(int newRow, int newCol, Monster* myMonster, Weapon* playerWeapon){
    //print that the monster dies
    cout << "Player " << playerWeapon->getAction() << " " << myMonster->getName() << " dealing a final blow." << endl;
    //remove the monster from the grid
    (temple[currentLvl][newRow][newCol]).setActor(nullptr);
    //one in 10 chance the monster will drop something depending on what it is
    //Bogeymen may drop a magic axe when they die
    if (myMonster->getName() == "Bogeymen"){
        if (trueWithProbability(0.1) && (!(temple[currentLvl][newRow][newCol]).object())){
            magicAxe* dropped = new magicAxe();
            (temple[currentLvl][newRow][newCol]).setObject(dropped);
        }
    }
    if (myMonster->getName() == "Dragon"){
        //dragons always drop a scroll of some kind when they die
        Scroll *newScroll = createRandomScrollDragon();
        (temple[currentLvl][newRow][newCol]).setObject(newScroll);
    }
    if (myMonster->getName() == "Snakewomen"){
        //snakewomen may drop their magic fangs of sleep when they die
        if (trueWithProbability(0.33) && (!(temple[currentLvl][newRow][newCol]).object())){
            magicFang* dropped = new magicFang();
            (temple[currentLvl][newRow][newCol]).setObject(dropped);
        }
    }
    //goblins may either drop magic axe or magic fangs
    if (myMonster->getName() == "Goblin"){
        if (trueWithProbability(0.33) && (!(temple[currentLvl][newRow][newCol]).object())){
            int choice = randInt(1,2);
            switch (choice){
                case 1:
                {
                    magicAxe* dropped = new magicAxe();
                    (temple[currentLvl][newRow][newCol]).setObject(dropped);
                    break;
                }
                case 2:
                {
                    magicFang* dropped = new magicFang();
                    (temple[currentLvl][newRow][newCol]).setObject(dropped);
                    break;
                }
                default:
                    break;
            }
        }
    }
}

//helper function for the player to take it's turn
void Game::moveIntoCell(int newRow, int newCol){
    int myRow;
    int myCol;
    (*myPlayer).getPos(&myCol, &myRow); //save the location of the old actor
    //if it isn't an actor or a wall, move (update player and temple locations)
    if ((temple[currentLvl][newRow][newCol]).isWall()){
        clearScreen();
        displayScreen(currentLvl);
        return; // do nothing
    }
    //if no actor, then move into that spot
    if(!(temple[currentLvl][newRow][newCol]).actor()){
        (*myPlayer).setPos(newCol, newRow);
        (temple[currentLvl][myRow][myCol]).setActor(nullptr);
        (temple[currentLvl][newRow][newCol]).setActor(myPlayer);
        clearScreen();
        displayScreen(currentLvl);
    }
    //if there's already an actor, attack
    else{
        //get the monster that's in the cell
        Actor* myActor = (temple[currentLvl][newRow][newCol]).getActor();
        if (dynamic_cast<Monster*>(myActor)){
            Monster* myMonster = dynamic_cast<Monster*>(myActor);
            Weapon* playerWeapon = myPlayer->getCurrentWeapon();
            int playerPoints = (myPlayer->getDexterity()) + (playerWeapon->getDexterityBonus());
            int monsterPoints = (myMonster->getDexterity()) + (myMonster->getArmorPoints());
            clearScreen();
            displayScreen(currentLvl);
            if ((randInt(1, playerPoints)) >= (randInt(1, monsterPoints))){
                //attacker (player) hits defender (monster)
                int damagePoints = randInt(0, (myPlayer->getStrength() + playerWeapon->getDamageAmount() - 1));
                myMonster->setHitPoints(-1*(damagePoints));
                if (myMonster->getHitPoints() <= 0){ //if the monster's hit points are <= 0, kill the monster
                    monsterDie(newRow, newCol, myMonster, playerWeapon);
                }
                //if magic fang, set sleep time for monster and print a different message
                else if (playerWeapon->getName() == "Magic Fang"){
                    if (trueWithProbability(0.2)){
                        if (myMonster->getSleepTime() > 0){
                            int current = myMonster->getSleepTime();
                            int newSleep = std::max(current, randInt(2, 6));
                            myMonster->setSleepTime(newSleep);
                        }
                        else{
                            myMonster->setSleepTime(randInt(2,6));
                        }
                        //if put to sleep, print that it put the monster to sleep
                        cout << "Player " << playerWeapon->getAction() << myMonster->getName() <<" and hits, putting the " << myMonster->getName() << "to sleep." << endl;
                    }
                    else{ //probability not true, only changes hit points
                        cout << "Player " << playerWeapon->getAction() << myMonster->getName() <<" and hits." << endl;
                    }
                }
                //if it's any other type of weapon
                else{
                    cout << "Player " << playerWeapon->getAction() << myMonster->getName() <<" and hits." << endl;
                }
            }
            else{
                //else, it misses
                cout << "Player " << playerWeapon->getAction() << myMonster->getName() <<" and misses." << endl;
            }
        }
    }
}

void Game::scrollAction(Scroll* myScroll, Player* myPlayer){
    //get the amount to increase by
    int increase = myScroll->scrollMagic();
    //call the correct function on myPlayer
    if (myScroll->getName() == "Scroll of Enhance Armor"){
        myPlayer->setArmorPoints(increase);
    }
    if (myScroll->getName() == "Scroll of Strength"){
        myPlayer->setStrength(increase);
    }
    if (myScroll->getName() == "Scroll of Enhance Health"){
        myPlayer->increaseMaxHitPoints(increase);
    }
    if (myScroll->getName() == "Scroll of Dexterity"){
        myPlayer->setDexterity(increase);
    }
    if (myScroll->getName() == "Scroll of Teleportation"){
        int myRow;
        int myCol;
        myPlayer->getPos(&myCol, &myRow);
        (temple[currentLvl][myRow][myCol]).setActor(nullptr); //make sure no one there
        findEmptySpaceActor(&myRow, &myCol); //reset location
        myPlayer->setPos(myCol, myRow); //set new location
    }
}

void Game::executeCommand(const char c){ //function that executes the command from the user
    int myRow;
    int myCol;
    (*myPlayer).getPos(&myCol, &myRow);
    if(myPlayer->getSleepTime() == 0){
        switch(c){
                //move functions for arrow up/down/left/right
            case ARROW_LEFT:
            {
                moveIntoCell(myRow, (myCol-1));
                break;
            }
            case ARROW_RIGHT:
            {
                moveIntoCell(myRow, (myCol+1));
                break;
            }
            case ARROW_UP:
            {
                moveIntoCell((myRow-1), myCol);
                break;
            }
            case ARROW_DOWN:
            {
                moveIntoCell((myRow+1), myCol);
                break;
            }
            case 'g': //pick up the item
            {
                //if standing on golden idol, player wins
                if ((temple[currentLvl][myRow][myCol]).isIdol()){
                    cout << "You won the game!" << endl;
                    exit(0); //end the game
                }
                //if standing on an object, pick it up from this command
                else if ((temple[currentLvl][myRow][myCol]).object()){
                    Object* myObj = (temple[currentLvl][myRow][myCol]).getObject();
                    (*myPlayer).addObjectToInventory(myObj);
                    if (dynamic_cast<Weapon*>(myObj)){ //check if weapon
                        cout << "You pick up a " << myObj->getName() <<endl;
                    }
                    if (dynamic_cast<Scroll*>(myObj)){
                        cout << "You pick up a scroll called " << myObj->getName() << endl;
                    }
                    //remove it from the floor
                    (temple[currentLvl][myRow][myCol]).setObject(nullptr);
                }
                break;
            }
            case 'w':
            {
                clearScreen();
                (*myPlayer).displayInventory();
                char weaponLetter = getCharacter();
                //if inventory includes this weapon, change it to current
                if ((*myPlayer).hasObjectInInventory(weaponLetter)){
                    Object* myObj = myPlayer->getObjectFromInventory(weaponLetter);
                    //check if it's a weapon
                    if (dynamic_cast<Weapon*>(myObj)){
                        Weapon* myWeapon = dynamic_cast<Weapon*>(myObj);
                        myPlayer->changeCurrentWeapon(myWeapon);
                        clearScreen();
                        displayScreen(currentLvl);
                        cout << "You are weilding " <<  myWeapon->getName() << endl;
                    }
                    //if it's a scroll then doesn't work
                    else{
                        clearScreen();
                        displayScreen(currentLvl);
                        cout << "You can't weild " <<  myObj->getName() << endl;
                    }
                }
                else{ //if not a valid letter of anything in inventory, display game again
                    clearScreen();
                    displayScreen(currentLvl);
                }
                break;
            }
            case 'r':
            {
                clearScreen();
                (*myPlayer).displayInventory();
                char scrollLetter = getCharacter();
                //if have that letter in investory
                if ((*myPlayer).hasObjectInInventory(scrollLetter)){
                    //get the object from that spot
                    Object* myObj = myPlayer->getObjectFromInventory(scrollLetter);
                    //check if it's a scroll
                    if (dynamic_cast<Scroll*>(myObj)){
                        Scroll* myScroll = dynamic_cast<Scroll*>(myObj);
                        scrollAction(myScroll, myPlayer); //scroll performs magic
                        clearScreen();
                        displayScreen(currentLvl);
                        cout << "You read the scroll called " << myScroll->getName() << endl;
                        myPlayer->removeObjectFromInventory(myScroll); //self-destruct
                    }
                    else{ //not a scroll
                        clearScreen();
                        displayScreen(currentLvl);
                        cout << "You can't read a " << myObj->getName() << endl;
                    }
                }
                else{ //if not a valid letter of anything in inventory, display game again
                    clearScreen();
                    displayScreen(currentLvl);
                }
                break;
            }
            case 'i': //displays the inventory
            {
                clearScreen();
                (*myPlayer).displayInventory();
                getCharacter();
                break;
            }
                //case for going down a staircase to the next level
            case '>':
            {
                if ((temple[currentLvl][myRow][myCol]).isStaircase()){
                    currentLvl++; //increments the level, went down the staircase
                    createLevel(currentLvl);
                }
                break;
            }
                //case for cheating
            case 'c':
            {
                myPlayer->cheatStrength(); //sets strength to 9
                myPlayer->cheatHitPoints(); //sets max hit points to 50
                clearScreen();
                displayScreen(currentLvl);
                break;
            }
            default:
                break;
        }
    }
    else{
        clearScreen();
        displayScreen(currentLvl);
        myPlayer->decrementSleepTime();
    }
    monsterMove(); //monster then takes its turn
}

void Game::displayScreen(int lvl){
    //print temple array
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLUMNS; ++j) {
            cout << temple[lvl][i][j].printCell(); //this prints the icon at that spot
        }
        cout << endl;
    }
    cout << "Level: " << lvl << ", Hit Points: " << (*myPlayer).getHitPoints() << ", Armor: " << (*myPlayer).getArmorPoints() << ", Strength: " << (*myPlayer).getStrength() << ", Dexterity: " << (*myPlayer).getDexterity() << endl;
}

void Game::play()
{
    createLevel(currentLvl); //creates the level
    cout << "Press q to exit game." << endl;
    char command = getCharacter();
    while (command != 'q'){
        executeCommand(command);
        //before each command there is a 1 in 10 chance that the player gains 1 hit point, up to the player's max
        if (trueWithProbability(0.1)){
            myPlayer->setHitPoints(1);
        }
        command = getCharacter(); //gets a new char from the user
    }
}

