#include "BottomMenu.hpp"
#include "GUI.hpp"
#include "Global.hpp"
#include "Scene.hpp"
#include "tool.hpp"
#include <vector>

bool Tool::groupChoosing = false;

void Tool::Group(){
    static bool choosingGui = true;
    static std::vector<GUI*> cache{};
    static Node* cacheNode = nullptr;

    if(G::curTool != G::lastTool){
        cache.clear();
        groupChoosing = false;
    }
    if(!groupChoosing){
        choosingGui = selectedGui;
        if(selectedGui){
            cache.clear();
            cache.assign(selectGUI.begin(),selectGUI.end());
        }else{//Node selected
            cache.clear();
            cacheNode = selectNODE;
            if(cacheNode == Scene::getRoot())
                return;
        }
        groupChoosing = true;
    }
    if(!choosingGui & (cacheNode == selectNODE))
        return;
    BottomMenu::setMessage("Please select a Node as parent");
    if(selectedGui)
        return;
    Node* n = new Node();
    n->setParent(selectNODE);
    for(GUI* g: cache){
        g->setParent(n);
    }
    groupChoosing = false;
    cache.clear();
}