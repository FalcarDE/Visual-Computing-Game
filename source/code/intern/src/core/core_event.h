#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace Core
{
    // -----------------------------------------------------------------------------
    // 1. Abstraktes Event-Interface
    // -----------------------------------------------------------------------------
    class IEvent
    {
    public:

        virtual ~IEvent() = default;
        virtual const std::string& GetType() const = 0;
    };

    // -----------------------------------------------------------------------------
    // 2. Abstraktes Listener-Interface
    // -----------------------------------------------------------------------------
    class IEventListener
    {
    public:

        virtual ~IEventListener() = default;
        virtual void OnEvent(const IEvent& _rEvent) = 0;
    };

    // -----------------------------------------------------------------------------
    // 3. Globale Event-Queue (Singleton)
    // -----------------------------------------------------------------------------
    class CEventQueue
    {
    public:

        static CEventQueue& GetInstance()
        {
            static CEventQueue s_Instance;
            return s_Instance;
        }

        void AddListener(IEventListener* _pListener);
        void AddEvent(std::unique_ptr<IEvent> _pEvent);
        void ProcessEvents();
        void Clear();

    private:

        std::queue<std::unique_ptr<IEvent>> m_Events;
        std::vector<IEventListener*>        m_Listeners;
    };
}
