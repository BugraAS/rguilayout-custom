#include "Global.hpp"
#include "InputProcessor.hpp"
#include "MainLoop.hpp"
#include "State.hpp"
#include "raylib.h"
#include "tool.hpp"

static void EXITING_ESCAPE(){
    G::state = STATE::BASE;
}
static void EXITING_ENTER(){
    MainLoop::Close();
}
static void BASE_ESCAPE(){
    switch (G::curTool._value) {
        case TOOL::CREATE:
            Tool::createFlag = false;
            break;
    }
}

InputProcessor::InputProcessor()
: keyMap()
{
    singleton = this;

    keyMap[STATE::BASE][KEY_ESCAPE] = BASE_ESCAPE;
    keyMap[STATE::EXITING][KEY_ESCAPE] = EXITING_ESCAPE;
    keyMap[STATE::EXITING][KEY_ENTER] = EXITING_ENTER;
}