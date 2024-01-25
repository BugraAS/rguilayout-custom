#include "Global.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "tool.hpp"

void Tool::Pan(){
    bool held = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    if(held){
        Vector2 delta = GetMouseDelta();
        Node* root = Scene::getRoot();
        root->pos = delta + root->pos;
    }
}