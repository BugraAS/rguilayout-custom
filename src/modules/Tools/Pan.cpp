#include "Cursor.hpp"
#include "Scene.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "raymath.h"
#include "tool.hpp"
#include <math.h>

void Tool::Pan(){
    bool held = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    if(held){
        Vector2 delta = GetMouseDelta();
        Scene::deltaOffset(delta);
    }
    if(Cursor::IsInputted(CURSOR::SCROLL)){
        Scene::deltaZoom(1.0f + GetMouseWheelMove()*0.01);
        Scene::setZoom(Clamp(Scene::getZoom(), 0.25f, 2.0f));
    }

}