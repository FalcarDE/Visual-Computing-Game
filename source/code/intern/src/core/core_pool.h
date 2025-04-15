#pragma once

#include <new.h>
#include <stdlib.h>

namespace Core
{
    template <class T, size_t TNumberOfBytesPerPage>
    class CPool
    {
        public:

            static constexpr size_t s_NumberOfItemsPerPage = TNumberOfBytesPerPage / sizeof(T);

        public:

            CPool()
                : m_pFirstPage     (nullptr)
                , m_pFirstFreeChunk(nullptr)
            {
            }

           ~CPool()
            {
                SPage* pCurrentPage;
                SPage* pNextPage;

                for (pCurrentPage = m_pFirstPage; pCurrentPage != nullptr; pCurrentPage = pNextPage)
                {
                    pNextPage = pCurrentPage->m_pNextPage;

                    free(pCurrentPage);
                }
            }

        public:

            T& AllocateItem()
            {
                T*      pNewItem;
                SPage*  pNewPage;
                SChunk* pNewChunk;
                size_t  IndexOfChunk;

                if (m_pFirstFreeChunk == nullptr)
                {

                    // -----------------------------------------------------------------------------
                    // Allocate new page, because no free item
                    // -----------------------------------------------------------------------------
                    pNewPage = static_cast<SPage*>(malloc(sizeof(SPage)));

                    // -----------------------------------------------------------------------------
                    // Push all chunks of new page to front of free list
                    // -----------------------------------------------------------------------------
                    IndexOfChunk = s_NumberOfChunksPerPage;

                    while (IndexOfChunk != 0)
                    {
                        --IndexOfChunk;

                        SChunk& rChunk = pNewPage->m_Chunk[IndexOfChunk];

                        rChunk.m_pNextFreeChunk = m_pFirstFreeChunk;

                        m_pFirstFreeChunk = &rChunk;
                    }

                    pNewPage->m_pNextPage = m_pFirstPage;

                    m_pFirstPage = pNewPage;
                }

                // -----------------------------------------------------------------------------
                // Get chunk from free list
                // -----------------------------------------------------------------------------
                pNewChunk = m_pFirstFreeChunk;

                m_pFirstFreeChunk = m_pFirstFreeChunk->m_pNextFreeChunk;

                // -----------------------------------------------------------------------------
                // Placement new to construct new instance of T in chunk
                // -----------------------------------------------------------------------------
                pNewItem = new (&pNewChunk->m_Bytes[0]) T();

                return *pNewItem;
            }

            void FreeItem(T& _rItem)
            {
                SChunk* pChunk;

                // -----------------------------------------------------------------------------
                // Explicit call of destructor of T
                // -----------------------------------------------------------------------------
                _rItem.~T();

                // -----------------------------------------------------------------------------
                // Push front of chunk into free list
                // -----------------------------------------------------------------------------
                pChunk = reinterpret_cast<SChunk*>(&_rItem);

                pChunk->m_pNextFreeChunk = m_pFirstFreeChunk;

                m_pFirstFreeChunk = pChunk;
            }

        private:

            static const size_t s_NumberOfChunksPerPage = s_NumberOfItemsPerPage;

        private:

            struct SChunk
            {
                union
                {
                    SChunk*		  m_pNextFreeChunk;
                    unsigned char m_Bytes[sizeof(T)];
                };
            };

            struct SPage
            {
                SChunk m_Chunk[s_NumberOfChunksPerPage];
                SPage* m_pNextPage;
            };

        private:

            SPage*  m_pFirstPage;
            SChunk* m_pFirstFreeChunk;
    };
} // namespace Core
