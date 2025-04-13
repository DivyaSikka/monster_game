//
//  Objects.h
//  Project3
//
//  Created by Divya Sikka on 5/19/24.
//

#ifndef Objects_h
#define Objects_h

#include <string>
#include <iostream>
#include "utilities.h"
using namespace std;


class Object{
public:
    Object(string name, char icon); 
    virtual char getIcon();
    virtual string getName();
    virtual ~Object() = default; //destructor
private:
    string myName;
    char myIcon;
};

//weapon, a type of object
class Weapon : public Object{
public:
    Weapon(string name, string action, int dexterityBonus, int damageAmount);
    int getDexterityBonus(); //returns dexterity bonus of weapon
    int getDamageAmount(); //returns damage amount of weapon
    string getAction(); //returns the action string of weapon
private:
    string myAction;
    int myDexterityBonus;
    int myDamageAmount;
};

//different types of weapons
class Mace : public Weapon{
public:
    Mace();
};

class shortSword : public Weapon{
public:
    shortSword();
};

class longSword : public Weapon{
public:
    longSword();
};

class magicAxe : public Weapon{
public:
    magicAxe();
};

class magicFang : public Weapon{
public:
    magicFang();
};

//scroll, a type of weapon
class Scroll : public Object{
public:
    Scroll(string name);
    int scrollMagic(); //returns the number that the scroll increases the player's points by
};



#endif /* Objects_h */
