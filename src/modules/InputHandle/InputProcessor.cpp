#include "InputProcessor.hpp"
#include "Global.hpp"
#include "State.hpp"
#include "raylib.h"


InputProcessor* InputProcessor::singleton = nullptr;

InputProcessor::~InputProcessor(){
    singleton = nullptr;
}

void InputProcessor::process(){
    int flag = 0;
    flag |= KeyFlag::L_SHIFT*IsKeyDown(KEY_LEFT_SHIFT);
    flag |= KeyFlag::R_SHIFT*IsKeyDown(KEY_RIGHT_SHIFT);
    flag |= KeyFlag::L_CTRL*IsKeyDown(KEY_LEFT_CONTROL);
    flag |= KeyFlag::R_CTRL*IsKeyDown(KEY_RIGHT_CONTROL);
    for(int key = GetKeyPressed(); key != 0; key = GetKeyPressed()){
        key |= flag;
        InputHandler handler = keyMap[G::state][key];
        if(handler)
            handler();
    }
    if(WindowShouldClose())
        G::state = STATE::EXITING;
}

void InputProcessor::mapKey(STATE::ENUM state, int keyCode, InputHandler handler){
    singleton->keyMap[state][keyCode] = {handler};
}

void InputProcessor::unmapKey(STATE::ENUM state, int keyCode) {
    singleton->keyMap[state].erase(keyCode);
}

void InputProcessor::clearKeyMappings() {
    for(int i = 0; i < STATE::NUM_STATES; i++)
        singleton->keyMap[i].clear();
}