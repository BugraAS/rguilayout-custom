#pragma once

#include "Runnable.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include "Event.hpp"


/**
 * @class EventQueue
 * @brief Singleton class for managing and processing events.
 * @details The EventQueue class handles the registration of event handlers and the processing of events.
 */
class EventQueue {
private:
    static EventQueue* singleton;  ///< Static pointer to the singleton instance.

    std::map<Event, std::vector<EventHandler>> eventHandlers;  ///< Map to store event handlers.
    std::vector<std::pair<Event, void*>> activeEvents;  ///< Vector to store active events.

public:
    /**
     * @brief Constructor: Set the singleton instance to the current instance.
     */
    EventQueue();

    /**
     * @brief Destructor: Reset the singleton instance on destruction.
     */
    ~EventQueue();

    /**
     * @brief Activate an event with payload.
     *
     * @param event Event to activate
     * @param data void pointer to payload
     */
    static inline void fireEvent(Event event, void* data){singleton->activeEvents.push_back({event,data});}

    /**
     * @brief Add an event handler for a specific event.
     * @param event The event for which the handler is registered.
     * @param handler The event handler function to be added.
     */
    static void addHandler(Event event, EventHandler handler);

    /**
     * @brief Process the events in the event queue.
     * @details This function processes the registered event handlers for active events.
     */
    void process();

    /**
     * @brief Static function to get the singleton instance of EventQueue.
     * @return Pointer to the singleton instance of EventQueue.
     */
    static inline EventQueue* getSingleton(){return singleton;}
};