#include "MainLoop.hpp"
#include "RendererDefault.hpp"
#include "Window.hpp"
#include "raylib.h"
#include <memory>


MainLoop* MainLoop::singleton = nullptr;

MainLoop::MainLoop()
: processes(), window(0,0)
{
#ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif // !NDEBUG
    isRunning = true;
    singleton = this;
    SetExitKey(0);
    window.SetTargetFPS(60);

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