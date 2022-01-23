#ifndef UIFX_H
#define UIFX_H

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../typedefs/evalTypes.h"
#include "../libdefs/NumTools.h"
#define clear system("clear");
#define newL printf("\n");

// performs a pauses the system by millliseconds

void sleep_ms(int milliseconds);

// prints a 2 dimensional array or img

void print2d(char* img[], size_t img_height);

// prints a string sequentially

void print1d(char str[], int strLength);

// returns a divider

char* createDivider(char divSymbol, int divLength);

// displays where the player currently is given their position on the board

void displayPos(int pos);

// returns the name of the property given its position on the board for all valid properties

char* getPropertyName(int propIndex);

// shows the balance update that is shown after every turn

void showBalanceUpdate(
                    float p1CurrentBalance,
                    float p1NewBalance,
                    char* p1Name,
                    float p2CurrentBalance,
                    float p2NewBalance,
                    char* p2Name
                    );
                
void showPersonalBalanceUpdate(float currentBalance, float newBalance);

// contextual ending screen that cognratulates the winner(s) according to their win conditions
void displayEndingScreen(struct winstate win, char* p1Name, char* p2Name);

#endif