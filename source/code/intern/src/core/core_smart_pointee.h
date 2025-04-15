
#pragma once

#include "core_uncopyable.h"

#include <assert.h>

namespace Core
{
    class CSmartPointee : private CUncopyable
    {
        public:

            CSmartPointee()
                : m_NumberOfReferences(0)
            {
            }

            virtual ~CSmartPointee()
            {
                assert(m_NumberOfReferences == 0);
            }

        public:

            int GetNumberOfReferences() const
            {
                return m_NumberOfReferences;
            }

            int AddRef()
            {
                ++ m_NumberOfReferences;

                return m_NumberOfReferences;
            }

            int Release()
            {
                assert(m_NumberOfReferences > 0);

                -- m_NumberOfReferences;

                if (m_NumberOfReferences == 0)
                {
                    FreeResource();
                }

                return m_NumberOfReferences;
            }

        private:

            int m_NumberOfReferences;

        private:

            virtual void FreeResource() = 0;
    };
} // namespace Core