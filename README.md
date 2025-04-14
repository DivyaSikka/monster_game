# Grid-Based Game Simulation

This project is a grid-based game simulation written in C++. It features a turn-based system with actors (such as players and enemies), objects, and a dynamic game board composed of cells. The game demonstrates principles of object-oriented programming, encapsulation, and modular design.

## Features

- Actor system for players and non-player characters
- Game board constructed from individual 'Cel'` objects
- Object management (items, obstacles, etc.)
- Turn-based simulation loop
- Console-based interface
- Modular and maintainable code structure

## File Overview

| File | Description |
|------|-------------|
| 'main.cpp' | Entry point of the program. Manages game initialization and execution loop. |
| 'Game.h/cpp' | Contains the main game logic, including the game loop and turn mechanics. |
| 'Actor.h/cpp' | Defines and implements the behavior and properties of characters in the game. |
| 'Objects.h/cpp' | Defines various interactive and non-interactive objects that can exist on the game board. |
| 'Cell.h/cpp' | Represents individual grid cells and their states on the game board. |
| 'utilities.cpp | Contains helper functions used across various modules. |

## Build Instructions

### Requirements

- C++17 or later
- A C++ compiler such as `g++` or `clang++`
- Make (optional, but useful)

### Compilation

To compile manually:

'''bash
g++ -std=c++17 -o game main.cpp Game.cpp Actor.cpp Objects.cpp Cell.cpp utilities.cpp

Or, with a makefile:
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = main.cpp Game.cpp Actor.cpp Objects.cpp Cell.cpp utilities.cpp
OBJ = $(SRC:.cpp=.o)

game: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o game

Then run: 

 make
./game

## How to Play

- The game is played in the terminal.
- Players and enemies move and interact turn-by-turn.
- Objects can be picked up or interacted with depending on their type.
- More instructions can be added depending on your game rules.
