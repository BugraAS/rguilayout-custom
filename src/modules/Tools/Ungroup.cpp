#include "BottomMenu.hpp"
#include "GUI.hpp"
#include "Global.hpp"
#include "Scene.hpp"
#include "tool.hpp"
#include <vector>

static Node* commonAncestor(){
    Node *out = (*Tool::selectGUI.begin())->getParent();
    if(out == nullptr)
        return out;
    for(GUI* g: Tool::selectGUI){
        while(!g->childOf(out))
            out= out->getParent();
    }
    return out;
}

void Tool::Ungroup(){

    if(selectedGui){
        if(selectGUI.empty())
            return;
        Node* ancestor = commonAncestor();
        for(GUI* g: selectGUI)
            g->setParent(ancestor);
        selectGUI.clear();
        return;
    }
    if((selectNODE == nullptr)|(selectNODE == Scene::getRoot()))
        return;
    Node* p = selectNODE->getParent();
    std::vector<void*> cache{};
    for(auto &g: selectNODE->getGuis())
        cache.push_back(g.get());
    for(void* g: cache)
        static_cast<GUI*>(g)->setParent(p);
    cache.clear();
    for(auto &n: selectNODE->getChildren())
        cache.push_back(n.get());
    for(void* n: cache)
        static_cast<Node*>(n)->setParent(p);
    cache.clear();
    selectNODE = nullptr;
}