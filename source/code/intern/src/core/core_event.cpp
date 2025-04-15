#include "core_event.h"

#include <iostream>

namespace Core
{
    // -----------------------------------------------------------------------------

    CEventQueue& GetEventQueue()
    {
        static CEventQueue s_Instance;
        return s_Instance;
    }

    // -----------------------------------------------------------------------------

    void CEventQueue::AddListener(IEventListener* _pListener)
    {
        m_Listeners.push_back(_pListener);
    }

    // -----------------------------------------------------------------------------

    void CEventQueue::AddEvent(std::unique_ptr<IEvent> _pEvent)
    {
        m_Events.push(std::move(_pEvent));
    }

    // -----------------------------------------------------------------------------

    void CEventQueue::ProcessEvents()
    {
        while (!m_Events.empty())
        {
            const std::unique_ptr<IEvent>& rEvent = m_Events.front();

            for (IEventListener* pListener : m_Listeners)
            {
                if (pListener)
                {
                    pListener->OnEvent(*rEvent);
                }
            }

            m_Events.pop();
        }
    }

    // -----------------------------------------------------------------------------

    void CEventQueue::Clear()
    {
        while (!m_Events.empty())
        {
            m_Events.pop();
        }
    }
}