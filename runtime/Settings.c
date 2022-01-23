#include "runtime_headers/Settings.h"


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
        printf("[D] Reset settings\n");
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