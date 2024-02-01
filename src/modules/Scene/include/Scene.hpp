#pragma once

#include "Node.hpp"
#include "Runnable.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include <vector>

/**
 * @brief The Scene class represents a scene.
 * @details This class is derived from the Runnable interface and manages the processes of nodes in the scene.
 */
class Scene : public Runnable{
private:
    static float initFont;
    static Scene *singleton;
    Node root;
    float zoom = 1;
    Vector2 offset{};
public:
    static inline void deltaOffset(Vector2 delta){singleton->offset = singleton->offset + delta;}
    static inline void setOffset(Vector2 off){singleton->offset = off;}
    static inline Vector2 getOffset(){return singleton->offset;}

    static inline void deltaZoom(float delta){singleton->zoom *= delta;}
    static inline float getZoom(){return singleton->zoom;}
    static inline void setZoom(float zoom){singleton->zoom = zoom;}
    /**
     * @brief Adds a node to the scene.
     * @param n The node to be added.
     */
    static void addNode(Node* n);

    static void addGui(GUI* g);

    static void setScale(float scale);
    static float getScale();
    static Rectangle getScaledRec(Rectangle rec);

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
