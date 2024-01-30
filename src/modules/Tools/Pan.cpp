#include "Cursor.hpp"
#include "Scene.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "raymath.h"
#include "tool.hpp"
#include <math.h>

void Tool::Pan(){
    bool held = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    Node* root = Scene::getRoot();
    if(held){
        Vector2 delta = GetMouseDelta();
        root->pos = delta + root->pos;
    }
    if(Cursor::IsInputted(CURSOR::SCROLL)){
        root->scale *= 1.0f + GetMouseWheelMove()*0.01;
        root->scale = Clamp(root->scale, 0.25f, 2.0f);
    }

}