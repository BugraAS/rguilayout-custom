#pragma once

#include "GUI.hpp"
#include "Runnable.hpp"
#include "raylib.h"
#include <memory>
#include <string>
#include <vector>

/**
 * @brief The Node class represents a basic node in a hierarchical structure.
 * @details Node is a virtual class inheriting from NodeType and implementing Runnable.
 * It serves as a building block for creating hierarchical structures of nodes in a scene.
 */

class GUI; //fix circular dependency problemtransformRec(rec)

class Node{
    public:
        std::string name{"Dingleberg"};
        Vector2 pos{0.0f, 0.0f};
        //TODO: ADD visibility conditions based on some resource
        //TODO: ADD scale factor
        float scale = 1.0f;
    protected:
        std::vector<std::unique_ptr<Node>> children{};
        std::vector<std::unique_ptr<GUI>> guis{};
        //TODO: ADD modifications vector
        Node* parent = nullptr;
    public:
        /**
         * @brief Gets the parent node of the current node.
         * @return A pointer to the parent node.
         */
        inline Node* getParent(){return parent;}

        Vector2 getGPos();

         /**
         * @brief Sets the parent node of the current node.
         * @param parent A pointer to the parent node.
         */
        void setParent(Node* parent);

         /**
         * @brief Finds a child node by its name.
         * @param name The name of the child node to find.
         * @return A pointer to the found child node, or nullptr if not found.
         */
        Node* findChild(std::string name);

        inline Rectangle recurseRec(Rectangle rec){return isOrphan() ? transformRec(rec) : parent->recurseRec(transformRec(rec)) ;}
        inline Rectangle transformRec(Rectangle rec){return {rec.x*scale + pos.x,rec.y*scale + pos.y,rec.width*scale,rec.height*scale};}
        inline void setScale(float scale){this->scale = scale;}
        inline void setPos(Vector2 pos){this->pos = pos;}

        /**
         * @brief Gets the vector of children nodes.
         * @return A reference to the vector of children nodes.
         */
        inline std::vector<std::unique_ptr<Node>>& getChildren(){ return children;}
        inline std::vector<std::unique_ptr<GUI>>& getGuis(){ return guis;}


        /**
         * @brief Checks if the node is an orphan (has no parent).
         * @return True if the node has no parent, false otherwise.
         */
        inline bool isOrphan(){return parent == nullptr;}

        /**
         * @brief Default constructor for Node.
         */
        explicit inline Node() =default;

        /**
         * @brief Constructor for Node with a specified name.
         * @param name The name of the node.
         */
        explicit inline Node(std::string name): Node(){this->name = name;}

        // Delete copy and move constructors and assignment operators
        explicit Node(const Node &) = delete;
        explicit Node(Node &&) = delete;
        Node &operator=(Node &&) = default;
        Node &operator=(const Node &) = default;

         /**
         * @brief Destructor for Node.
         * @details Doesn't need virtual as it doesn't have any derivatives.
         */
        ~Node();
    protected:
         /**
         * @brief Removes a child node from the current node.
         * @param n A pointer to the child node to be removed.
         */
        void removeChild(Node* n);
        void removeGui(GUI* g);
        friend GUI;
};
