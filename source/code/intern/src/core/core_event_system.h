#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Core
{
    enum class EEventType
    {
        WindowCreated,
        KeyPressed,
        Collision
    };

    class IEvent
    {
    public:

        virtual ~IEvent() = default;

        virtual EEventType GetType() const = 0;
    };

    class CWindowCreatedEvent : public IEvent
    {
    public:

        CWindowCreatedEvent(const std::string& _Title, int _Width, int _Height);

        EEventType GetType() const override;

    public:

        std::string m_Title;
        int         m_Width;
        int         m_Height;
    };

    class CKeyPressedEvent : public IEvent
    {
    public:

        CKeyPressedEvent(int _KeyCode);

        EEventType GetType() const override;

    public:

        int m_KeyCode;
    };

    class CCollisionEvent : public IEvent
    {
    public:

        CCollisionEvent(int _ObjectA, int _ObjectB);

        EEventType GetType() const override;

    public:

        int m_ObjectA;
        int m_ObjectB;
    };

    class CEventDispatcher
    {
    public:

        using FEventHandler = std::function<void(const IEvent&)>;

    public:

        void Subscribe(EEventType _Type, FEventHandler _Handler);
        void Dispatch(const IEvent& _rEvent);

    private:

        std::unordered_map<EEventType, std::vector<FEventHandler>> m_Handlers;
    };
} // namespace Core
