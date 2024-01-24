#include "GUI.hpp"
#include <memory>

void GUI::setParent(Node* parent){
    if(parent == this->parent)
        return;
    this->parent->removeGui(this);
    if(parent)
        parent->getGuis().push_back(std::unique_ptr<GUI>(this));
}

GUI::~GUI(){
    if(parent)
        setParent(nullptr);
}

void GUI::offsetPos(Vector2 delta){
    Rectangle temp = getRectangle();
    temp.x += delta.x;
    temp.y += delta.y;
    setRectangle(temp);
}
void GUI::offsetDim(Vector2 delta){
    Rectangle temp = getRectangle();
    temp.width += delta.x;
    temp.height += delta.y;
    setRectangle(temp);
}
void GUI::setPos(Vector2 pos){
    Rectangle temp = getRectangle();
    temp.x = pos.x;
    temp.y = pos.y;
    setRectangle(temp);
}
void GUI::setDim(Vector2 size){
    Rectangle temp = getRectangle();
    temp.width = size.x;
    temp.height = size.y;
    setRectangle(temp);
}