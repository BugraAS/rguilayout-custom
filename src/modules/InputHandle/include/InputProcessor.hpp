/**
 * @file InputHandle.hpp
 * @brief Header file for the InputHandle class.
 */
#pragma once

#include <map>
#include <functional>
#include "Runnable.hpp"
#include "State.hpp"


namespace KeyFlag{
    enum ENUM{
        L_SHIFT = 1 << 16,
        R_SHIFT = 1 << 17,
        L_CTRL = 1 << 18,
        R_CTRL = 1 << 19,
    };
}

typedef void (*InputHandler)();

/**
 * @class InputHandle
 * @brief Singleton class for handling input events.
 * @details The InputHandle class manages key mappings and processes input events.
 */
class InputProcessor : public Runnable {
private:
    static InputProcessor* singleton; ///< Static pointer to the singleton instance.
    std::map<int, InputHandler> keyMap[STATE::NUM_STATES]; ///< Map to store key mappings.

public:
    /**
     * @brief Constructor: Initialize keyMap and set singleton.
     */
    InputProcessor();

    /**
     * @brief Destructor: Cleanup and set the singleton instance to null.
     */
    ~InputProcessor();

    /**
     * @brief Process inputs - Placeholder comment for future implementation.
     * @details This function is a placeholder for handling inputs. Actual implementation is pending.
     */
    virtual void process() override;

    /**
     * @brief Map a key to an input event type.
     * @param keyCode The key code to be mapped.
     * @param eventType The input event type to be associated with the key.
     */
    static void mapKey(STATE::ENUM state, int keyCode, InputHandler handler);

    /**
     * @brief Unmap a key, removing it from the keyMap.
     * @param keyCode The key code to be unmapped.
     */
    static void unmapKey(STATE::ENUM state, int keyCode);

    /**
     * @brief Clear all key mappings from the keyMap.
     */
    static void clearKeyMappings();

    /**
     * @brief Static function to get the singleton instance of InputHandle.
     * @return Pointer to the singleton instance of InputHandle.
     */
    static inline InputProcessor* getSingleton(){return singleton;}
};