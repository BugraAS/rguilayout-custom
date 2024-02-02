#pragma once

#include "GUI.hpp"
#include "Node.hpp"
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
    GROUP,
    UNGROUP,
    NUM_TOOLS
)
namespace Tool {
    void Select() __attribute__((weak));
    void Move() __attribute__((weak));
    void Resize() __attribute__((weak));
    void Pan() __attribute__((weak));
    void Create() __attribute__((weak));
    void Interact() __attribute__((weak));
    void Group() __attribute__((weak));
    void Ungroup() __attribute__((weak));

    void Delete();

    extern GUITYPE createChoice;
    extern bool createFlag;

    extern std::set<GUI*> selectGUI;
    extern Node* selectNODE;
    extern GUI* selectHover;
    extern bool selectedSingle;
    extern bool selectedGui;

    extern bool snapToGrid;

    extern Rectangle resizeArea;

    extern bool groupChoosing;
}