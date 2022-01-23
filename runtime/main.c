#include "runtime_headers/GameLoop.h"
#include "runtime_headers/Settings.h"
/*
    Description: Property...Property is a terminal-based take on Monopoly written entirely in C.
    Programmed by: Aaron Nicholas Lizardo Gumapac
    Last modified: January 19, 2022
    Version: V3
    [Acknowledgements: geekhack.org, computerphile, numberphile]
*/

/*
    This function begins the game and calls game functions.
    @params game the game package that contains all game information
    @returns a game package after the game is finished
*/
struct gamepkg playGame(struct gamepkg game){

    struct gamepkg lgame = game; // localize parameter in order to minimize errors

    fflush(stdout);
    printf("\nRandomizing first player!\n");
    sleep_ms(500);
    fflush(stdout);

    lgame.state.activePlayer = getRandNum(1,2);

    char* strFirstPlayer = lgame.arrPlayerContainer[lgame.state.activePlayer - 1].name;
    printf("%s WILL GO FIRST!",strFirstPlayer);
    fflush(stdout);
    sleep_ms(1000);

    clearbuff;
    while(continueGame(lgame.state.SETTINGS.winsettings.winstate.winner))// check if the game should continue
    { 
        lgame = updateGame(lgame); // pass localized game onto updategame and receive an updated package that has ran all player events

        // update player values and change active player to the next
        updatePlayer(&lgame.state.activePlayer, &lgame.arrPlayerContainer[0].isJailed, &lgame.arrPlayerContainer[1].isJailed); 
    }


    return lgame; 
}

/*
    This function instantiates the first game variable and asks for player names.
    @returns game of type gamepkg with values fit to play the game
*/
void slowpr(char str[], int strLength)
{
    for (size_t i = 0; i < strLength; i++)
    {
        printf("%c",str[i]);
        sleep_ms(150);
        fflush(stdout);
    }
    sleep_ms(1000);
    
}
struct gamepkg initializeGame(){
    // char* strMsg = "WELCOME TO MONOPOLY";
    // print1d(strMsg, strlen(strMsg));
    // getchar();

    struct gamestate initstate = initializeGamestate();
    initstate.SETTINGS = settingsPrompt(initstate.SETTINGS);
    struct Player* arrPlayers = malloc(512);
    arrPlayers[0] = initializePlayer();
    arrPlayers[1] = initializePlayer();

    char** ptrP1Name = &arrPlayers[0].name;
    fetchPlayerName(ptrP1Name);

    char** ptrP2Name = &arrPlayers[1].name;
    fetchPlayerName(ptrP2Name);

    struct gamepkg game;
    game.state = initstate;
    game.arrPlayerContainer = arrPlayers;

    return game;
}

int main()
{
    srand( (unsigned)time( NULL ) ) ;

    char choice;
    clear
    printf("\nWELCOME TO MONOPOLY!\n");
    sleep_ms(1000);
    print1d("oh wait.......",strlen("oh wait......."));
    sleep_ms(1500);
    clear
    printf("\nWELCOME TO PROPERTY");
    print1d("...PROPERTY!",strlen("...PROPERTY!"));
    print1d("\nyup...",strlen("\nyup..."));
    sleep_ms(3000);
    do
    {
        // play the game
        struct gamepkg game = playGame(initializeGame());

        // show the ending screen
        displayEndingScreen(game.state.SETTINGS.winsettings.winstate,
        game.arrPlayerContainer[0].name, game.arrPlayerContainer[1].name);

        clear
        // prompt for a replay
        printf("Press [G] to play again\n");
        printf("Press [E] to exit\n");
        char validInputs[2] = "GE";
        choice = handleInput(validInputs, 2);
    } while (choice == 'G');
    return 0;
}
