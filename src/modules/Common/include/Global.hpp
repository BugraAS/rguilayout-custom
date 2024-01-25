#pragma once

#include "State.hpp"
#include "tool.hpp"
namespace G {
    extern STATE state;
    extern TOOL curTool;
    extern void (*tools[TOOL::NUM_TOOLS])();
}