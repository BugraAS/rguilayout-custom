#pragma once

#include "GUI.hpp"
#include "enum.h"
#include <set>
#include <vector>
BETTER_ENUM(TOOL, int,
    SELECT,
    MOVE,
    RESIZE,
    PAN,
    CREATE,
    INTERACT,
    NUM_TOOLS
)
namespace Tool {
    void Select() __attribute__((weak));
    void Move() __attribute__((weak));
    void Resize() __attribute__((weak));
    void Pan() __attribute__((weak));
    void Create() __attribute__((weak));
    void Interact() __attribute__((weak));

    extern GUITYPE createChoice;
    extern bool createFlag;

    extern std::set<GUI*> selectGUI;
    extern GUI* selectHover;

    extern bool snapToGrid;

    extern Rectangle resizeArea;
}