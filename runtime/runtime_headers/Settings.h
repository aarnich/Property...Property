
#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H
#include "../../typedefs/stateTypes.h"
#include "../../typedefs/gameTypes.h"
#include "../../libdefs/SettingsEvents.h"
#include "../../libdefs/InputTools.h"
/*
    Header file for Settings.c
    Author: Aaron Nicholas Lizardo Gumapac
*/

// Primary settings screen function

struct settings settingsPrompt(struct settings initsettings);
#endif