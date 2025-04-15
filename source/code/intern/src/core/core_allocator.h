
#pragma once

#include <assert.h>
#include <exception>
#include <stdlib.h>

#include "core_uncopyable.h"

namespace Core
{
    template <int TNumberOfBytesPerChunk>
    class CAllocator : private CUncopyable
    {
        public:

            static const int s_NumberOfBytesPerChunk = TNumberOfBytesPerChunk;

        public:

            using CThis = CAllocator<TNumberOfBytesPerChunk>;

        public:

            CAllocator(int _NumberOfChunksPerPage)
                : m_NumberOfChunksPerPage(_NumberOfChunksPerPage)
                , m_NumberOfBytesPerPage (sizeof(SPage) + _NumberOfChunksPerPage * s_NumberOfBytesPerChunk)
                , m_pFirstPage           (nullptr)
                , m_pFirstFreeChunk      (nullptr)
            {
                assert(_NumberOfChunksPerPage != 0);
            }

           ~CAllocator()
            {
                Clear();
            }

        public:

            void* AllocateMemory()
            {
                SChunk* pChunk;
                SChunk* pFirstChunk;
                SPage*  pPage;

                if (m_pFirstFreeChunk == nullptr)
                {
                    // -----------------------------------------------------------------------------
                    // Allocate a new page and add it to the list of pages.
                    // -----------------------------------------------------------------------------
                    pPage = static_cast<SPage*>(::malloc(m_NumberOfBytesPerPage));

                    if (pPage == nullptr)
                    {
                        throw std::exception("Failed to allocate resource memory.");
                    }

                    pPage->m_pNextPage = m_pFirstPage; m_pFirstPage = pPage;

                    // -----------------------------------------------------------------------------
                    // Add the chunks of the new page into the free list. Insert those free chunks 
                    // in reverse order, so when we pop the chunks from the free list they are in
                    // increasing order.
                    // -----------------------------------------------------------------------------
                    pFirstChunk = GetFirstChunkOfPage(pPage);
                    pChunk      = pFirstChunk + m_NumberOfChunksPerPage;

                    while (pChunk != pFirstChunk)
                    {
                        PushFreeChunkToFront(-- pChunk);
                    }
                }

                pChunk = PopFreeChunkFromFront();

                return pChunk;
            }

            void FreeMemory(void* _pChunk)
            {
                SChunk* pChunk;

                assert(_pChunk != nullptr);

                pChunk = static_cast<SChunk*>(_pChunk);

                PushFreeChunkToFront(pChunk);
            }

            void Clear()
            {
                SPage* pPage;

                while (m_pFirstPage != nullptr)
                {
                    pPage = m_pFirstPage;

                    m_pFirstPage = m_pFirstPage->m_pNextPage;

                    ::free(pPage);
                }

                m_pFirstFreeChunk = nullptr;
            }

        private:

            static_assert(TNumberOfBytesPerChunk > 0, "Number of bytes per chunk has to be greater 0.");

        private:

            struct SChunk
            {
                union
                {
                    unsigned char m_Chunk[TNumberOfBytesPerChunk];
                    SChunk*       m_pNextFreeChunk;
                };
            };

        private:

            struct SPage
            {
                SPage* m_pNextPage;
            };

        private:

            const int m_NumberOfChunksPerPage;
            const int m_NumberOfBytesPerPage;
            SPage*    m_pFirstPage;
            SChunk*   m_pFirstFreeChunk;

        private:

            bool HasFreeChunk() const
            {
                return m_pFirstFreeChunk != nullptr;
            }

            void PushFreeChunkToFront(SChunk* _pChunk)
            {
                assert(_pChunk != nullptr);

                _pChunk->m_pNextFreeChunk = m_pFirstFreeChunk;

                m_pFirstFreeChunk = _pChunk;
            }

            SChunk* PopFreeChunkFromFront()
            {
                SChunk* pChunk;

                assert(HasFreeChunk());

                pChunk = m_pFirstFreeChunk;

                m_pFirstFreeChunk = m_pFirstFreeChunk->m_pNextFreeChunk;

                return pChunk;
            }

            SChunk* GetFirstChunkOfPage(SPage* _pPage)
            {
                assert(_pPage != nullptr);

                return reinterpret_cast<SChunk*>(_pPage + 1);
            }
    };
} // namespace Core