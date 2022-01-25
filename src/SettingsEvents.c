#include "../libdefs/SettingsEvents.h"
/*
    all initializers always output the same data
*/

/*
    This function returns initial values for struct winstate
    Preconditions: none
    @return the initial winstate (initwinstate) 
*/
struct winstate initializeWinstate(){
    struct winstate initwinstate; // contains game winner parameters
    initwinstate.winRationale = malloc (256);
    initwinstate.winRationale[0] = NOCONTEXT; // no context needed 
    initwinstate.winRationale[1] = NOCONTEXT; // no context needed 
    initwinstate.winner = NONE; // no winners decided

    return initwinstate;
}

/*
    This function returns initial values for struct winconditions
    Preconditions: none
    @return the initial winconditions (initwinconds) 
*/
struct winconditions initializeWinconditions(){
    struct winconditions initwinconds; // tells the game how to decide the winner and which parameters to check
    initwinconds.arrWintoggles[0] = DISABLED; 
    initwinconds.arrWintoggles[1] = DISABLED; // the game is initialized at 1 winning condition only
    initwinconds.isSimul = false; // only one condition must be satisfied
    initwinconds.losingBalance = DEFAULT_LOSING_BALANCE; // 
    initwinconds.winningBalance = DEFAULT_WINNING_BALANCE;
    initwinconds.winstate = initializeWinstate();

    return initwinconds;
}

/*
    This function returns initial values for struct settings
    @return the initial values for settings (initsettings)
*/
struct settings initializeSettings(){
    struct settings initsettings;
    initsettings.bonusrange.max = DEFAULT_BONUS_MAX;
    initsettings.bonusrange.min = DEFAULT_BONUS_MIN;
    initsettings.penaltyrange.max = DEFAULT_PENALTY_MAX;
    initsettings.penaltyrange.min = DEFAULT_PENALTY_MIN;
    initsettings.electricMulti = DEFAULT_ELECTRIC_MULTI;
    initsettings.electricCost = DEFAULT_ELECTRIC_COST;
    initsettings.railRent = DEFAULT_RAILROAD_RENT;
    initsettings.railCost = DEFAULT_RAILROAD_COST;
    initsettings.winsettings = initializeWinconditions();
    initsettings.dicerange.max = DEFAULT_DICE_MAX;
    initsettings.dicerange.min = DEFAULT_DICE_MIN; 
    initsettings.renovationCost = DEFAULT_RENOVATION_COST;
    initsettings.goBonus = DEFAULT_GO_BONUS;
    return initsettings;
}

/*
    This function dsplays a menu used to modify initial win conditions
    Precondition: initwinconds have been initialized with initializeWinconditions()
    @param wincond initial values for winconditions; this structure tells the game how to decide a winner
*/
struct winconditions winconditionsMenu(winconditions wincond){

    bool isMulti = checkIfMulti(wincond.arrWintoggles[0], wincond.arrWintoggles[1]);
    displayWinconditionsMenu(wincond);
    newL
    char validInputs[6] = {'1','2','3','4','E','S'};
    char cSelection = handleInput(validInputs,6);
    switch(cSelection){
        case '1':
            if(wincond.arrWintoggles[0] == DISABLED)
                wincond.arrWintoggles[0] = LOSING_BALANCE_REACHED;
            else
                wincond.arrWintoggles[0] = DISABLED;
            break;
        case '2':
            if(wincond.arrWintoggles[1] == DISABLED)
                wincond.arrWintoggles[1] = WINNING_BALANCE_REACHED;
            else
                wincond.arrWintoggles[1] = DISABLED;
            break;
        case '3':
            if(wincond.arrWintoggles[0] != DISABLED){
                float tmpLosingBal;
                changeFloatParam(&tmpLosingBal,"Enter losing balance: ");
                wincond.losingBalance = tmpLosingBal;
            }
            break;
        case '4':
            if(wincond.arrWintoggles[1] != DISABLED){
                float tmpWinBal;
                changeFloatParam(&tmpWinBal, "Enter winning balance: ");
                wincond.winningBalance = tmpWinBal;
            }
            break;
        case 'E':
            if(isMulti){
                if(wincond.isSimul == false)
                    wincond.isSimul = true;
                else
                    wincond.isSimul = false;
            }
            break;
        case 'S':
            return wincond;
    }
    return winconditionsMenu(wincond);
}

//primary function for SettingsEvents
/*
    This function displays a menu used to modify initial game settings
    Precondition: initsettings have been initialized with initializeSettings()
    @param initsettings initial values for game setttings
    @return game settings as modified by the user(s)
*/
struct settings settingsPrompt(struct settings initsettings){
    char cSettingsSelect;
    do{ // while the player has yet to press 'G', continue displaying the settings screen
        clear
        displayCurrentConfig(initsettings); // defined in SettingsUI.c, used to display current settings
        printf("[1] Edit win conditions\n");
        printf("[2] Edit renovation cost\n");
        printf("[3] Edit railroad rent\n");
        printf("[4] Edit the electric company's multiplier\n");
        printf("[5] Edit feeling lucky range\n");
        newL
        printf("[D] Reset settings\n");
        newL
        printf("[G] Start game \n\n");
        char validSettingsInput[7] = {'1','2','3','4','5','D','G'};
        cSettingsSelect = handleInput(validSettingsInput,7); 
        switch(cSettingsSelect){
            case '1':
                initsettings.winsettings = winconditionsMenu(initsettings.winsettings);
                break;
            case '2':
                changeFloatParam(&initsettings.renovationCost, "Enter renovation cost: ");
                break;
            case '3':
                changeFloatParam(&initsettings.railRent, "Enter railroad rent: ");
                break;
            case '4':
                changeFloatParam(&initsettings.electricMulti, "Enter electric co. multiplier: ");
                break;
            case '5':
                feelingLuckySubMenu(
                    &initsettings.bonusrange,
                    &initsettings.penaltyrange
                    );
                break;
            case 'D':
                initsettings = initializeSettings();
            default:
                break;
            }
        }while(cSettingsSelect != 'G');

    return initsettings;
}

/*
    This method shows a menu that enables the user to customize the range of
    Feelin' Lucky bonuses and pentalties
    @Preconditions: ptrBonus and ptrPenalty point to non null ranges
    @param ptrBonus the pointer for the bonus range used in settings
    @param ptrPenalty the pointer for the penalty range used in settings
*/
void feelingLuckySubMenu(range* ptrBonus, range* ptrPenalty){
    {
        char cSettingsSelect = ' ';
        do
        {
            clear
            printf("[W] Edit bonus range\n");
            printf("[S] Edit penalty range\n");
            printf("[B] Go Back\n");
            char subMenuInput[3] = {'W','S','B'};
            cSettingsSelect = handleInput(subMenuInput,3);
            switch(cSettingsSelect){
                case 'W':
                    range initBonus; // localize in order to avoid null value errors
                    initBonus.max = DEFAULT_BONUS_MAX;
                    initBonus.min = DEFAULT_BONUS_MIN;
                    *ptrBonus = editRange(initBonus, "bonus");
                    break;
                case 'S':
                    range initPenalty ; // localize in order to avoid null value errors
                    initPenalty.max = DEFAULT_PENALTY_MAX;
                    initPenalty.min = DEFAULT_PENALTY_MIN;
                    *ptrPenalty = editRange(initPenalty, "bonus");
                    break;
                default:
                    break;
            }
        } while (cSettingsSelect != 'B');
    }
}
