#pragma once

#include <stdarg.h>

enum class EventType {
    STOCK_BUTTON_PRESSED = 0
};

class IEventsListener
{
public:
    friend class EventsController;
    virtual ~IEventsListener() {};
    virtual void onEvent(EventType eType, std::vector<void*> params) = 0;
};

