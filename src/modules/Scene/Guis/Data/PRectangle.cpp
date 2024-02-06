#include "PRectangle.hpp"
#include "raylib.h"

void* PRectangle::getData(){
    return &data;
}
void PRectangle::setData(void* data){
    this->data = *((Rectangle*)(data));
}