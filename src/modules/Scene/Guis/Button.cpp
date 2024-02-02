#include "Button.hpp"
#include "GUI.hpp"
#include "Param.hpp"
#include <vector>
#include "raygui-implement.h"
std::vector<Param*> Button::getParams(){
    return {&rectangle, &text};
}
void Button::draw(){
    raygui::GuiButton(getGRectangle(), (char*)text.getData());
}
GUI* Button::copy(){
    Button *out = new Button();
    out->label = label;
    out->setRectangle(getRectangle());
    out->text.setData(text.getData());
    return out;
}