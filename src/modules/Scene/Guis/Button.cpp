#include "Button.hpp"
#include "Param.hpp"
#include <vector>
#include "raygui-implement.h"
std::vector<Param*> Button::getParams(){
    return {&rectangle, &text};
}
void Button::draw(){
    raygui::GuiButton(getRectangle(), (char*)text.getData());
}