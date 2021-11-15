#pragma once

enum EventType : int8_t {
    EVENT_MODIFY = 0
};

template<typename T>
class EventModify {
public:
    EventModify(T initial, std::function<void()> event) : initial(initial), event(event) {
        if (this->initial != newValue) {
            newValue = initial;
            event();
        }
    }

    EventModify &operator=(T const& newValue) {
        initial = newValue;
        event();
        return *this;
    }

    operator T() const { return initial; }

private:
    T initial;
    T newValue;
    std::function<void()> event;
};

/*
 * Game:
 *  EventModify
 *      -> Events.push_back(Event) !
 *  Event
 *      -> Update()
 *          -> Check for event
 */