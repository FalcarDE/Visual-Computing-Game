#include "core_event_system.h"

// -----------------------------------------------------------------------------
// Core Event System
// -----------------------------------------------------------------------------
//
// Dieses Modul ermöglicht eine lose gekoppelte Ereignisverarbeitung im Core-Teil.
// Es definiert ein generisches Interface (IEvent), konkrete Events (z. B.
// CKeyPressedEvent) und einen Dispatcher (CEventDispatcher), über den beliebige
// Systeme auf bestimmte Eventtypen reagieren können.
//
// Verwendung:
// - Systeme registrieren Callback-Funktionen via Subscribe(EventType, Handler)
// - Bei einem Ereignis wird Dispatch(Event) aufgerufen, was alle registrierten
//   Handler für diesen Typ ausführt.
//
// -----------------------------------------------------------------------------

namespace Core
{
    // -------------------------------------------------------------------------

    CWindowCreatedEvent::CWindowCreatedEvent(const std::string& _Title, int _Width, int _Height)
        : m_Title(_Title)
        , m_Width(_Width)
        , m_Height(_Height)
    {
    }

    // -------------------------------------------------------------------------

    EEventType CWindowCreatedEvent::GetType() const
    {
        return EEventType::WindowCreated;
    }

    // -------------------------------------------------------------------------

    CKeyPressedEvent::CKeyPressedEvent(int _KeyCode)
        : m_KeyCode(_KeyCode)
    {
    }

    // -------------------------------------------------------------------------

    EEventType CKeyPressedEvent::GetType() const
    {
        return EEventType::KeyPressed;
    }

    // -------------------------------------------------------------------------

    CCollisionEvent::CCollisionEvent(int _ObjectA, int _ObjectB)
        : m_ObjectA(_ObjectA)
        , m_ObjectB(_ObjectB)
    {
    }

    // -------------------------------------------------------------------------

    EEventType CCollisionEvent::GetType() const
    {
        return EEventType::Collision;
    }

    // -------------------------------------------------------------------------

    void CEventDispatcher::Subscribe(EEventType _Type, FEventHandler _Handler)
    {
        m_Handlers[_Type].push_back(_Handler);
    }

    // -------------------------------------------------------------------------

    void CEventDispatcher::Dispatch(const IEvent& _rEvent)
    {
        auto HandlerIterator = m_Handlers.find(_rEvent.GetType());

        if (HandlerIterator != m_Handlers.end())
        {
            for (const FEventHandler& rHandler : HandlerIterator->second)
            {
                rHandler(_rEvent);
            }
        }
    }
} // namespace Core
