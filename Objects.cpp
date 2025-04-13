//
//  Objects.cpp
//  Project3
//
//  Created by Divya Sikka on 5/19/24.
//

#include <stdio.h>
#include <iostream>
#include "Objects.h"
#include <string>
using namespace std;

Object::Object(string name, char icon) : myName(name), myIcon(icon)
{}

char Object::getIcon(){
    return myIcon;
}

string Object::getName(){
    return myName;
}

int getDamageAmount();

//Create Weapon constructor 
Weapon::Weapon(string name, string action, int dexterityBonus, int damageAmount) : Object(name, ')')
{
    myAction = action;
    myDexterityBonus = dexterityBonus;
    myDamageAmount = damageAmount;
}

int Weapon::getDexterityBonus(){
    return myDexterityBonus;
}

int Weapon::getDamageAmount(){
    return myDamageAmount;
}

string Weapon::getAction(){
    return myAction;
}

//Create all weapon types' constructors with their respective values
//Create a Mace Constructor
Mace::Mace() : Weapon("Mace", "swings mace at ", 0, 2)
{}

//Create a Short Sword Constructor
shortSword::shortSword() : Weapon("Short Sword", "slashes short sword at ", 0, 2)
{}

//Create a Long Sword Constructor
longSword::longSword() : Weapon("Long Sword", "swings long sword at ", 2, 4)
{}

//Create a Magic Axe Constructor
magicAxe::magicAxe() : Weapon("Magic Axe", "swings magic axe at ", 5, 5) //find action string 
{}

//Create a Magic Fangs of Sleep Constructor
magicFang::magicFang() : Weapon("Magic Fang", "strikes magic fangs at ", 3, 2)
{}

//Scroll constructor
Scroll::Scroll(string name) : Object(name, '?')
{}

//returns the value that the scrolls increase the player's points by depending on their name 
int Scroll::scrollMagic(){
    if (getName() == "Scroll of Enhance Armor"){
        return randInt(1,3);
    }
    if (getName() == "Scroll of Strength"){
        return randInt(1,3);
    }
    if (getName() == "Scroll of Enhance Health"){
        return randInt(3,8);                              
    }
    if (getName() == "Scroll of Dexterity"){
        return 1;
    }
    return 0;
}

