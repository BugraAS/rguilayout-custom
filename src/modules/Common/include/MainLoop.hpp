#pragma once

//Intentionally didn't implement a singleton baseclass.
#include "Runnable.hpp"
#include "Scene.hpp"
#include "Window.hpp"
#include <memory>
#include <vector>
class MainLoop {
public:
    raylib::Window window;
private:
    static MainLoop* singleton;
    std::vector<std::unique_ptr<Runnable>> processes;
    std::unique_ptr<Scene> scene;
    bool isRunning;
public:
    static MainLoop *getSingleton();
    static void Update(); // Per frame update function.
    static inline bool ShouldClose(){return !singleton->isRunning;}
    static inline void Close(){singleton->isRunning = false;}
    MainLoop();   // Allocate resources for runtime
    ~MainLoop(); // Save progress and free resources
};