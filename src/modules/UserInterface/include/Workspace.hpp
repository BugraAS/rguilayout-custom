#pragma once

#include "raylib.h"
namespace Workspace {
    extern Rectangle rec;
    extern float increment;
    extern bool gridVisible;

    Vector2 posGtoGrid(Vector2 pos);
    Vector2 posGtoR(Vector2 pos);
    Rectangle recGtoR(Rectangle rec);
    void Draw();
    void Resize();
}