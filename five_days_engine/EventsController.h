#pragma once

#include <vector>
#include "IEventsListener.h"

class EventsController
{
private:
    static std::vector<IEventsListener*> _listeners;

public:
    static void addListener(IEventsListener* listener);
    static void removeListener(IEventsListener* listener);

    static void notify(EventType eType, std::vector<void*> params);

};

