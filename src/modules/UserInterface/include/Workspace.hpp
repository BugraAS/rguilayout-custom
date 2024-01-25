#pragma once

#include "raylib.h"
namespace Workspace {
    extern Rectangle rec;
    extern float increment;
    extern bool gridVisible;

    void Draw();
    void Resize();
}