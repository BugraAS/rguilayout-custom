#include "Scene.hpp"
#include "LeftMenu.hpp"
#include "Node.hpp"
#include "RendererDefault.hpp"
#include "TopMenu.hpp"
#include "raygui-implement.h"
#include <functional>
#include <memory>
#include <queue>
#include <vector>

//TODO: Write tests for this class

/**
 * @brief The singleton instance of the Scene class.
 */
Scene *Scene::singleton=nullptr;

void Scene::process(){
    // TODO: implement interaction mode
    bool locked = raygui::GuiIsLocked();
    raygui::GuiLock();

    std::queue<Node*> queue{};
    queue.push(&root);
    for(Node* n=queue.front(); !queue.empty(); n=queue.front()){
        queue.pop();
        auto& childs = n->getChildren();
        for(auto& child: childs)
            queue.push(child.get());
        auto& guis = n->getGuis();
        for(auto& gui: guis){
            gui->draw();
        }
    }
    if(!locked)
        raygui::GuiUnlock();
}
/**
 * @brief Default constructor for the Scene class.
 */
Scene::Scene()
: root("root")
{
    singleton = this;
    root.pos = {LeftMenu::width*(1.33f),TopMenu::width*(1.33f) };
}

/**
 * @brief Default destructor for the Scene class.
 */
Scene::~Scene(){
    singleton = nullptr;
}

/**
 * @brief Adds a node to the scene.
 * @param n The node to be added.
 */
void Scene::addNode(Node *n){
    // if(n == nullptr) //intentionally removed safeguard
    //     return;
    n->setParent(Scene::getRoot());
}

void Scene::addGui(GUI *g){
    // if(n == nullptr) //intentionally removed safeguard
    //     return;
    g->setParent(Scene::getRoot());
}

/**
 * @brief Gets the root node of the scene.
 * @return The root node of the scene.
 */
Node* Scene::getRoot(){
    return &singleton->root;
}
