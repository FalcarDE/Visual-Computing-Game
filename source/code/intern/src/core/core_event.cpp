#include "core_event.h"
#include <iostream>

namespace Core
{
    CEventQueue& GetEventQueue()
    {
        static CEventQueue instance;
        return instance;
    }

    void CEventQueue::AddListener(IEventListener* listener)
    {
        m_Listeners.push_back(listener);
    }

    void CEventQueue::AddEvent(std::unique_ptr<IEvent> event)
    {
        m_Events.push(std::move(event));
    }

    void CEventQueue::ProcessEvents()
    {
        while (!m_Events.empty())
        {
            const std::unique_ptr<IEvent>& event = m_Events.front();

            for (IEventListener* listener : m_Listeners)
            {
                if (listener)
                {
                    listener->OnEvent(*event);
                }
            }

            m_Events.pop();
        }
    }

    void CEventQueue::Clear()
    {
        while (!m_Events.empty())
        {
            m_Events.pop();
        }
    }


}