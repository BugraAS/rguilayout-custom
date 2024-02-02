#include "Scene.hpp"
#include "Global.hpp"
#include "LeftMenu.hpp"
#include "Node.hpp"
#include "RendererDefault.hpp"
#include "TopMenu.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "raymath.h"
#include "rlgl.h"
#include "tool.hpp"
#include <functional>
#include <memory>
#include <queue>
#include <vector>

//TODO: Write tests for this class

void Scene::setScale(float scale){
    singleton->zoom = scale;
}
float Scene::getScale(){
    return singleton->zoom;
}
Rectangle Scene::getScaledRec(Rectangle rec){
    float scale = getScale();
    return {rec.x,rec.y,rec.width*scale,rec.height*scale};
}

/**
 * @brief The singleton instance of the Scene class.
 */
Scene *Scene::singleton=nullptr;
float Scene::initFont=raygui::getFontSize();

static bool isFocused(GUI* gui){
    if(Tool::selectGUI.empty())
        return Tool::selectHover == gui;
    return Tool::selectGUI.find(gui) != Tool::selectGUI.end();
}

void Scene::process(){
    // TODO: implement interaction mode
    // Node* root = getRoot();

    bool locked = raygui::GuiIsLocked();
    raygui::GuiLock();

    float scale = getScale();

    Camera2D cam{
        offset,
        {},
        0.0f,
        scale
    };
    BeginMode2D(cam);

    bool selectF = (G::curTool._value != TOOL::INTERACT) & ((Tool::selectHover != nullptr)|(!Tool::selectGUI.empty()));
    std::queue<Node*> queue{};
    queue.push(root.get());
    for(Node* n=queue.front(); !queue.empty(); n=queue.front()){
        queue.pop();
        if(!n->isVisible())
            continue;
        auto& childs = n->getChildren();
        for(auto& child: childs)
            queue.push(child.get());
        auto& guis = n->getGuis();
        if(Tool::selectedGui){
            for(auto& gui: guis){
                bool focused = (isFocused(gui.get()))&selectF;
                if(focused) raygui::GuiSetState(raygui::STATE_FOCUSED);
                gui->draw();
                if(focused) raygui::GuiSetState(raygui::STATE_NORMAL);
            }
        }else{
            bool focused = n->childOf(Tool::selectNODE);
            for(auto& gui: guis){
                if(focused) raygui::GuiSetState(raygui::STATE_FOCUSED);
                gui->draw();
                if(focused) raygui::GuiSetState(raygui::STATE_NORMAL);
            }

        }
    }
    EndMode2D();

    if(!locked)
        raygui::GuiUnlock();
}
/**
 * @brief Default constructor for the Scene class.
 */
Scene::Scene()
: root(new Node("root"))
{
    singleton = this;
    offset = {LeftMenu::width*(1.33f),TopMenu::width*(1.33f) };
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
    return singleton->root.get();
}
