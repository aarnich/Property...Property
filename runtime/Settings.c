#include "runtime_headers/Settings.h"


struct settings settingsPrompt(struct settings initsettings){
    char cSettingsSelect;
    do{ // while the player has yet to press 'G', continue displaying the settings screen
        clear
        displayCurrentConfig(initsettings); // defined in SettingsUI.c, used to display current settings
        printf("[1] Edit win conditions\n");
        printf("[2] Edit renovation cost\n");
        printf("[3] Edit railroad rent\n");
        printf("[4] Edit railroad purchase cost\n");
        printf("[5] Edit the electric company's multiplier\n");
        printf("[6] Edit the electric company's purchase cost\n");
        printf("[7] Edit feeling lucky range\n");
        printf("[8] Edit dice faces\n");
        printf("[9] Edit Go! tile bonus amount\n");
        printf("[0] Edit passing Go! bonus amount\n");
        newL
        setRed
        printf("[D] Reset settings\n");
        resetColor
        setGreen
        printf("[S] Save and Exit \n\n");
        resetColor
        char validSettingsInput[12] = "123456789DS0";
        cSettingsSelect = handleInput(validSettingsInput,12); 
        switch(cSettingsSelect){
            case '1':
                initsettings.winsettings = winconditionsMenu(initsettings.winsettings);
                break;
            case '2':
                changeIntParam(&initsettings.renovationCost, "Enter renovation cost: ");
                break;
            case '3':
                changeIntParam(&initsettings.railRent, "Enter railroad rent: ");
                break;
            case '4':
                changeIntParam(&initsettings.railCost, "Enter railroad purchase cost: ");
                break;
            case '5':
                changeIntParam(&initsettings.electricMulti, "Enter electric co. multiplier: ");
                break;
            case '6':
                changeIntParam(&initsettings.electricCost, "Enter electric co. purchase cost: ");
                break;
            case '7':
                feelingLuckySubMenu(
                    &initsettings.bonusrange,
                    &initsettings.penaltyrange
                    );
                break;
            case '8':
                changeIntParam(&initsettings.dicerange.max, "How many faces should the dice have (6 default) ?: ");
                break;
            case '9':
                changeIntParam(&initsettings.goBonus, "Enter Go! tile bonus amount: ");
                break;
            case '0':
                changeIntParam(&initsettings.passingGo, "Enter passing Go! bonus amount: ");
                break;
            case 'D':
                initsettings = initializeSettings();
            default:
                break;
            }
        }while(cSettingsSelect != 'S');
        setGreen
        printf("\nConfig Saved!\n\n");
        resetColor

    return initsettings;
}