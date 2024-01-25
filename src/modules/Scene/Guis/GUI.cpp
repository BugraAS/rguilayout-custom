#include "GUI.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include <memory>

Vector2 GUI::getGPos(){
    Vector2 temp = getPos();
    return parent ? temp + parent->getGPos() : temp ;
}

Vector2 GUI::getPos(){
    Rectangle temp = getRectangle();
    return {temp.x,temp.y};
}
Vector2 GUI::getDim(){
    Rectangle temp = getRectangle();
    return {temp.width,temp.height};
}

void GUI::setParent(Node* parent){
    if(parent == this->parent)
        return;
    this->parent->removeGui(this);
    if(parent)
        parent->getGuis().push_back(std::unique_ptr<GUI>(this));
}

GUI::~GUI(){
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