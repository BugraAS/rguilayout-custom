/**
 * @file InputHandle.hpp
 * @brief Header file for the InputHandle class.
 */
#pragma once

#include <map>
#include <functional>
#include "Runnable.hpp"
#include "Event.hpp"

/**
 * @brief Enum for built-in events
 * 
 */
namespace InputEvent{
    enum ENUM{
        KEY_UP,
        KEY_DOWN,
        KEY_RIGHT,
        KEY_LEFT,
        CLICK_LEFT,
        CLICK_RIGHT,
    };
};

/**
 * @class InputHandle
 * @brief Singleton class for handling input events.
 * @details The InputHandle class manages key mappings and processes input events.
 */
class InputHandle : public Runnable {
private:
    static InputHandle* singleton; ///< Static pointer to the singleton instance.
    std::map<int, Event> keyMap; ///< Map to store key mappings.

public:
    /**
     * @brief Constructor: Initialize keyMap and set singleton.
     */
    InputHandle();

    /**
     * @brief Destructor: Cleanup and set the singleton instance to null.
     */
    ~InputHandle();

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
    static void mapKey(int keyCode, InputEvent::ENUM eventType);

    /**
     * @brief Unmap a key, removing it from the keyMap.
     * @param keyCode The key code to be unmapped.
     */
    static void unmapKey(int keyCode);

    /**
     * @brief Clear all key mappings from the keyMap.
     */
    static void clearKeyMappings();

    /**
     * @brief Static function to get the singleton instance of InputHandle.
     * @return Pointer to the singleton instance of InputHandle.
     */
    static inline InputHandle* getSingleton(){return singleton;}
};