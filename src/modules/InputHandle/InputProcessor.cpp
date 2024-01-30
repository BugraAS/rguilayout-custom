#include "InputProcessor.hpp"
#include "Global.hpp"
#include "State.hpp"
#include "raylib.h"
#include <algorithm>
#include <cstdio>
#include <vector>


InputProcessor* InputProcessor::singleton = nullptr;

InputProcessor::~InputProcessor(){
    singleton = nullptr;
}

void InputProcessor::process(){
    //TODO: CHANGE HERE
    int flag = 0;
    flag |= KeyFlag::L_SHIFT*IsKeyDown(KEY_LEFT_SHIFT);
    flag |= KeyFlag::R_SHIFT*IsKeyDown(KEY_RIGHT_SHIFT);
    flag |= KeyFlag::L_CTRL*IsKeyDown(KEY_LEFT_CONTROL);
    flag |= KeyFlag::R_CTRL*IsKeyDown(KEY_RIGHT_CONTROL);
    for(int key = GetKeyPressed(); key != 0; key = GetKeyPressed()){
        key |= flag;
        int map = keyMap[G::state][key];
        InputHandler handler = handles[G::state][map];
        if(handler)
            handler();
    }

    if(WindowShouldClose())
        G::state = STATE::EXITING;
}

void InputProcessor::mapKey(STATE state, KEYMAP map, int keyCode){
    singleton->keyMap[state][keyCode] = map;
    singleton->inversekeyMap[state][map._value].push_back(keyCode);
}

void InputProcessor::unmapKey(STATE state, KEYMAP map, int keyCode) {
    singleton->keyMap[state].erase(keyCode);
    std::vector<int> &inverse = singleton->inversekeyMap[state][map];
    std::vector<int>::iterator res = inverse.begin();
    if((res = std::find(inverse.begin(),inverse.end(),keyCode))!= inverse.end())
    {
        inverse.erase(res);
    }
}

void InputProcessor::clearKeyMappings() {
    for(int i = 0; i < STATE::NUM_STATES; i++)
        singleton->keyMap[i].clear();
}