#include "runtime_headers/GameLoop.h"
#include "runtime_headers/Settings.h"
/*
    Description: Property...Property is a terminal-based take on Monopoly written entirely in C.
    Programmed by: Aaron Nicholas Lizardo Gumapac
    Last modified: January 25, 2022
    Version: V7
    [Acknowledgements: geekhack.org, computerphile, numberphile]
*/

/*
    This function begins the game and calls game functions.
    @param game the game package that contains all game information
    @returns a game package after the game is finished
*/
struct gamepkg playGame(struct gamepkg game){

    struct gamepkg lgame = game; // localize parameter in order to minimize errors

    fflush(stdout); // flush stdout to clear buffer
    printf("\nRandomizing first player!\n");
    lgame.state.activePlayer = getRandNum(1,2); // randomize the first player
    sleep_ms(500);
    fflush(stdout); // flush after sleep in order to avoid printf printing slowdowns

    char* strFirstPlayer = lgame.arrPlayerContainer[lgame.state.activePlayer - 1].name; // get the opening player's name

    printf("%s WILL GO FIRST!",strFirstPlayer); // print opening player's name
    fflush(stdout); // flush for printf
    sleep_ms(1000);

    clearbuff; // clearbuffer to ensure no inputs remain in the buffer 

    while(continueGame(lgame.state.SETTINGS.winsettings.winstate.winner == NONE))// check if the game should continue
    { 
        lgame = updateGame(lgame); // pass localized game onto updategame and receive an updated package that has ran all player events

        // update player values and change active player to the next
        updatePlayer(&lgame.state.activePlayer, &lgame.arrPlayerContainer[0].isJailed, &lgame.arrPlayerContainer[1].isJailed); 
    }

    return lgame; 
}

/*
    creates a struct gamepkg with initial game values and asks the users to configure
    settings and enter their names 
    @returns a game with intitial values
*/
struct gamepkg initializeGame(){

    struct gamestate initstate = initializeGamestate(); // initialize a gamestate variable with basic values
    struct Player* arrPlayers = malloc(512); // initialize a player array with size 512
    arrPlayers[0] = initializePlayer(); // create player 1 with initial values and store in arrPlayers[0]
    arrPlayers[1] = initializePlayer(); // create player 2 with initial values and store in arrPlayers[1]

    // create game variable that contains players and settings
    struct gamepkg game;
    game.state = initstate; // store initialstate into game.state
    game.arrPlayerContainer = arrPlayers; // store player array into arrPlayerContainer

    // return a game variable with initial values that has been through player customization
    return game;
}

int main()
{
    srand( (unsigned)time( NULL ) ) ;

    char choice;
    clear // clear the screen 
    printf("WELCOME TO MONOPOLY!\n");  // show opening message
    sleep_ms(1000); // sleep for ui flair
    // slow print that prints a character every 300-320 milliseconds
    print1d("oh wait.......",strlen("oh wait......."), 300,320); 
    sleep_ms(1500); // sleep for ui flair
    clear
    // slow print that prints a character every 200-210 milliseconds
    print1d("\nWELCOME TO PROPERTY",strlen("\nWELCOME TO PROPERTY"),200,210); 
    // slow print that prints a character every 230-240 milliseconds
    print1d("...PROPERTY!",strlen("...PROPERTY!"), 230,240); 
    // slow print that prints a character every 300-320 milliseconds
    print1d("\nyup...",strlen("\nyup..."),300,320);

    continuePrompt(); // ask the user to press enter to continue with the program

    struct gamepkg game = initializeGame();

    printf("\n[G] Start\n");
    printf("\n[S] Settings\n");
    printf("\n[E] Exit\n");

    char startingInputs[3] = "GSE";
    choice = handleInput(startingInputs,strlen(startingInputs));

    switch(choice){
        case 'E': // the player exits the game
            break;
        case 'S':
            struct settings config = settingsPrompt();
            game.state.SETTINGS = config;
        case 'G':
            do{
                // create pointer for player 1 name as strings are not mutable without more complex functions
                char** ptrP1Name = &game.arrPlayerContainer[0].name;
                fetchPlayerName(ptrP1Name);
                // create pointer for player 1 name as strings are not mutable without more complex functions
                char** ptrP2Name = &game.arrPlayerContainer[1].name;
                fetchPlayerName(ptrP2Name);
                game = playGame(game);
                // display the ending scree
                clear
                displayEndingScreen(game.state.SETTINGS.winsettings.winstate, 
                game.arrPlayerContainer[0], game.arrPlayerContainer[1]);
                continuePrompt();
                // prompt for a replay
                printf("Press [G] to play again\n");
                printf("Press [E] to exit\n");
                char exitInputs[2] = "GE";
                choice = handleInput(exitInputs, strlen(exitInputs));
             } while (choice == 'G');
            
    }
    char exitMsg[] = "\nNext time come back with better players!\n";
    print1d(exitMsg, strlen(exitMsg), 200, 200);
    return 0;
}
