#pragma once

#include "Runnable.hpp"

// Renderer is a singleton but it has NO mechanisms to enforce it.
// A standard singleton is indestructible.
/**
 * @brief The Renderer class represents a renderer and is derived from the Runnable interface.
 */

class Renderer : public Runnable{
public:
    static Renderer *singleton;
public:
    /**
     * @brief Get the singleton instance of the Renderer class.
     * @return The singleton instance of the Renderer class.
     */
    static Renderer *getSingleton();

    /**
     * @brief Constructor for the Renderer class.
     * @details Initializes the singleton instance.
     */
    Renderer();

     /**
     * @brief Destructor for the Renderer class.
     * @details Sets the singleton instance to nullptr upon destruction.
     */
    virtual ~Renderer();
};
