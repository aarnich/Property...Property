
#pragma once
#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "../typedefs/stateTypes.h"
#include "../typedefs/gameTypes.h"
#include "../libdefs/NumTools.h"

// returns the integer at index

int readStatekeyAtIndex(unsigned int STATEKEY, unsigned int index, int OFFSET);

// changes the statekey with value at index

int mutateStatekeyAtIndex(unsigned int STATEKEY, unsigned int index, unsigned int value, int OFFSET);

// returns the cost of the property purchase 

float getPropertyCost(int propIndex, float electricCost, float railCost);

// returns the cost of rent for the property

float getRent(int propIndex, int roll, float electricMulti, float railRent);

// saves the game

struct gamepkg saveGame(Player currentPlayer, int currentPlayerKey, Player opposingPlayer, int enemyPlayerKey, struct gamestate containedstate);

#endif