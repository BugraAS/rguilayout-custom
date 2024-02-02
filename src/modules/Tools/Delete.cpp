#include "Scene.hpp"
#include "tool.hpp"
void Tool::Delete(){
    groupChoosing = false;
    selectGUI.clear();

    if(selectedGui){
        for(GUI* gui: selectGUI){
            gui->setParent(nullptr);
            delete gui;
        }
        return;
    }
    //selected NODE
    if((selectNODE == nullptr)|(selectNODE == Scene::getRoot()))
        return;

    selectNODE->setParent(nullptr);
    delete selectNODE;
    selectNODE = nullptr;
}