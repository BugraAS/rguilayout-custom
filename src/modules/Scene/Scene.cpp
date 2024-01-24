#include "Scene.hpp"
#include "Node.hpp"
#include "RendererDefault.hpp"
#include <functional>
#include <memory>
#include <vector>

//TODO: Write tests for this class

/**
 * @brief The singleton instance of the Scene class.
 */
Scene *Scene::singleton=nullptr;

/**
 * @brief Processes the scene by fetching visibles and running runnables.
 */
void Scene::process(){
}
/**
 * @brief Default constructor for the Scene class.
 */
Scene::Scene()
: root("root")
{
    singleton = this;
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

/**
 * @brief Gets the root node of the scene.
 * @return The root node of the scene.
 */
Node* Scene::getRoot(){
    return &singleton->root;
}
