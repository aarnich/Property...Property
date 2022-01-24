/*
    Description: A collection of UI flairs used in the game Property...Property
    Author: Aaron Nicholas Lizardo Gumapac
*/
#include "../libdefs/uiFX.h"
#include <string.h>
#define shortpause 600
#define longpause 1000
#define quickpause 200
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
/*
    This cross-platform function pauses the system for a given amount of time (milliseconds)
    @param milliseconds how long to pause the system for
*/
void sleep_ms(int milliseconds){ 
#ifdef WIN32 // if the current system is a windows system
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L // if the current system is posix compliant (linux/mac)
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else // if the current system is neither, use system directives
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

/*
    prints an image defined by a stack of strings
    @param img[] the image to be printed (2d array)
    @param img_height the height of the image, tells the method when to stop printing
*/
void print2d(char* img[], size_t img_height){
    int pace = img_height > 20 ? 20 : 100;
    for (size_t i = 0; i < img_height; i++)
    {
        sleep_ms(pace);
        printf("%s\n",img[i]);
        fflush(stdout);
    }
}

/*
    Creates a divider given a symbol and its length
    @param divSymbol the symbol or design of the divider
    @param divLength how long is the divider
    @returns a divider string
*/
char* createDivider(char divSymbol, int divLength){
    char* div = malloc(1 + sizeof div[0] * divLength);
    for (size_t i = 0; i < divLength; i++)
    {
        div[i] = divSymbol;
    }
    return div;
}

/*
    A simple method that helps with code readability. Asks the user to press enter in order to continue with game events
*/
void continuePrompt(){
    sleep_ms(500);
    fflush(stdout);
    printf("\nPress ENTER to continue: ");
    getchar();
}

/*
    Prints a string by printing each individual character sequentially within a randomized time interval
    in order to mimic human typing
    @param str[] the string to be printed
    @param strLength the length of the string being passed
    @param paceFloor is the integer value that decides the 
*/
void print1d(char str[], int strLength, int paceFloor, int paceCeil)
{
    for (size_t i = 0; i < strLength; i++)
    {
        int randInterval = getRandNum(paceFloor,paceCeil);
        sleep_ms(randInterval);
        printf("%c",str[i]);
        fflush(stdout); // flush stdout in order to begin the next output
    }
    sleep_ms(1000);
}

/*
    Returns the name of the property given its index
    @params propIndex the property's position on the board
    @returns the name of the property (string)
*/
char* getPropertyName(int propIndex){
    switch(propIndex){
        case 1:
            return "Tree house";
            break;
        case 2:
            return "Electric Co.";
            break;
        case 3:
            return "Beach house";
            break;
        case 5:
            return "Castle";
            break;
        case 7:
            return "Railroad";
            break;
        case 8:
            return "Igloo";
            break;
        case 9:
            return "Farm house";
            break;
    }
    return " ";
}

/*
    Displays the changes in the player's balance as a UI flair
    @param currentBalance the player's balance before the change
    @param newBalance the player's balance after the change
*/
void showPersonalBalanceUpdate(float currentBalance, float newBalance)
{
    printf("\nYour pending balance: %.2f ➡️ %.2f\n", currentBalance, newBalance);
}

/*
    Displays the changes in the both players' balances in a with borders, dividers, and emojis
    @param p1CurrentBalance player1's balance before the change
    @param p1NewBalance player1's balance after the change
    @param p1Name player1's name, necessary for UI flair
    @param p2CurrentBalance player2's balance before the change
    @param p2NewBalance player2's balance after the change
    @param p2Name player2's name, necessary for UI flair
*/
void showBalanceUpdate(
                    float p1CurrentBalance,
                    float p1NewBalance,
                    char* p1Name,
                    float p2CurrentBalance,
                    float p2NewBalance,
                    char* p2Name
                    )
{
    char* DIVIDER = createDivider('-',24);
    char* DIVIDER2 = createDivider('-',13);
    char* p1Indicator = malloc(128);
    char* p2Indicator = malloc(128);

    if(p1CurrentBalance < p1NewBalance)
        p1Indicator = "🔺";
    else if(p1CurrentBalance > p1NewBalance)
        p1Indicator = "🔻";
    else
        p1Indicator = " ✒ ";

    if(p2CurrentBalance < p2NewBalance)
        p2Indicator = "🔺";
    else if(p2CurrentBalance > p2NewBalance)
        p2Indicator = "🔻";
    else
        p2Indicator = " ✒ ";
    
    printf("\n%s[ BALANCE  UPDATE 🏦 ]%s\n",DIVIDER,DIVIDER);
    sleep_ms(1000);
    printf("\n%s %s's balance: \n%.2f ➡️ %.2f\n\n",
                    p1Indicator,
                    p1Name,
                    p1CurrentBalance,
                    p1NewBalance
    );
    printf("\n%s %s's balance: \n%.2f ➡️ %.2f\n",
                    p2Indicator,
                    p2Name,
                    p2CurrentBalance,
                    p2NewBalance 
    );
    sleep_ms(700);
    printf("\n%s[ STATEMENT ISSUED BY: Wayland Corporation ]%s\n",DIVIDER2,DIVIDER2);
}


/*
    Dislays a message that congratulates or demeans the players
    @param context tells how the winningPlayer was decided and which win conditions were satisfied
    @param winningPlayer whether player1, player2, or both of the won
    @param p1Name player 1's name
    @param p2name player 2's name
*/
void displayContextFlair(enum winContext context, enum winner winningPlayer, char* p1Name, char* p2Name){
    char* strLoser = malloc (256);
    char* strWinner = malloc (256);
    strLoser = " both of you";
    strWinner = " both of you";
    if(winningPlayer == PLAYER1){
        strLoser = p1Name;
        strWinner = p2Name;
    }
    if(winningPlayer == PLAYER1){
        strLoser = p2Name;
        strWinner = p1Name;
    }
    
    char* strArticle = winningPlayer == TIE ? " were" : " was";
    if(context == ENEMY_BANKRUPTY)
    {
        sleep_ms(1000);
        print1d(strLoser, strlen(strLoser)); // animated print for loser name 
        sleep_ms(800);
        print1d(strArticle, strlen(strArticle));
        char strFlair1[] = " pushed to the annals of BANKRUPTCY!";
        print1d(strFlair1, strlen(strFlair1)); // animated print for the bankruptcy flair
    }
    if(context == ENEMY_LOSING_BALANCE)
    {
        sleep_ms(1000);
        print1d(strLoser, strlen(strLoser)); // animated print for loser name
        sleep_ms(800);
        print1d(strArticle, strlen(strArticle)); // animated print for the article
        char strFlair1[] = " constricted by the forces of capitalism..."; // animated print for message flair
        print1d(strFlair1, strlen(strFlair1));
        sleep_ms(1000);
        char strFlair2[] = " so tightly that you could not maintain a balance above the losing balance"; // animated print for losing balance flair
        print1d(strFlair1, strlen(strFlair2)); 
    }
    if(context == REACHED_WINNING_BALANCE){
        sleep_ms(1000);
        print1d(strWinner, strlen(strWinner)); // animated print for winner name
        char strFlair1[] = " THRIVED IN THIS NEOCLASSICIST HELLSCAPE...";
        print1d(strFlair1, strlen(strFlair1)); // animated print for winning balance flair
        sleep_ms(1000);
        char strFlair2[] = " and reached the winning balance!\n";
        print1d(strFlair1, strlen(strFlair2)); // animated print for winning balance flair
        sleep_ms(1000);
        char strFlair3[] = " I could not find a better capitalist dog if I tried!";
        print1d(strFlair3, strlen(strFlair3)); // animated print for winning balance flair
    }
}
/*
    contextual ending screen that cognratulates the winner(s) according to their win conditions
    @param win describes how the winner(s) won
    @param p1Name player 1's name
    @param p2Name player 2's name
*/
void displayEndingScreen(struct winstate win, char* p1Name, char* p2Name){
    // show monopoly man pointing his finger
    printf("\nA WINNER HAS BEEN DECIDED\n");
    sleep_ms(2000);
    clear;
    if(win.winner == TIE){
        printf("\n🙆‍By some freak accident\n");
        sleep_ms(1000);
        printf(".");
        sleep_ms(1000);
        printf(".");
        sleep_ms(1000);
        printf(".");
        printf("both players won...");
        sleep_ms(1500);
        printf(" or lost?\n");
    }
        char* strMulti = (win.winRationale[0] != NOCONTEXT && win.winRationale[1] != NOCONTEXT) ? "\nfurthermore...\n" : " ";

        for (size_t i = 0; i < 2; i++)
        {
            if(win.winRationale[i] != NOCONTEXT)
            {
                displayContextFlair(win.winRationale[i], win.winner, p1Name, p2Name);
                sleep_ms(700);
                print1d(strMulti, strlen(strMulti)); 
            }
        }
}
/*
    Draws an image of where the player is given current position
    @param pos the player's current position
*/
void displayPos(int pos){
    if(pos == 4){
        char* display[] = {

"                                                                          ",
"                        ░░▓▓▒▒▒▒▒▒▓▓░░                                    ",
"                      ▒▒▓▓▒▒▒▒▒▒▓▓▓▓▓▓▒▒                                  ",
"                      ▒▒▓▓▓▓▒▒▓▓▓▓▓▓▓▓▒▒▒▒                                ",
"                      ▓▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒                                ",
"                    ░░▓▓▒▒▒▒▒▒▒▒▓▓▓▓▒▒▓▓▓▓░░                              ",
"                    ▒▒▓▓▒▒  ░░▓▓▓▓▓▓▓▓▒▒▓▓                                ",
"                    ░░▓▓▒▒    ▓▓▓▓▓▓▒▒▓▓▒▒                                ",
"                    ▒▒▓▓░░  ░░▓▓▓▓▒▒  ░░▓▓                                ",
"                    ▓▓▓▓    ░░▓▓▓▓░░  ░░▒▒                                ",
"                    ▓▓▒▒    ▒▒▓▓▓▓░░  ▒▒                                  ",
"                  ░░▓▓▓▓▒▒▒▒▓▓▓▓▓▓░░  ▒▒                                  ",
"                ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░▒▒                                  ",
"                ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▓▓▒▒                                ",
"                ░░▒▒▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▓▓▒▒░░                            ",
"                ▒▒▓▓▓▓▒▒▒▒▓▓▓▓▒▒▒▒▒▒▓▓▓▓  ▓▓▓▓▒▒░░                        ",
"                ▒▒▓▓▒▒░░▓▓▓▓▓▓▓▓▒▒▒▒▒▒      ▓▓▓▓▒▒▒▒░░                    ",
"                ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒        ░░▓▓▓▓▒▒▒▒░░                ",
"                ░░████████▓▓▓▓▓▓▓▓▓▓▓▓            ▒▒▓▓▓▓▒▒▒▒░░            ",
"                    ▓▓██████████████▒▒                ▓▓▓▓▓▓▒▒▒▒          ",
"          ░░░░░░░░▒▒▒▒▒▒▒▒████████▓▓▒▒░░░░░░░░          ░░▓▓▓▓▓▓▒▒░░      ",
"      ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░          ▒▒▓▓▓▓▒▒▒▒    ",
"    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒            ▒▒▓▓▓▓▒▒░░",
"  ░░▒▒▒▒▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒                  ██▓▓",
"  ░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓  ▓▓▓▓░░░░▓▓░░░░░░░░▓▓▓▓▓▓▒▒▒▒▒▒▒▒                ░░▒▒▒▒",
"  ▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓░░▓▓▓▓░░░░▒▒▒▒░░▒▒░░▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒                    ",
"  ▒▒▒▒▓▓▓▓▓▓▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒                    ",
"░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▒▒░░                  ",
"  ░░▒▒▒▒▓▓████████████████████████████████▓▓▓▓▒▒▒▒░░░░                    "

        };
    int rows = sizeof(display) / sizeof(display[0]);
    print2d(display,rows);
    }
    else if(pos == 1){
        char* display[] = {

"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒    ██████████▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓                  ██▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██      ▒▒▒▒▒▒▒▒▒▒▒▒      ▓▓████▓▓▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓    ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒    ▓▓▓▓▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██    ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒        ██▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░  ██▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  ▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒    ",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▒▒▒▒▒▒▒▒",
"░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒██████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
"▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"

        };
        int rows = sizeof(display) / sizeof(display[0]);
        print2d(display,rows);
    }
    else if(pos == 2){
        char* display[] = {
                                                                                
                                                                                        
"                                   ░░░░░░░░░░░░                                      ",
"                               ░░░░            ░░░░                                  ",
"                             ░░          ██        ░░                                ",
"                           ░░          ████          ░░                              ",
"                           ░░        ████            ░░                              ",
"                          ░░        ██████              ░░                           ",
"                         ░░      ██████                ░░                            ",
"                         ░░    ██████████████████      ░░                            ",
"                         ░░    ████████████████        ░░                            ",
"                         ░░            ██████          ░░                            ",
"                         ░░          ██████            ░░                            ",
"                           ░░      ██████            ░░                              ",
"                           ░░      ████              ░░                              ",
"                             ░░    ██              ░░                                ",
"                               ░░░░            ░░░░                                  ",
"                                   ░░░░░░░░░░░░                                      ",
                                                                                        
        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);
    }                                                                       
    else if(pos == 3){                                                                                
        char* display[] = {

                                                                                        
"                          ▓▓████                          ",
"                            ██▓▓██▓▓▓▓                    ",
"                              ████▓▓▓▓▓▓                  ",
"                                ▓▓██▓▓▓▓██                ",
"                                  ████▓▓██                ",
"                      ████████████████▓▓██                ",
"                          ██████████▓▓██▓▓████            ",
"                    ████      ██████▓▓████████▓▓          ",
"                ██████      ████████████  ▓▓██▓▓██        ",
"              ██▓▓██      ████    ████    ████████        ",
"            ██████      ██      ████        ██████        ",
"            ████              ██████          ████        ",
"        ██████▓▓████        ██████            ██          ",
"      ▓▓▓▓▓▓████▓▓████      ████              ██          ",
"    ██████████████▓▓████  ██████                          ",
"    ████  ████  ████████  ████                            ",
"    ██    ██      ██████  ████                            ",
"    ██    ██      ██████▓▓████                            ",
"          ██        ████▓▓████                            ",
"                    ██████▓▓██                            ",
"                      ████▓▓██                            ",
"                  ▓▓  ██████▓▓                            ",
"              ██  ▓▓██▓▓▓▓████                            ",
"        ████████▓▓████████████▓▓████████████              ",
"  ░░░░░░░░░░████░░░░████████░░░░████████░░░░░░░░░░░░░░░░░░",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░      ",
"      ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░          "

        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);
    }                                                                            
    else if(pos == 5){
        char* display[] = {



"        ░░░░░░      ░░  ░░░░░░      ░░  ░░██░░      ░░      ░░  ░░  ░░  ░░░░░░  ░░░░░░  ",
"░░░░    ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  ██████  ░░░░░░░░    ░░  ░░░░░░  ░░░░░░  ░░░░░░░░",
"            ░░░░░░░░                      ██  ░░░░░░░░                            ░░░░░░",
"          ░░  ░░                          ██░░  ░░░░                            ░░  ░░  ",
"          ░░░░░░                        ██  ██░░                                ░░░░░░  ",
"░░░░░░░░░░  ░░  ░░░░░░░░░░░░░░  ░░░░░░██      ██  ░░░░░░    ░░  ░░░░░░░░░░░░░░░░░░░░░░░░",
"      ░░░░░░  ░░      ░░      ░░      ██  ██  ██      ░░      ░░      ░░    ░░░░░░      ",
"░░░░░░░░░░                          ░░██  ██  ██                      ░░░░░░░░░░        ",
"░░░░░░░░                            ░░████  ████                      ░░░░  ░░          ",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██      ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
"      ░░      ░░      ░░      ░░    ██          ██    ░░      ░░      ░░      ░░        ",
"                                    ██    ██    ██                                      ",
"                                    ██  ██████  ██                                      ",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  ██  ██████  ██  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
"                                    ██  ██  ██  ██                                      ",
"                                    ████      ████                                      ",
"                                    ██          ██                                      ",
"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██              ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",
"              ░░      ░░      ░░░░██              ██░░░░      ░░      ░░      ░░    ░░  ",
"            ░░░░          ░░░░██████              ██████░░░░                      ░░░░  ",
"            ░░░░░░    ░░░░██████████              ██████████░░░░                  ░░░░░░",
"  ░░      ░░░░░░  ░░░░██████████████    ██████    ██████████████░░░░    ░░░░    ░░░░░░  ",
"      ░░░░  ░░      ████████████████  ██      ██  ████████████████          ░░░░  ░░    ",
"    ░░░░░░░░        ██████  ██  ████  ██  ██  ██  ████  ██  ██████        ░░░░░░░░      ",
"  ░░░░░░░░          ████████████████  ██████████  ████████████████      ░░░░░░░░        ",
"░░░░░░░░  ░░░░░░░░░░██████  ██  ████  ██  ██  ██  ████  ██  ██████░░░░░░░░░░░░  ░░░░░░░░",
"  ░░░░        ░░    ██████  ██  ████  ██  ██  ██  ████  ██  ██████      ░░░░  ░░        ",
"                    ████████████████  ██      ██  ████████████████                      ",
"      ░░      ░░  ██████████████████████████████████████████████████                    "

        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);
    }
    else if(pos == 8){
        char* display[] = {

"                                                                                  ░░▒▒▓▓▓▓▓▓▓▓██▓▓▒▒░░  ",
"  ██████████████████████▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░            ░░    ▒▒  ░░              ░░▒▒▓▓",
"▓▓                                                                                                      ",
"██                                                                                                ░░░░▒▒",
"██                                                                                              ░░░░░░██",
"░░▒▒                                    ░░░░░░░░░░░░░░░░░░░░                            ░░░░░░░░░░░░░░▒▒",
"  ▓▓░░                  ░░░░        ░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░                  ░░░░░░░░░░░░░░░░░░  ",
"  ▓▓░░░░░░  ░░░░░░░░░░      ░░  ░░░░      ░░░░░░  ░░          ░░░░░░              ░░░░          ░░░░▒▒  ",
"  ░░▒▒    ░░██▒▒                                                      ░░                            ░░  ",
"    ▓▓        ▓▓          ░░░░                ░░▓▓                                    ██▒▒          ░░  ",
"    ██        ▒▒          ▓▓▓▓                ▒▒░░░░                      ▒▒▓▓      ▓▓  ▓▓              ",
"    ▓▓    ░░    ░░        ██▒▒                ░░  ▒▒        ▓▓▓▓          ████░░  ░░▒▒  ░░▒▒      ░░    ",
"    ▒▒░░  ░░    ░░      ░░██░░                    ▓▓        ████░░      ▓▓▒▒▓▓██  ██      ▓▓      ░░    ",
"    ▒▒▒▒  ░░    ▒▒      ▒▒██  ░░            ░░    ██      ░░▒▒██▓▓      ██  ░░██  ██      ██      ▒▒    ",
"      ██  ░░    ▓▓      ▓▓██░░▒▒            ▓▓    ▓▓      ▓▓  ▒▒██    ▒▒▓▓    ██▓▓▒▒      ██      ▒▒    ",
"      ██  ░░    ▓▓      ████  ██            ██    ▒▒      ██    ██▒▒  ██        ▒▒        ▒▒▒▒    ██    ",
"      ██  ░░    ▓▓      ██▒▒  ▓▓            ██    ░░░░    ██    ██▓▓  ██                  ░░▓▓    ██    ",
"      ██        ██    ░░██    ▓▓  ░░        ██    ░░▒▒    ██    ▒▒██░░▒▒                  ░░▓▓    ██    ",
"      ██        ▒▒    ▒▒██    ██▒▒██      ░░▓▓    ░░▓▓  ▒▒▓▓      ██▓▓░░                    ██    ██    ",
"      ██░░      ░░    ▓▓██    ██████      ▒▒██      ██  ██▒▒      ▓▓██                      ██    ██    ",
"      ██▒▒      ░░    ████    ▓▓▓▓██░░    ██▒▒      ██  ▓▓░░        ░░                      ██    ██    ",
"      ██▓▓        ▒▒  ████    ██▒▒▒▒▒▒    ██░░      ██  ██                                  ██  ░░██    ",
"      ▓▓██        ██  ██▒▒    ░░  ░░▓▓    ██░░      ██  ██                                  ██░░░░▒▒    ",
"      ░░██        ▓▓  ██░░          ██    ██        ██  ██                                  ██▒▒░░▒▒    ",
"        ░░        ██░░██            ██    ██        ██  ██                                  ▓▓▒▒▒▒      ",
"                  ▓▓████            ██  ░░██        ██░░██                                  ▒▒▓▓██      ",
"                  ██▓▓██            ██  ░░██        ██░░▓▓                                  ▒▒██▓▓      ",
"                  ████░░            ▒▒░░▒▒██        ██▒▒▒▒                                  ░░████      ",
"                  ████                ░░▓▓▓▓        ▓▓▓▓░░                                    ████      ",
"                  ████                ▒▒██▒▒        ░░██                                      ██▓▓      ",
"                  ▒▒██                ████▒▒          ▓▓                                      ██▒▒      ",
"                                      ▓▓██░░                                                  ██        ",
"                                      ████                                                    ██        ",
"                                      ████                                                    ░░        ",
"                                      ▒▒▓▓                                                              "

        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);
    }
    else if(pos == 9){
        char* display[] = {
                                                                                                
"                                                      ██                        ",
"                                        ████        ██░░██                      ",
"                                      ██  ▒▒▓▓    ██░░░░██          ██          ",
"    ████                              ░░██    ██  ██░░░░██        ██░░██        ",
"  ██    ██                              ██    ████████████▓▓██    ██░░██        ",
"██      ██                                ██████████████████  ██████░░██        ",
"░░██  ██                                  ██████████████████    ░░██▓▓██        ",
"  ░░██          ██████████████████████████░░████████████              ████████  ",
"    ██        ██████████████████████████▒▒████████████                ░░░░░░░░██",
"    ██      ██████████████████████████░░  ██      ██                  ████    ██",
"    ██    ████████████████████████████  ██      ████                  ████  ██░░",
"      ████  ██████████████████████████  ██      ████          ██    ██░░░░██    ",
"        ██  ████████████░░████████████  ██      ░░░░        ████    ██          ",
"        ██  ░░████████    ░░████████    ██  ██████          ████  ██            ",
"        ██      ░░██          ████      ████░░▒▒░░██████          ██            ",
"        ██                              ██░░░░░░░░░░░░░░████      ██            ",
"        ██                              ██░░██▓▓░░░░░░░░░░░░▓▓  ▓▓░░            ",
"        ██      ██░░                    ░░▓▓▒▒▒▒░░░░░░░░░░░░▒▒████              ",
"        ██    ██████        ██              ██░░░░░░░░░░████░░██                ",
"        ██    ██████    ██    ████            ██████▒▒▒▒░░░░██                  ",
"        ░░▓▓  ▒▒░░░░    ██    ████        ▓▓  ░░░░░░▒▒▒▒▓▓▓▓░░                  ",
"          ██            ████████████      ████▓▓    ▒▒▒▒░░░░                    ",
"          ██          ██▒▒  ██    ██      ██░░██    ██▒▒▒▒                      ",
"            ██        ██    ██      ██    ██    ██  ██                          ",
"            ██        ██    ██      ██    ██    ██  ██                          ",
"            ██      ████    ██      ██    ██    ██  ██                          ",
"            ██▓▓  ▓▓████▓▓▒▒██      ██  ▓▓██▓▓  ████████                        ",
"              ██▓▓██▒▒▓▓██████      ░░░░██████  ░░██████                        "

        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);
    }
    else if(pos == 0){
        char* display[] = {
                                                              
"                                ▒▒                            ",
"                              ▓▓░░░░                          ",
"                              ▒▒░░▓▓                          ",
"                            ░░▒▒░░▓▓                          ",
"                            ▒▒░░░░░░▒▒                        ",
"                            ▓▓░░░░░░▓▓                        ",
"                            ██░░░░░░▓▓                        ",
"                          ██░░░░░░░░▒▒░░                      ",
"                          ▓▓░░░░░░░░░░░░                      ",
"                          ▓▓░░░░░░░░░░░░                      ",
"                          ▓▓░░░░░░░░▒▒░░                      ",
"                        ░░██████████████                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██░░░░▓▓▓▓░░██                      ",
"                        ░░██▓▓▓▓████▓▓██                      ",
"                        ░░░░░░░░░░░░░░██                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░░░░░░░▒▒░░░░▓▓                      ",
"                        ░░██████████████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓██░░████                      ",
"                        ░░██▓▓▓▓▓▓▓▓▓▓██                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ░░░░░░░░░░░░░░▓▓                      ",
"                        ▓▓░░░░░░▒▒░░░░▓▓▒▒                    ",
"                        ██░░░░░░▓▓░░░░▓▓▒▒                    ",
"                      ▓▓▒▒░░░░░░▓▓░░░░▓▓▒▒░░                  ",
"                      ▒▒▒▒░░░░░░▓▓░░░░▓▓░░▒▒                  ",
"                    ▒▒░░▒▒░░░░░░▓▓░░░░▓▓░░▒▒                  ",
"                    ▓▓░░▒▒▒▒░░░░▓▓░░░░▒▒░░░░▓▓                ",
"                    ▒▒▒▒▒▒██▒▒▒▒██▒▒▒▒▓▓▒▒░░                  ",
"                            ░░▓▓▓▓██                          ",
"                            ██▓▓▓▓▓▓▓▓                        ",
"                          ▒▒▓▓▓▓▓▓▓▓▓▓                        ",
"                          ▓▓▓▓▓▓▓▓▓▓▓▓░░                      ",
"                            ██████████                        ",
"                          ▒▒░░░░  ░░▒▒░░                      ",
"                          ▒▒░░░░  ░░░░▒▒                      ",
"                        ░░▒▒░░      ░░▓▓                      ",
"                        ░░▒▒░░    ░░░░▓▓                      ",
"                        ░░░░░░    ░░░░▒▒                      ",
"                        ▓▓░░░░░░  ░░░░░░▓▓                    ",
"                        ▓▓░░░░░░░░░░░░░░▓▓                    ",
"                        ▓▓░░░░░░░░░░░░░░▓▓                    ",
"                        ▓▓░░░░░░░░░░░░░░▓▓                    ",
"                        ░░░░░░░░░░░░░░▒▒                      ",
"                          ▒▒░░░░░░░░░░▒▒                      ",
"                            ░░░░░░░░░░                        "
                                                              
        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);
    }
    else if(pos == 6){
        char* display[] = {

"                                ██▓▓██                                      ",
"                            ▓▓▓▓▓▓██                                        ",
"                          ██▓▓▓▓██                                          ",
"                        ▓▓▓▓▓▓▓▓██                                          ",
"                        ██▓▓▓▓▓▓██                                          ",
"                      ██▓▓▓▓▓▓▓▓▓▓██                                        ",
"                      ██▓▓▓▓▓▓▓▓▓▓▓▓████          ██████                    ",
"                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██░░▓▓▓▓▓▓██                    ",
"                    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██                      ",
"                    ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████                        ",
"                ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████░░                          ",
"      ████▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓████                                ",
"      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██████░░░░██                              ",
"        ██████▓▓▓▓▓▓▓▓▓▓▓▓████████░░░░░░░░░░██                              ",
"              ████████████░░▓▓░░██░░░░░░░░░░░░██                            ",
"                      ██░░░░░░░░██░░░░░░░░░░░░░░████████      ██████        ",
"                    ██  ░░░░░░░░░░██░░░░░░░░░░░░░░░░░░░░██████░░██          ",
"  ██████████        ██████░░▓▓░░░░██░░░░░░░░░░████░░░░░░░░░░░░██            ",
"██░░░░░░░░░░██          ██▓▓░░░░██░░██░░░░░░██▓▓▓▓██░░░░░░░░██              ",
"██░░▓▓░░░░░░██▓▓        ████████░░████░░░░██▓▓▓▓▓▓▒▒██░░░░██████            ",
"██░░░░▓▓░░░░██  ▒▒            ████▓▓██░░██▓▓▓▓▒▒▓▓▓▓▓▓▓▓░░░░░░░░▓▓▓▓        ",
"██▓▓░░░░████    ▓▓            ██▓▓▓▓██░░██▓▓▓▓██▓▓▓▓▓▓▓▓██░░░░░░░░░░██      ",
"██░░░░░░██    ▓▓              ██▓▓▓▓██░░██▓▓▓▓▒▒██▓▓▓▓▓▓▒▒██░░██████████    ",
"██▒▒▒▒░░██  ▓▓██████▓▓██    ▓▓▓▓██▓▓▓▓▓▓██▓▓▓▓▓▓▓▓██▓▓▓▓▓▓██░░██░░          ",
"████████    ██░░░░██▓▓▓▓████▓▓▓▓██▓▓▓▓▓▓██▓▓▓▓▓▓██▓▓▓▓▓▓▓▓██░░░░██          ",
"            ██░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▒▒██▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓▓▓▓▓▓██░░░░░░██        ",
"              ▓▓████▓▓▓▓▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▓▓████▓▓▓▓▓▓▒▒██▓▓██▓▓░░░░▓▓      ",
"              ▓▓  ██▓▓▓▓▓▓▓▓▓▓██  ██▓▓▓▓▓▓██░░░░██▓▓▓▓▓▓██▓▓██  ██████▓▓    ",
"              ▒▒  ██▓▓▓▓▓▓▓▓██      ██▓▓▓▓██░░░░██▓▓▓▓██▓▓▓▓██              ",
"              ▒▒    ██▓▓▓▓██        ██▓▓▓▓▓▓████▓▓▓▓██▒▒▓▓▓▓██              ",
"              ▓▓      ████          ██▓▓▓▓▓▓▓▓██████▓▓▓▓▓▓▓▓▓▓██            ",
"              ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"              ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"              ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▒▒░░                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██            ",
"            ▓▓                          ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██          ",
"            ░░▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██          ",
"              ▒▒                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██          ",
"                ▒▒                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██        ",
"                ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██        ",
"                ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      ",
"                ▓▓                      ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██    ",
"              ▓▓                        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  ",
"              ▒▒                      ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
"              ▓▓                      ██████████████████████████████████████",

        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);
        sleep_ms(700);
        print1d("\nYou feelin' lucky, Child? 🦹",strlen("\nYou feelin' lucky, Child? 🦹",));
    }
if(pos == 7){
    char* display[] = {
"                                                                              ▓▓▓▓              ",
"                  ████████                                                ████                  ",
"                ▓▓░░░░░░░░██                    ▓▓▓▓▒▒▓▓▓▓▒▒          ▓▓▒▒████▓▓██▓▓██▓▓██▓▓▓▓  ",
"                  ████████                      ██▒▒▒▒▒▒▒▒██        ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██",
"                  ██░░░░██                      ██▒▒▒▒▒▒▒▒██    ▓▓  ████████▓▓▓▓██▓▓▓▓██████████",
"          ██████  ██░░░░██  ████████            ██▒▒▒▒▒▒▒▒██  ██▒▒██  ██▒▒▒▒▒▒██    ██          ",
"          ██▒▒██  ██░░░░██  ██▒▒▒▒██    ▓▓      ██▒▒▒▒▒▒▒▒██  ██▒▒██  ██▒▒░░▒▒██    ██          ",
"          ██▒▒██  ██░░░░██  ██▒▒▒▒██  ▓▓▒▒▓▓  ████▒▒▒▒▒▒▒▒██░░██████▓▓██▒▒  ▒▒██    ██          ",
"          ██████████░░░░██████▒▒▒▒██▓▓██████▓▓██▒▒████████▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒▒██    ██          ",
"        ██▒▒░░▒▒░░░░▓▓██░░██▒▒▓▓▓▓▒▒▓▓▓▓▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒██████▓▓████████          ",
"      ▓▓░░░░░░░░░░░░░░░░░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██          ",
"      ██░░░░░░░░░░░░░░░░░░██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒██          ",
"      ██░░░░░░░░░░░░░░░░░░██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██▒▒▒▒▒▒▒▒▒▒▒▒██          ",
"        ██░░░░░░░░░░░░░░░░██▓▓▓▓▓▓▓▓▓▓██████▓▓▓▓▓▓▓▓▓▓██████▓▓▓▓▓▓▓▓▓▓██████▒▒▒▒▒▒▒▒██          ",
"          ████▓▓██▓▓██▓▓████▓▓▓▓▓▓▓▓██▒▒▒▒▒▒██▓▓▓▓▓▓██▒▒▒▒▒▒██▓▓▓▓▓▓██▒▒▒▒▒▒██████████▓▓▓▓      ",
"    ██████▒▒▒▒▒▒▒▒██▒▒▒▒▒▒██████████▒▒▒▒▒▒▒▒▒▒██▓▓██▒▒▒▒▒▒▒▒▒▒██▓▓██▒▒▒▒▒▒▒▒▒▒██▓▓▓▓██▒▒██      ",
"  ▓▓▒▒▒▒▒▒██▓▓████████████████  ░░██▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒██▓▓▓▓████        ",
"██▒▒▒▒▒▒▒▒██  ██▒▒▒▒██▓▓██▒▒▒▒██  ██▒▒▒▒▒▒▒▒▒▒██  ██▒▒▒▒▒▒▒▒▒▒██  ██▒▒▒▒▒▒▒▒▒▒██████  ████      ",
"████████████  ██▒▒▒▒██████▒▒▒▒██    ██▒▒▒▒▒▒██      ██▒▒▒▒▒▒██      ██▒▒▒▒▒▒██                  ",
"                ████      ████        ██████          ██████          ██████                    ",
"                                                                        ░░                      "
        };
        int rows = sizeof display / sizeof display[0];
        print2d(display, rows);                                                                                         
        sleep_ms(700);
        print1d("\nYou hear the sound of trains and the complex machinations of the industrial era!",strlen("\nYou feelin' lucky, Child? 🦹",));
    }                                                                                                

}                                                                                               




// char* display[] = {
// "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒░░      ░░░░░░▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░░░▒▒▓▓██▓▓▒▒░░▒▒░░    ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░░░▒▒████████▓▓▓▓░░▒▒░░    ▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░░░░░████████████▓▓██▓▓░░░░▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓██████████████████▓▓██▓▓░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░██▓▓▓▓▓▓▓▓██████████████▓▓▓▓██░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░▓▓██████████▓▓▓▓██████████▓▓▓▓░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░▓▓████████████████▓▓▓▓████░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░▓▓████▓▓▓▓▓▓██████████▓▓▒▒▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░░░▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓██▓▓░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░▒▒██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░██████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░░░██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░██▒▒░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██████▓▓░░  ░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░████████▓▓░░░░▒▒██▓▓▓▓▓▓▓▓████▓▓████▓▓██▒▒░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░▒▒██████████████▒▒░░░░▓▓▓▓░░▒▒░░░░▒▒▓▓▓▓██████▓▓░░  ░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░░░▓▓████████████████████████░░░░░░░░░░░░░░░░▒▒████▓▓▓▓▓▓░░  ░░▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░  ██████▓▓████████████████▓▓▓▓░░░░░░░░░░░░░░░░░░░░░░▓▓████████▓▓▓▓░░  ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "░░░░░░░░░░░░░░░░▓▓██████████▒▒▒▒▓▓▓▓████▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓▓▓████▓▓▓▓▓▓░░    ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "                ▓▓████████████████▓▓▒▒▓▓██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▓▓▓▓████▓▓████▓▓░░░░  ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓",
// "            ░░    ▒▒████████████████████▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒████████████▓▓▓▓▒▒░░░░  ░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓",
// "                      ░░▒▒██████████████▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓▓▓████████████▓▓▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓",
// "                              ░░▒▒██████  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒░░▓▓████████████████▓▓▓▓░░░░░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓",
// "        ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░        ░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▓▓▓▓██████████████▓▓▒▒░░░░▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓",
// "    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▓▓▒▒▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▓▓██████████████▓▓██▓▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓",
// "    ████████████████████████████████████████▓▓▓▓▓▓██▓▓▓▓▓▓██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓████████████████▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
// "    ████████████████████████████████████████████▓▓▓▓▓▓▓▓▓▓██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██████████████▓▓▒▒  ▒▒▓▓",
// "░░  ██████████████████████████████████████████▓▓▓▓▓▓▓▓▓▓▓▓██░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓████████████▓▓",
// "░░░░▓▓▓▓████████████████████▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░░░░░░░▒▒▒▒▓▓▓▓▒▒░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████████",
// "░░▓▓████████████████████████████████████████████████▓▓██▓▓▓▓▒▒░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓██▒▒",
// "░░░░██████████████████████████████████████████████████████░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓",
// "░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓",
// "░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒",
// "░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░▒▒░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░▒▒▒▒",
// "░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
// "░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
// "░░░░▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
// "░░░░▒▒▒▒▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▒▒▓▓▓▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
// "░░░░░░░░▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░▒▒▒▒░░░░░░░░░░  ░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
// "░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░▒▒░░░░░░░░░░▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
// "░░░░░░░░░░░░▒▒▒▒▒▒░░░░▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒",
// "░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▓▓▓▓▒▒▓▓▒▒▒▒░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
// };