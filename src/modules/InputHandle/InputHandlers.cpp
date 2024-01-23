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

InputProcessor::InputProcessor()
: keyMap()
{
    singleton = this;

    keyMap[STATE::EXITING][KEY_ESCAPE] = EXITING_ESCAPE;
    keyMap[STATE::EXITING][KEY_ENTER] = EXITING_ENTER;
}