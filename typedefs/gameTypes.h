/*
    Description: gameTypes.h is a header file containing necessary definitions for game entities
    Author: Aaron Nicholas Lizardo Gumapac
*/

#pragma once
#ifndef GAMETYPES_H
#define GAMETYPES_H
#include <stdbool.h>

// defines the player type
typedef struct Player
{
    unsigned int jailedCounter;
    unsigned int pos;
    float balance;
    char* name;
    bool isJailed;
    bool isBankrupt;
}Player;

#endif