#include "InputHandle.hpp"


InputHandle* InputHandle::singleton = nullptr;

InputHandle::InputHandle()
: keyMap()
{
    singleton = this;
}
InputHandle::~InputHandle(){
    singleton = nullptr;
}

void InputHandle::process(){
    //TODO: Handle inputs
    //we will ignore this for now since everything is based on clicks
}

void InputHandle::mapKey(int keyCode, InputEvent::ENUM eventType) {
    singleton->keyMap[keyCode] = {eventType};
}

void InputHandle::unmapKey(int keyCode) {
    singleton->keyMap.erase(keyCode);
}

void InputHandle::clearKeyMappings() {
    singleton->keyMap.clear();
}