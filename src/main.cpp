#include "MainLoop.hpp"
#include "raylib.h"
#include "Window.hpp"
#include <cstdio>
#include <iostream>

#include "raygui-implement.h"

int main(int argc, const char** argv) {

    MainLoop loop{};

    while(!MainLoop::ShouldClose()){
        MainLoop::Update();
    }
    return 0;
}