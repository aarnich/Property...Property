/*
    Description: A collection of functions that dictate behaviours strictly related to the player
    Author: Aaron Nicholas Lizardo Gumapac
*/

#include "../libdefs/PlayerEvents.h"

// player roll dice event

/*
    This function rolls the dice for the player and returns the corresponding value
    @param diceRange describes the minimum and maximum dice value
    @returns value of the dice roll
*/
int rollDice(range diceRange)
{
    printf("\nTHE DICE SPINS IN THE AIR!🎲\n");
    char* diceImg[8] = { // set of chars that make up an image of the dice 
        "   _______",
        "  /\\ o o o\\",
        " /o \\ o o o\\_______",
        "<    >------>   o /|",
        " \\ o/  o   /_____/o|",
        "  \\/______/     |oo|",
        "        |   o   |o/",
        "        |_______|/"
    };
    print2d(diceImg,8); // print dice
    return getRandNum(diceRange.min, diceRange.max);
}

/*
    Returns a string that contains all the names of the player's properties
    @param STATEKEY the 9 digit integer that tracks all properties on the board
    @param OFFSET the OFFSET used to decrypt the statekey
    @param playerID the ID (1 or 2) of the player being checked
    @returns the string of all the player's properties
*/
char* getAllPlayerProperties(unsigned int STATEKEY, unsigned int OFFSET, unsigned int playerID){
    char* strPlayerProperties = malloc (512);
    for (size_t i = 1; i <= 9; i++)
    {
        int indicator = readStatekeyAtIndex(
            STATEKEY, i,
            OFFSET
            );
        if(playerOwns(playerID, indicator)){
            strcat(strPlayerProperties," ");
            strcat(strPlayerProperties, getPropertyName(i));
        }
    }
    return strPlayerProperties;
}


/*
    Tells the game whether the player owns any properties at all. It checks every digit in the statekey
    and runs a simple boolean function.
    @param STATEKEY the 9 digit integer that tracks all properties on the board
    @param OFFSET the OFFSET used to decrypt the statekey
    @param playerID the ID (1 or 2) of the player being checked
    @returns boolean value that determines whether the player owns any properties
*/
bool playerOwnsProperties(unsigned int STATEKEY, unsigned int OFFSET, unsigned int playerID){
    for (size_t i = 1; i <= 9; i++)
    {
        if(playerOwns(playerID,readStatekeyAtIndex(STATEKEY,i,OFFSET))){
            return true;
        }
    }
    return false;
}

// a dialogue prompt that asks a question that is answered by yes or no

/*
    Asks the player a yes or no question supplied by strDialogueMsg and prompts for an answer
    @params strDialogueMsg string of the question displayed
    @returns boolean value that tells you the player's choice
*/
bool playerDialogue(char* strDialogueMsg){
    printf("%s Y/N: ",strDialogueMsg);
    char c;
    scanf(" %c",&c);
    getchar();
    switch(c){
        case 'y':
        case 'Y':
            return true;
            break;
        case 'n':
        case 'N':
            return false;
            break;
        default:
            printf("\ninvalid input");
            return playerDialogue("\n");
    }
}


/*
    Tells the game whether the player described in playerID owns the current property
    @params playerID which player is being checked (player 1 or player 2)
    @params propIndicator the value of the property as described by the statekey
    @returns boolean value that depends on the player's ownership of the property
*/
bool playerOwns(unsigned int playerID, int propIndicator){

    if(propIndicator == 5) // if the current property cannot be owned
        return false;
    if((playerID % 2 == propIndicator % 2) && propIndicator != 0) // if the property is even/odd and is not owned by the bank
        return true;

    return false; // false by default
}

/*
    displays the winning player's stats after the game has finished
    @params PLAYER the structure containing all of the winning player's information
    @params STATEKEY 9 digit integer holding all information regarding the positions on the board
    @params playerID integer value used to parse the statekey in order to get all of the winning player's properties
*/
void displayPlayerEndingStats(Player PLAYER, unsigned playerID, unsigned int STATEKEY){
    printf("\n[%s's STATS]\n",PLAYER.name);
    printf("Finishing Balance: %.2f\n", PLAYER.balance);
    printf("Remaining Properties: %s\n",getAllPlayerProperties(STATEKEY, -4, playerID));
    printf("Times Jailed: %d\n",PLAYER.jailedCounter);
}

/*
    returns a valid sell choice given the statekey and the current player's ID
    @params playerID integer value of the current player's ID (1 or 2)
    @params STATEKEY 9 digit integer holding ownership statuses
    @returns which property the player would like to sell
*/
int getPlayerSellChoice(unsigned int STATEKEY, unsigned int OFFSET, unsigned int playerID){
    int sellChoice = getValidInteger("\nEnter property to be sold\n");
    bool bInRange = true;
    do
    {
        range stateindexes;
        stateindexes.min = 1;
        stateindexes.max = 9;
        bool isInRange = checkIfInRange(sellChoice,stateindexes);
        if(!isInRange){
            printf("\ninvalid input");
            sellChoice = getValidInteger("\n");
        }
    } while (!bInRange);
    if(playerOwns(playerID,readStatekeyAtIndex(STATEKEY,sellChoice,OFFSET))){
        return sellChoice;
    }
    printf("\nYou do not own that property\n");
    return getPlayerSellChoice(STATEKEY, OFFSET, playerID);
}

/*
    Method that changes the player's name given its pointer
    @param ptrPlayerName pointer to the player's name (string)
*/
void fetchPlayerName(char** ptrPlayerName){
    printf("Enter name: ");
    char* initName = malloc(256);
    scanf("%s",initName);
    if(initName[0] == ' '){
        printf("\n invalid name\n");
        return fetchPlayerName(ptrPlayerName);
    }
    strcpy(*ptrPlayerName,initName);
    free(initName);
}