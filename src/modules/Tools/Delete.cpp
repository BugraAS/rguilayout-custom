#include "Scene.hpp"
#include "tool.hpp"
#include <vector>
void Tool::Delete(){
    groupChoosing = false;

    if(selectedGui){
        for(GUI* gui: selectGUI){
            gui->setParent(nullptr);
            delete gui;
        }
        selectGUI.clear();
        return;
    }
    //selected NODE
    if((selectNODE == nullptr)|(selectNODE == Scene::getRoot()))
        return;

    selectNODE->setParent(nullptr);
    delete selectNODE;
    selectNODE = nullptr;
}