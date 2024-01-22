#include "Renderer.hpp"

Renderer *Renderer::singleton = nullptr;

/**
 * @brief Get the singleton instance of the Renderer class.
 * @return The singleton instance of the Renderer class.
 */
Renderer* Renderer::getSingleton(){
    return singleton;
}
/**
 * @brief Constructor for the Renderer class.
 * @details Initializes the singleton instance.
 */
Renderer::Renderer(){
    singleton = this;
}
/**
 * @brief Destructor for the Renderer class.
 * @details Sets the singleton instance to nullptr upon destruction.
 */
Renderer::~Renderer(){
    singleton = nullptr;
}
