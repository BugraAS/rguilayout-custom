#include "Cursor.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Workspace.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "raymath.h"
#include "tool.hpp"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <queue>

bool Tool::snapToGrid = false;

void Tool::Move(){
    static bool dragging = false;

    if(selectGUI.empty()){
        dragging = false;
        return;
    }
    static Vector2 pin{};
    static Vector2 olddelta{};

    Vector2 mouse = Workspace::posGtoR(GetMousePosition());
    bool hold = Cursor::IsInputted(CURSOR::HOLD);
    if(hold & !dragging){
        pin = mouse;
        dragging = true;
    }
    if(!hold | !dragging){
        dragging = false;
        olddelta = {};
        return;
    }
    float increment = Workspace::increment;
    if(Vector2LengthSqr(pin - mouse) < (increment*increment))
        return;

    Vector2 delta = mouse - pin;
    delta = {
        delta.x - fmodf(delta.x, increment),
        delta.y - fmodf(delta.y, increment),
    };
    Vector2 temp = delta - olddelta;
    olddelta = delta;

    for(GUI* gui: selectGUI)
        gui->offsetPos(temp);
}