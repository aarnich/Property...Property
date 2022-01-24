#include "runtime_headers/GameLoop.h"
/*
    Creates a new player
    @returns player with initial values
*/
Player initializePlayer(){
    Player initPlayer;
    initPlayer.pos = DEFAULT_STARTINGPOS;
    initPlayer.balance = DEFAULT_STARTINGBALANCE;
    initPlayer.jailedCounter = 0;
    initPlayer.name = malloc (256);
    initPlayer.name = "Harambe";
    initPlayer.isBankrupt = false;
    initPlayer.isJailed = false;
    return initPlayer;
}

/*
    initializes gamestate with default values 
    @returns initial gamestate

*/
struct gamestate initializeGamestate()
{
    struct gamestate initgamestate;
    initgamestate.activePlayer = 0;
    initgamestate.SETTINGS = initializeSettings();
    initgamestate.STATEKEY = STARTING_STATEKEY;

    return initgamestate;
}

/*
    Determines whether the game should continue or not given an enum winner
    @param WINNER enum that tells the game whether a winner has been decided
    @returns boolean value that dictates the continuation of the game
*/
bool continueGame(enum winner WINNER){
    if(WINNER != NONE)
        return false;
    return true;
}

/*
    A method that accesses and modifies the state's activePlayer and both players' jail status
    @param ptrActivePlayer the pointer variable pointing to the current active player as described by the state variable
    @param ptrP1Jail pointer to jail status of player 1
    @param ptrP2Jail pointer to jail status of player 2
*/
void updatePlayer(unsigned int* ptrActivePlayer, bool* ptrP1Jail, bool* ptrP2Jail){
    int activePlayer = *ptrActivePlayer; // dereference activePlayer pointer
     if(activePlayer == 1){
        if(*ptrP2Jail){
            *ptrP2Jail = false;
            if(*ptrP1Jail)
                *ptrActivePlayer = 3;
        }
        else if(!*ptrP2Jail)
            *ptrActivePlayer = 2;
    }
    if(activePlayer == 2){
        if(*ptrP1Jail){
            *ptrP1Jail = false;
            if(*ptrP2Jail)
                *ptrActivePlayer = 4;
        }
        else if(!*ptrP1Jail){
            *ptrActivePlayer = 1;
        }
    }
}

/*
    This function returns a gamepkg with with updated winsettings values;
    @param currentPlayer the player whose turn it is
    @param currentPlayerKey currentPlayer's location (index) in the player array
    @param opposingPlayer currentPlayer's enemy
    @param enemyPlayeyKey opposingPlayer's location (index) in  the player array
    @param containedstate the state evaluated during updateGame();
    @returns updated gamepkg struct with new winsettings values
*/
struct gamepkg saveGame(Player currentPlayer, int currentPlayerKey, Player opposingPlayer, int enemyPlayerKey, struct gamestate containedstate){
    Player* playerContainer = malloc (512);
    playerContainer[currentPlayerKey - 1] = currentPlayer;
    playerContainer[enemyPlayerKey - 1] = opposingPlayer;
    struct gamestate state = containedstate;
    state.SETTINGS.winsettings.winstate = updateWinState(state.SETTINGS.winsettings, playerContainer[0], playerContainer[1]); // evaluate win settings

    struct gamepkg updatedGame;
    updatedGame.state = state;
    updatedGame.arrPlayerContainer = playerContainer;
    
    return updatedGame;
}

/*
    Updates game data depending on player actions 
    @param game game package containing all game data
    @returns updated game after 1 game turn
*/
struct gamepkg updateGame(struct gamepkg game){
    fflush(stdout);
    if(game.state.activePlayer == 3 || game.state.activePlayer == 4)
    {
        printf("\nBOTH PLAYERS HAVE BEEN IMPRISONED!\n");
        sleep_ms(1000);
        game.state.activePlayer -= 2;
        return game;
    }
    showGameStatus(game);
    struct gamepkg updatedGame = game;
    struct gamestate containedState = updatedGame.state;
    Player* playerContainer = updatedGame.arrPlayerContainer;

    // integer value used to index currentPlayer
    unsigned int currentPlayerKey = containedState.activePlayer;
    unsigned int enemyPlayerKey = currentPlayerKey == 1 ? 2 : 1;

    Player currentPlayer = playerContainer[currentPlayerKey - 1]; // current player from player container
    Player opposingPlayer = playerContainer[enemyPlayerKey - 1]; // opposing player from player container
    float pendingPlayerBalance = currentPlayer.balance; // player 1 balance to be sent after updateGame() events
    float pendingOpponentBalance = opposingPlayer.balance; // player 2 balnace to be sent after updateGame() events

    range lDiceRange = containedState.SETTINGS.dicerange; // localized dice range
    // Evaluate Player Position
    printf("\n[Press ENTER to roll the dice!]\n");
    getchar();
    char strFlair1[] = ".....";
    print1d(strFlair1, strlen(strFlair1), 150,170);
    sleep_ms(800);
    unsigned int roll = rollDice(lDiceRange);
    printf("\nThe dice face says: %d!\n", roll);
    sleep_ms(1000);

    // update player positiion
    currentPlayer.pos += roll;
    currentPlayer.pos %= 9;

    unsigned int pos = currentPlayer.pos;
    updatedGame.arrPlayerContainer[currentPlayerKey] = currentPlayer;
    clear
    showGameStatus(updatedGame);
    bool isHouse = true; // default property type
    // Show position prompt
    pos = 4;
    displayPos(pos);
    sleep_ms(600);
    switch(pos)
    {
        // cases 0,4,6 are non property types and as such, isHouse is inconsequential

        // player lands on Go!
        case 0: 
        {
            char* goMsg = "\n🏁 Go Go Go!' The bank handed you 200 for an extra boost!\n";
            sleep_ms(600);
            pendingPlayerBalance += 200;
            break;
        }
        // player is Jailed :(
        case 4:
        {
            sleep_ms(500);
            clear
            char* jailMsg = malloc (256);
            // int spaces = 44;
            print1d(currentPlayer.name, strlen(currentPlayer.name), 170,190);
            print1d(" just got CAUGHT BY THE POPO'S for TAX EVASION ♀️\n", strlen(" just got CAUGHT BY THE POPO'S for TAX EVASION ♀️\n"),170,190);
            // printf("%*s",spaces," ");
            print1d("\nDon't drop the soap buddy\n",strlen("\nDon't drop the soap buddy 💀\n",220,230));
            currentPlayer.jailedCounter += 1;
            currentPlayer.isJailed = true;
            break;  
        }
        // player lands on feelin' lucky plot
        case 6:
        {
            char* jailMsg = malloc (256);
            // int spaces = 44;
            // printf("%*s",spaces," ");
            print1d("You feelin' lucky?🧙‍️\n",strlen("You feelin' lucky?🧙‍️\n"),230,250);
            printf("\n[PRESS ENTER to roll the dice]\n");
            getchar();
            clear
            sleep_ms(500);
            printf("\nDivining your luck....\n");
            sleep_ms(800);
            int num = rollDice(lDiceRange);
            sleep_ms(500);
            clear
            if(isPrime(num))
            {
                printf("\n🤯You rolled a LUCKY %d!\n",num);
                int luckyNum = getRandNum(
                    containedState.SETTINGS.bonusrange.min,
                    containedState.SETTINGS.bonusrange.max
                    );
                showPersonalBalanceUpdate(pendingOpponentBalance, pendingPlayerBalance + luckyNum);
                pendingPlayerBalance += luckyNum;
                sleep_ms(1000);
            }
            else
            {
                printf("\nLady luck frowns upon you; you rolled a pitiful %d\n",num);
                int unluckyNum = getRandNum(
                    containedState.SETTINGS.penaltyrange.min,
                    containedState.SETTINGS.penaltyrange.max
                    );
                showPersonalBalanceUpdate(pendingPlayerBalance, (pendingOpponentBalance - unluckyNum));
                pendingPlayerBalance -= unluckyNum;
                sleep_ms(1000);
                continuePrompt();
            }
           break;
        }
        case 2: // player lands on the electric company
        case 7: // player lands on the railroad
        {
            isHouse = false;
            // 2 and 7 are non house types and cannot be renovated
        }
        case 1: // player lands on the tree house
        case 3: // player lands on the beach house
        case 5: // player lands on the castle 
        case 8: // player lands on the igloo 
        case 9: // player lands on the farm house
        {
            // instantiate localized statekey
            int STATEKEY = containedState.STATEKEY;

            // get the property index for the current position
            int propIndex = readStatekeyAtIndex(STATEKEY,pos,STATEKEY_OFFSET);

            // flag for enemy property ownership
            bool isOwnedByOpponent = playerOwns(enemyPlayerKey, propIndex);
            // flag for current player property ownership
            bool isOwnedByPlayer = playerOwns(currentPlayerKey, propIndex);
            // check if property has been renovated
            bool isRenovated = (propIndex == 3 || propIndex == 4) && isHouse;
            
            // get the current property's cost
            float propertyCost = getPropertyCost(pos,DEFAULT_ELECTRIC_COST,DEFAULT_RAILROAD_COST);

            // if the property is owned the bank and the player has enough capital, give the player the choice to purchase the property
            if((propIndex == 0) && pendingPlayerBalance >= propertyCost)
            {
                printf("\nPROPERTY COST: [%.2f 💰]",propertyCost);
                if(playerDialogue("\nBuy property")){ // if the player buys the property
                   pendingPlayerBalance -= propertyCost; // subtract from balance
                    containedState.STATEKEY = mutateStatekeyAtIndex(
                        containedState.STATEKEY, pos,
                        currentPlayerKey, STATEKEY_OFFSET
                        ); // update statekey to reflect property purchase
                    printf("\nYou have successfully bought the %s\n",getPropertyName(pos));
                    showPersonalBalanceUpdate((pendingPlayerBalance + propertyCost), pendingPlayerBalance);
                }
            }
            // property is owned by the bank but the player doesn't have enough money
            else if((propIndex == 0) && pendingPlayerBalance < propertyCost)
            {
                printf("\nYou do not have enough money to purchase this property❗");
            }
            // The player has already renovated this property
            else if(isOwnedByPlayer && isRenovated)
            {
                printf("\nYou own this property and have already renovated it 👍");
            }
            // The player owns and has yet to renovate this property
            else if(isOwnedByPlayer && !isRenovated && isHouse) 
            {
                float renovationCost = game.state.SETTINGS.renovationCost; // get the renovation cost from settings
                if(pendingPlayerBalance >= renovationCost) // check if the player has enough capital to renovate the property
                {
                    printf("\nRENOVATION COST: [%.2f 💸]\n",renovationCost); 
                    if(playerDialogue("\nRenovate property")) // ask if the player would like to renovate the property
                    {
                        pendingPlayerBalance -= renovationCost; // player pays the renovation cost
                        containedState.STATEKEY = mutateStatekeyAtIndex( 
                            containedState.STATEKEY, pos,
                            currentPlayerKey+2, STATEKEY_OFFSET // + 2 means the property is renovated
                        ); // update the state key
                        printf("\nYou have successfully renovated the %s\n",getPropertyName(pos));
                        showPersonalBalanceUpdate((pendingPlayerBalance - renovationCost), pendingPlayerBalance);
                    }
                }
                else // The player does not have enough capital to renovate the property
                {
                    printf("\nYou do not have enough capital to renovate this property ❗");
                }
            }
            if(isOwnedByOpponent) // if the property belongs to the opposing player
            {
                printf("\nYou have landed on a property that is owned by %s! Time to pay rent fool!\n",opposingPlayer.name);
                printf("\n[PRESS ENTER TO PAY RENT!]\n");
                getchar();

                float fRent = getRent(pos,roll, // calculate rent
                                    containedState.SETTINGS.electricMulti,
                                    containedState.SETTINGS.railRent);

                fRent = isRenovated ? fRent * 2 + 1 : fRent; // if the property is renovated rent is *2 + 1
                printf("\nRENT: [%.2f 🤑]\n",fRent);

                // check if the player has enough capital to pay rent
                if(pendingPlayerBalance < fRent) 
                {
                    currentPlayer.isBankrupt = true; // for all intents and purposes, you are BANKRUPT!!... until further notice
                    printf("\n...\n");
                    sleep_ms(500);
                    printf("\nUh oh.. It seems as though you don't have enough money to pay rent\n");
                    sleep_ms(500);
                    while(currentPlayer.isBankrupt) // continue displaying the prompt while the player does not have enough money to pay rent
                    {
                        bool playerCanSell = playerOwnsProperties(containedState.STATEKEY,STATEKEY_OFFSET,currentPlayerKey);
                        if(playerCanSell) // if you can sell enough of your properties, the bank might rethink 😏  
                        {
                            // list down Player's properties
                            for (size_t i = 1; i <= 9; i++)
                            {
                                int propID = readStatekeyAtIndex(
                                    containedState.STATEKEY, i,
                                    STATEKEY_OFFSET);
                                if(playerOwns(currentPlayerKey,propID))
                                {
                                    char* strPropName = getPropertyName(i);
                                    printf("[%d]: %s\n",(int)i,strPropName);
                                }
                            }
                            // ask which properties the player would like to sell
                            int toBeSold = getPlayerSellChoice(containedState.STATEKEY, STATEKEY_OFFSET, currentPlayerKey);

                            containedState.STATEKEY = mutateStatekeyAtIndex(
                                containedState.STATEKEY, toBeSold,
                                0, STATEKEY_OFFSET); // reset the value of the property at 0, relinquishing it to the bank

                            float sellPrice = getPropertyCost(toBeSold,DEFAULT_ELECTRIC_COST,DEFAULT_RAILROAD_COST) * 0.5f; // get the cost of the property

                            printf("\n%s SOLD FOR: %.2f\n",getPropertyName(toBeSold),sellPrice);

                            showPersonalBalanceUpdate(pendingPlayerBalance, (pendingPlayerBalance + sellPrice));
                            pendingPlayerBalance += sellPrice; // reimburse the player
                        }
                        if(pendingPlayerBalance >= fRent) // check if player is no longer bankrupt
                        {
                            currentPlayer.isBankrupt = false;
                            clearbuff
                            printf("\nYou now have enough capital to pay rent!\n");
                            printf("\n[PRESS ENTER TO PAY RENT!]\n");
                            getchar();
                        }
                        else if(!playerCanSell) // if the player is still bankrupt and can no longer sell any properties, the player loses
                        {
                            printf("\nThere's nothing you can do to pay rent!\n");
                            updatedGame = saveGame(currentPlayer, currentPlayerKey, 
                                                    opposingPlayer, enemyPlayerKey,
                                                    containedState);
                            continuePrompt();
                            return updatedGame;
                        }

                    }
                }
                sleep_ms(700);
                pendingPlayerBalance -= fRent;
                pendingOpponentBalance += fRent;
            }

        }
    }


    // show UI flair for balance update and game status
    clear
    showGameStatus(updatedGame);
    showBalanceUpdate(
        currentPlayer.balance, pendingPlayerBalance, currentPlayer.name,
        opposingPlayer.balance, pendingOpponentBalance, opposingPlayer.name);

    // save the game 
    currentPlayer.balance = pendingPlayerBalance;
    opposingPlayer.balance = pendingOpponentBalance;
    updatedGame = saveGame(currentPlayer, currentPlayerKey, 
                            opposingPlayer, enemyPlayerKey,
                            containedState);

    continuePrompt();

    //// Save Game
    return updatedGame;
}

/*
    A dynamic game UI component that displays the current status of the game
    @param game the game package containing all game data
*/
void showGameStatus(struct gamepkg game){
    clear
    char* p1Properties = getAllPlayerProperties(game.state.STATEKEY,
                                                STATEKEY_OFFSET, 1);
    char* p2Properties = getAllPlayerProperties(game.state.STATEKEY,
                                                STATEKEY_OFFSET, 2);
    int currentPlayerIndex = game.state.activePlayer - 1;
    Player p1 = game.arrPlayerContainer[0];
    Player p2 = game.arrPlayerContainer[1];
    
    printf("\n%s's Statistics\n",p1.name);
    printf("properties:%s\n", p1Properties);
    printf("position: %d balance: %.2f\n",
     p1.pos, p1.balance
    );
    printf("\n%s's Statistics\n",p2.name);
    printf("properties:%s\n", p2Properties);
    printf("position: %d balance: %.2f\n",
     p2.pos, p2.balance
    );
    if(p1.isJailed){
        printf("\nIMPRISONED: [%s]\n",p1.name);
    }
    if(p2.isJailed){
        printf("\nIMPRISONED: [%s]\n",p2.name);
    }
    char* DIVIDER = createDivider('=',6);
    printf("\n%s[%s's TURN]%s\n",
    DIVIDER,
    game.arrPlayerContainer[currentPlayerIndex].name,
    DIVIDER 
    );
}

/*
    Populates the wincontext list given the context type
    @param arrContext[] a list of contexts that tell the game how a winner was decided
    @param context the wincontext type to use
    @returns arrContext that is populated with the given cwincontext
*/
enum winContext* populateContext(enum winContext arrContext[], enum winContext context){
    if(arrContext[0] != NOCONTEXT && arrContext[1] == NOCONTEXT){
        arrContext[1] = context;
    }
    else{
        arrContext[0] = context;
    }
    return arrContext;
}

/*
    Updates the winstate variable in contained in state and decides who to crown as the winner
    @param winsettings a struct of type winconditions that contains winner determinants
    @param p1 player1's data
    @param p2 player2's data
    @returns an updated winstate that has been through all winsettings checks
*/
struct winstate updateWinState(winconditions winsettings, Player p1, Player p2)
{
    struct winstate localWinstate = winsettings.winstate;
    if(p1.isBankrupt)
    {
        localWinstate.winRationale = populateContext(localWinstate.winRationale, ENEMY_BANKRUPTY);
        localWinstate.winner = PLAYER2;
        return localWinstate;
    }
    
    if(p2.isBankrupt)
    {
        localWinstate.winRationale = populateContext(localWinstate.winRationale, ENEMY_BANKRUPTY);
        localWinstate.winner = PLAYER2;
        return localWinstate;
    }

    unsigned int requiredFlags = winsettings.isSimul ? 2 : 1;
    unsigned int p1Flags = 0;
    unsigned int p2Flags = 0;

    bool checkLosingBalance = winsettings.arrWintoggles[0] == DISABLED ? false : true;
    bool checkWinningBalance = winsettings.arrWintoggles[1] == DISABLED ? false : true;

    float floor = winsettings.losingBalance;
    float ceil = winsettings.winningBalance;
    
    if(checkLosingBalance)
    {
        if(p1.balance <= floor)
        {
            p2Flags += 1;
            populateContext(localWinstate.winRationale, ENEMY_LOSING_BALANCE);
        }

        else if(p2.balance <= floor)
        {
            p1Flags += 1;
            populateContext(localWinstate.winRationale, ENEMY_LOSING_BALANCE);
        }
    }
    if(checkWinningBalance)
    {
        if(p1.balance >= ceil)
        {
            p1Flags += 1;
            populateContext(localWinstate.winRationale, REACHED_WINNING_BALANCE);
        }
        else if(p2.balance >= ceil)
        {
            p2Flags += 1;
            populateContext(localWinstate.winRationale, REACHED_WINNING_BALANCE);
        }
    }

    if(requiredFlags == p2Flags || requiredFlags == p1Flags)
    {
        if(p2Flags == requiredFlags)
            localWinstate.winner = PLAYER2;

        else if(p1Flags == requiredFlags)
            localWinstate.winner = PLAYER1;

        else
            localWinstate.winner = TIE;
    }

    return localWinstate;
}