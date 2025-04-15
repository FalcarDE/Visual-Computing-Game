#pragma once

#include "core_vector2.h"

namespace Core
{
    class CUserEvent
    {
        public:

            enum EAction
            {
                MouseMove,
                LeftButtonPressed,
                LeftButtonReleased,
                KeyPressed,
                KeyReleased,
            };

            enum EKey
            {
                Key1      = 49,
                Key2      = 50,
                Key3      = 51,
                Key4      = 52,
                Key5      = 53,
                Key6      = 54,
                Key7      = 55,
                KeySpace  = 32,
                KeyE      = 69,
                KeyW      = 87,
                KeyA      = 65,
                KeyS      = 83,
                KeyD      = 68,
                Numpad1   = 97,
                Numpad2   = 98,
                Numpad3   = 99,
                Numpad4   = 100,
                Numpad5   = 101,
                Numpad6   = 102,
                Numpad7   = 103,
                NumpadAdd = 107,
                NumpadDel = 109,
                KeyLeft   = 37,
                KeyRight  = 39,
                KeyUp     = 38,
                KeyDown   = 40,
                KeyEscape = 27,
                Mouse     = 0,
            };

        public:

            inline CUserEvent(unsigned int _Action, unsigned int _Key);
            inline CUserEvent(unsigned int _Action, unsigned int _Key, const SShort2& _rCursorPosition);
            inline CUserEvent(const CUserEvent& _rEvent);
            inline ~CUserEvent();

        public:

            inline CUserEvent& operator =(const CUserEvent& _rEvent);

        public:

            inline unsigned int GetAction() const;

            inline unsigned int GetKey() const;

            inline const SShort2& GetCursorPosition() const;

        private:

            struct SBits
            {
                unsigned int m_Action : 4;
                unsigned int m_Key    : 8;
            };

        private:

            SBits   m_Bits;
            SShort2 m_CursorPosition;
    };
} // namespace Core

namespace Core
{
    inline CUserEvent::CUserEvent(unsigned int _Action, unsigned int _Key)
        : m_CursorPosition(-1, -1)
    {
        m_Bits.m_Action = _Action;
        m_Bits.m_Key    = _Key;
    }

    // -----------------------------------------------------------------------------

    inline CUserEvent::CUserEvent(unsigned int _Action, unsigned int _Key, const SShort2& _rCursorPosition)
        : m_CursorPosition(_rCursorPosition)
    {
        m_Bits.m_Action = _Action;
        m_Bits.m_Key    = _Key;
    }

    // -----------------------------------------------------------------------------

    inline CUserEvent::CUserEvent(const CUserEvent& _rEvent)
        : m_CursorPosition(_rEvent.m_CursorPosition)
    {
        m_Bits.m_Action = _rEvent.m_Bits.m_Action;
        m_Bits.m_Key    = _rEvent.m_Bits.m_Key;
    }

    // -----------------------------------------------------------------------------

    inline CUserEvent::~CUserEvent() = default;

    // -----------------------------------------------------------------------------

    inline CUserEvent& CUserEvent::operator =(const CUserEvent& _rEvent)
    {
        m_Bits.m_Action  = _rEvent.m_Bits.m_Action;
        m_Bits.m_Key     = _rEvent.m_Bits.m_Key;
        m_CursorPosition = _rEvent.m_CursorPosition;

        return *this;
    }

    // -----------------------------------------------------------------------------

    inline unsigned int CUserEvent::GetAction() const
    {
        return static_cast<CUserEvent::EAction>(m_Bits.m_Action);
    }

    // -----------------------------------------------------------------------------

    inline unsigned int CUserEvent::GetKey() const
    {
        return static_cast<CUserEvent::EKey>(m_Bits.m_Key);
    }

    // -----------------------------------------------------------------------------

    inline const Core::SShort2& CUserEvent::GetCursorPosition() const
    {
        return m_CursorPosition;
    }
} // namespace Core
