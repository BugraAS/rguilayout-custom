#include "PString.hpp"
#include "raylib.h"
#include <string>

void* PString::getData(){
    if (data.empty())
        return nullptr;
    return data.data();
}
void PString::setData(void* data){
    this->data = *((std::string*)(data));
}