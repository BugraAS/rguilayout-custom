#include "Global.hpp"
#include "State.hpp"
#include "tool.hpp"

STATE G::state{STATE::BASE};
TOOL G::curTool{TOOL::SELECT};
void (*G::tools[TOOL::NUM_TOOLS])(){
    Tool::Select,
    Tool::Move,
    Tool::Resize,
    Tool::Pan,
    Tool::Create,
    Tool::Interact,
};