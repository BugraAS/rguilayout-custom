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
    singleton->root.scale = scale;
}
float Scene::getScale(){
    return singleton->root.scale;
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

// Initialize Matrix mode with (Matrix)
static void BeginModeMatrix(Matrix mat)
{
    rlDrawRenderBatchActive();      // Update and draw internal render batch

    rlLoadIdentity();               // Reset current matrix (modelview)

    // Apply Matrix transformation to modelview
    rlMultMatrixf(MatrixToFloat(mat));
}

// Ends Matrix mode with
static void EndModeMatrix(void)
{
    rlDrawRenderBatchActive();      // Update and draw internal render batch

    rlLoadIdentity();               // Reset current matrix (modelview)
}

void Scene::process(){
    // TODO: implement interaction mode
    // Node* root = getRoot();

    bool locked = raygui::GuiIsLocked();
    raygui::GuiLock();

    float scale = getScale();
    setScale(1.0f);
    Vector2 offset = root.pos;
    root.pos = {};

    Camera2D cam{
        offset,
        {},
        0.0f,
        scale
    };
    BeginMode2D(cam);

    bool selectF = (G::curTool._value == TOOL::SELECT) & (Tool::selectHover != nullptr);
    std::queue<Node*> queue{};
    queue.push(&root);
    for(Node* n=queue.front(); !queue.empty(); n=queue.front()){
        queue.pop();
        auto& childs = n->getChildren();
        for(auto& child: childs)
            queue.push(child.get());
        auto& guis = n->getGuis();
        for(auto& gui: guis){
            bool focused = (gui.get() == Tool::selectHover)&selectF;
            if(focused) raygui::GuiSetState(raygui::STATE_FOCUSED);
            gui->draw();
            if(focused) raygui::GuiSetState(raygui::STATE_NORMAL);
        }
    }
    root.pos = offset;
    setScale(scale);
    EndMode2D();

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
