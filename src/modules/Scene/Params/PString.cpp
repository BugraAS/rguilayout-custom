#include "PString.hpp"
#include "raylib.h"
#include <string>

void* PString::getData(){
    if (data.empty())
        return nullptr;
    return (void*)data.c_str();
}
void PString::setData(void* data){
    this->data = *((std::string*)(data));
}