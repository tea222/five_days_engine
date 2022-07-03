#include "EventsController.h"

std::vector<IEventsListener*> EventsController::_listeners;

void EventsController::addListener(IEventsListener* listener)
{
    _listeners.push_back(listener);
}

void EventsController::removeListener(IEventsListener* listener)
{
    auto beginIt = _listeners.begin();
    auto endIt = _listeners.end();
    auto findIt = std::find(beginIt, endIt, listener);
    if (findIt != endIt)
    {
        _listeners.erase(findIt);
    }
}

void EventsController::notify(EventType eType, std::vector<void*> params)
{
    for (IEventsListener* listener : _listeners)
    {
        listener->onEvent(eType, params);
    }
}
