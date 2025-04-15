#pragma once

#include <functional>
#include <queue>
#include <vector>
#include <memory>
#include <string>

namespace Core
{
    // ======================================
    // 1. Abstraktes Event-Interface
    // ======================================
    class IEvent
    {
    public:
        virtual ~IEvent() = default;
        virtual const std::string& GetType() const = 0;
    };

    // ======================================
    // 2. Abstraktes Listener-Interface
    // ======================================
    class IEventListener
    {
    public:
        virtual ~IEventListener() = default;
        virtual void OnEvent(const IEvent& event) = 0;
    };

    // ======================================
    // 3. EventQueue für globale Verwaltung
    // ======================================
    class CEventQueue
    {
    public:
        static CEventQueue& GetInstance()
        {
            static CEventQueue instance;
            return instance;
        }

        void AddListener(IEventListener* listener);

        void AddEvent(std::unique_ptr<IEvent> event);

        void ProcessEvents();

        void Clear();

    private:
        std::queue<std::unique_ptr<IEvent>> m_Events;
        std::vector<IEventListener*> m_Listeners;
    };
}
