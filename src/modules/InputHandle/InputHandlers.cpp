#include "Global.hpp"
#include "InputProcessor.hpp"
#include "Keymap.hpp"
#include "MainLoop.hpp"
#include "State.hpp"
#include "raylib.h"
#include "tool.hpp"
#include <cstdio>

static void EXITING_CANCEL(){
    G::state = STATE::BASE;
}
static void EXITING_CONFIRM(){
    MainLoop::Close();
}
static void BASE_CANCEL(){
    switch (G::curTool._value) {
        case TOOL::SELECT:
            Tool::selectGUI.clear();
            break;
        case TOOL::CREATE:
            Tool::createFlag = false;
            break;
    }
}
static void BASE_CONFIRM(){//BUG: Keybinds are not working
    printf("You pressed CONFIRM\n");
}

InputHandler InputProcessor::handles[STATE::NUM_STATES][KEYMAP::NUM_INPUTS]{};

InputProcessor::InputProcessor()
: keyMap(), inversekeyMap()
{
    singleton = this;

    mapKey(STATE::BASE, KEYMAP::CONFIRM, KEY_ENTER);
    mapKey(STATE::EXITING, KEYMAP::CONFIRM, KEY_ENTER);
    mapKey(STATE::BASE, KEYMAP::CANCEL, KEY_ESCAPE);
    mapKey(STATE::EXITING, KEYMAP::CANCEL, KEY_ESCAPE);


    handles[STATE::BASE][KEYMAP::CONFIRM] = BASE_CONFIRM;
    handles[STATE::BASE][KEYMAP::CANCEL] = BASE_CANCEL;

    handles[STATE::EXITING][KEYMAP::CONFIRM] = EXITING_CONFIRM;
    handles[STATE::EXITING][KEYMAP::CANCEL] = EXITING_CANCEL;

}