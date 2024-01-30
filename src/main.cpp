#include "MainLoop.hpp"

#ifdef PLATFORM_WEB
    #include "emscripten/emscripten.h"
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif // PLATFORM_WEB


int main(int argc, const char** argv) {

    MainLoop loop{};

    #ifdef PLATFORM_DESKTOP
    while(!MainLoop::ShouldClose())
        MainLoop::Update();
    #else
    emscripten_set_main_loop(MainLoop::Update, 0, true);
    #endif // PLATFORM_DESKTOP
    return 0;
}