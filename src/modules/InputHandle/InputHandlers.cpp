#include "Global.hpp"
#include "InputProcessor.hpp"
#include "MainLoop.hpp"
#include "State.hpp"
#include "raylib.h"

static void EXITING_ESCAPE(){
    G::state = STATE::BASE;
}
static void EXITING_ENTER(){
    MainLoop::Close();
}
static void BASE_ESCAPE(){
    G::state = STATE::EXITING;
}

InputProcessor::InputProcessor()
: keyMap()
{
    singleton = this;

    keyMap[STATE::BASE][KEY_ESCAPE] = BASE_ESCAPE;
    keyMap[STATE::EXITING][KEY_ESCAPE] = EXITING_ESCAPE;
    keyMap[STATE::EXITING][KEY_ENTER] = EXITING_ENTER;
}