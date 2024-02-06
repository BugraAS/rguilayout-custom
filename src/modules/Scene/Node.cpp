#include "Node.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include "raylib-wrap.hpp"

void Node::addChild(Node* n){
    int index = 0;
    std::string name = n->name;
    while(hasChild(name)){
        index++;
        name = n->name + "_" + std::to_string(index);
    }
    n->name=name;
    children.push_back(std::unique_ptr<Node>(n));
}
void Node::addGui(GUI* g){
    int index = 0;
    std::string name = g->getLabel();
    while(hasChild(name)){
        index++;
        name = g->getLabel() + "_" + std::to_string(index);
    }
    g->setLabel(name);
    guis.push_back(std::unique_ptr<GUI>(g));
}

bool Node::hasChild(std::string label){
    bool result = false;
    result |= std::find_if(children.begin(), children.end(), [&label](const std::unique_ptr<Node> &child){return child->name == label;}) != children.end();
    result |= std::find_if(guis.begin(), guis.end(), [&label](const std::unique_ptr<GUI> &gui){return gui->getLabel() == label;}) != guis.end();
    return result;
}

Vector2 Node::getGPos(){
    return isOrphan() ? pos : parent->getGPos() + pos;
}

/**
 * @brief Destructor for the Node class.
 * @details Clears the parent-child relationship by setting the parent to nullptr.
 */
Node::~Node(){
    setParent(nullptr);
}
/**
 * @brief Removes a child node from the list of children.
 * @param n The child node to be removed.
 */
void Node::removeChild(Node* n){
    std::vector<std::unique_ptr<Node>>::iterator res = children.begin();
    if((res = std::find_if(children.begin(),children.end(),
        [&](std::unique_ptr<Node> &v)-> bool{
            return v.get() == n;
        })) != children.end()){
            std::unique_ptr<Node> &temp= children.at(res - children.begin());
            n = temp.release();
            children.erase(res);
        }
}
/**
 * @brief Removes a child gui from the list of gui.
 * @param g The child gui to be removed.
 */
void Node::removeGui(GUI* g){
    std::vector<std::unique_ptr<GUI>>::iterator res = guis.begin();
    if((res = std::find_if(guis.begin(),guis.end(),
        [&](std::unique_ptr<GUI> &v)-> bool{
            return v.get() == g;
        })) != guis.end()){
            std::unique_ptr<GUI> &temp= guis.at(res - guis.begin());
            g = temp.release();
            guis.erase(res);
        }
}
/**
 * @brief Sets the parent node for this node.
 * @param parent The parent node to be set.
 */
void Node::setParent(Node* parent){
    if(this->parent == parent)
        return;
    Node* oldparent = this->parent;
    if (oldparent != nullptr) {
        oldparent->removeChild(this);
    }
    this->parent = parent;
    if(parent != nullptr)
        parent->addChild(this);
}
