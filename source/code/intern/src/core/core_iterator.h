
#pragma once

#include "core_link.h"

#include <assert.h>

namespace Core
{
    template <typename T, Core::CLink T::* TMtr>
    class CIterator
    {
        public:
            
            using CThis     = CIterator<T, TMtr>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;

        public:
            
            CIterator()
                : m_pLink(nullptr)
            {
            }

            explicit CIterator(CLink* _pLink)
                : m_pLink(_pLink)
            {
            }

        public:

            CThis& operator = (CLink* _pLink)
            {
                m_pLink = _pLink;

                return *this;
            }

            XRef operator * () const
            {
                assert(m_pLink != nullptr);

                return CLink::GetOwner<X>(*m_pLink, TMtr);
            }

            XPtr operator -> () const
            {
                return &CLink::GetOwner<X>(*m_pLink, TMtr);
            }

            CThis& operator ++ ()
            {
                assert(m_pLink != nullptr);

                m_pLink = m_pLink->GetNext();

                return *this;
            }

            CThis operator ++ (int)
            {
                CThis Iterator(m_pLink);

                ++ (*this);

                return Iterator;
            }

            bool operator == (const CThis& _rIterator) const
            {
                return m_pLink == _rIterator.m_pLink;
            }

            bool operator != (const CThis& _rIterator) const
            {
                return m_pLink != _rIterator.m_pLink;
            }

        private:

            CLink* m_pLink;
    };
} // namespace Core
