#include "raylib.h"
#include "Window.hpp"
#include <cstdio>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

int main(int argc, const char** argv) {
    int screenDim[2] ={GetScreenWidth(), GetScreenHeight()};

    raylib::Window window(screenDim[0],screenDim[1]);

    bool closeWindow = false;
    bool confirmCloseWindow = false;

    window.SetTargetFPS(60);
    SetExitKey(0);

    while(!closeWindow){
        // closeWindow = window.ShouldClose();
        confirmCloseWindow |= window.ShouldClose();
        BeginDrawing();
            if(confirmCloseWindow){
                int result = GuiMessageBox(Rectangle{GetScreenWidth()/2.0f - 320/2.0f, GetScreenHeight()/2.0f - 120/2.0f, 320, 120}, "Gui Editor", "Are you sure you want to exit?", "Yes;No");
                closeWindow = result == 1;
                confirmCloseWindow = result == -1;
            }
            ClearBackground(RAYWHITE);
            DrawFPS(10, 10);
        EndDrawing();
    }

    printf("Screen size is: %d, %d\n",screenDim[0],screenDim[1]);
    return 0;
}