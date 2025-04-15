#pragma once
#include "core_event.h"

namespace Core
{
    class CWindowClosedEvent : public IEvent
    {
    public:
        const std::string& GetType() const override
        {
            static std::string type = "WindowClosed";
            return type;
        }
    };
}
