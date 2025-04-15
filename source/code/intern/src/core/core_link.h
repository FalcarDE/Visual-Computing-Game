
#pragma once

#include <assert.h>

namespace Core
{
    class CLink
    {
        public:

            template <typename T>
            static T& GetOwner(CLink& _rLink, const CLink T::* _Mtr)
            {
                return *reinterpret_cast<T*>(reinterpret_cast<ptrdiff_t>(&_rLink) - (reinterpret_cast<ptrdiff_t>(&(static_cast<T*>(nullptr) ->*(_Mtr))) - reinterpret_cast<ptrdiff_t>(static_cast<void*>(nullptr))));
            }

            template <typename T>
            static const T& GetOwner(const CLink& _rLink, const CLink T::* _Mtr)
            {
                return *reinterpret_cast<T*>(reinterpret_cast<ptrdiff_t>(&_rLink) - (reinterpret_cast<ptrdiff_t>(&(static_cast<T*>(nullptr) ->*(_Mtr))) - reinterpret_cast<ptrdiff_t>(static_cast<void*>(nullptr))));
            }

        public:

            CLink()
            {
                m_pNext     = this;
                m_pPrevious = this;
            }

            CLink(const CLink& _rLink) = default;

        public:

            CLink& operator = (const CLink& _rLink) = default;

        public:

            void Link(CLink& _rNextLink)
            {
                assert(!IsLinked());

                m_pNext     = &_rNextLink;
                m_pPrevious = _rNextLink.m_pPrevious;

                _rNextLink.m_pPrevious->m_pNext = this;
                _rNextLink.m_pPrevious          = this;
            }

            void Unlink()
            {
                assert(IsLinked());

                m_pPrevious->m_pNext = m_pNext;
                m_pNext->m_pPrevious = m_pPrevious;

                m_pNext     = this;
                m_pPrevious = this;
            }

            bool IsLinked() const
            {
                return m_pNext != m_pNext->m_pNext;
            }

        public:

            CLink* GetNext()
            {
                return m_pNext;
            }

            const CLink* GetNext() const
            {
                return m_pNext;
            }

            CLink* GetPrevious()
            {
                return m_pPrevious;
            }

            const CLink* GetPrevious() const
            {
                return m_pPrevious;
            }

        private:

            CLink* m_pNext;
            CLink* m_pPrevious;
    };
} // namespace Core
