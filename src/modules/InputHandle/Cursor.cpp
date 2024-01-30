#include "Cursor.hpp"
#include "raylib.h"

bool Cursor::IsInputted(CURSOR::_enumerated input){
    switch (input) {
        case CURSOR::CLICK:
            return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        case CURSOR::RCLICK:
            return IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
        case CURSOR::HOLD:
            return !IsMouseButtonPressed(MOUSE_LEFT_BUTTON) & IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        case CURSOR::RELEASE:
            return IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        case CURSOR::SCROLL:
            return 0.0f != GetMouseWheelMove();
        default:
            return false;
    }
}