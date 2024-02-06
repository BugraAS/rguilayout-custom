#include "GUI.hpp"
#include "Button.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include <memory>

bool GUI::childOf(Node *n){
    return isOrphan()? false :parent->childOf(n);
}

Vector3 GUI::getTransform(){
    if(isOrphan())
        return {0,0,1};
    Rectangle trans = parent->recurseRec({0,0,1,1});
    return {trans.x, trans.y, trans.width};
}

Rectangle GUI::getGRectangle(){
    return isOrphan() ? getRectangle() : parent->recurseRec(getRectangle());
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
    if(this->parent)
        this->parent->removeGui(this);
    if(parent)
        parent->addGui(this);
    this->parent = parent;
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

GUI* GUI::_from_type(GUITYPE type){
    switch (type._value) {
        case GUITYPE::BUTTON: return new Button();
        default: return nullptr;
    }
}