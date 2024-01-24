#pragma once

#include "Node.hpp"
#include "Runnable.hpp"
#include <vector>

/**
 * @brief The Scene class represents a scene.
 * @details This class is derived from the Runnable interface and manages the processes of nodes in the scene.
 */
class Scene : public Runnable{
private:
    static Scene *singleton;
    Node root;
public:
      /**
     * @brief Adds a node to the scene.
     * @param n The node to be added.
     */
    static void addNode(Node* n);

     /**
     * @brief Gets the root node of the scene.
     * @return The root node of the scene.
     */
    static Node* getRoot();

     /**
     * @brief Gets the singleton instance of the scene.
     * @return The singleton instance of the scene.
     */
    static inline Scene* getSingleton(){return singleton;}

     /**
     * @brief Scene processing function.
     * @details Performs the processes of nodes in the scene.
     */
    virtual void process() override;

      /**
     * @brief Default constructor for the Scene class.
     */
    explicit Scene();

    /**
     * @brief Default destructor for the Scene class.
     */
    ~Scene();
    friend Node; //so the nodes can remove themselves
};
