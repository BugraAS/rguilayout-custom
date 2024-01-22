#include "EventQueue.hpp"
#include <utility>
#include <vector>

EventQueue* EventQueue::singleton = nullptr;

EventQueue::EventQueue() {
    singleton = this;
}
EventQueue::~EventQueue() {
    singleton = nullptr;
}

void EventQueue::addHandler(Event event, EventHandler handler) {
   if(handler){
        if(singleton->eventHandlers.count(event) != 0)

            singleton->eventHandlers[event].push_back(handler);
        else
            singleton->eventHandlers.insert(std::pair<Event, std::vector<EventHandler>>(event,{handler}));
    }
}

void EventQueue::process() {
    for (auto& payload : activeEvents) {
        if (eventHandlers.find(payload.first) != eventHandlers.end()) {
            for (EventHandler& handler : eventHandlers[payload.first]) {
                if (!handler(payload.second)) {
                    break;
                }
            }
        }
    }
    activeEvents.clear();
}