#include "MainLoop.hpp"
#include "InputProcessor.hpp"
#include "RendererDefault.hpp"
#include "Scene.hpp"
#include "Window.hpp"
#include "raylib.h"
#include <memory>


MainLoop* MainLoop::singleton = nullptr;

MainLoop::MainLoop()
: processes(), window(), scene(std::make_unique<Scene>())
{
#ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif // !NDEBUG
    isRunning = true;
    singleton = this;
    int wflags = 0;
#if defined(PLATFORM_DESKTOP)
    wflags |= FLAG_WINDOW_RESIZABLE;
    window.Init(0,0,"Bloody",wflags);
#else
    window.Init();
#endif
    window.SetTargetFPS(60);
    SetExitKey(0);

    processes.push_back(std::make_unique<InputProcessor>());
    processes.push_back(std::make_unique<RendererDefault>());

    return;
}
void MainLoop::Update(){
    for(auto &process: singleton->processes){
        process->process();
    }
}
MainLoop::~MainLoop(){ // WONT RUN IN WEB. The default is to abort code mid-execution if page closes
    singleton = nullptr;
    return;
}

MainLoop* MainLoop::getSingleton(){
    return singleton;
}