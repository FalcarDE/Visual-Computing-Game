
#pragma once

#include "core_pool.h"
#include "core_uncopyable.h"

#include <assert.h>
#include <vector>

namespace Core
{
    template <typename T>
    class CItemManager : private Core::CUncopyable
    {
        public:

            using CThis     = CItemManager<T>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;
            using BID       = unsigned int;

        public:

            CItemManager()
                : m_Items    ()
                , m_ItemsByID()
            {
                m_ItemsByID.reserve(16);
            }

           ~CItemManager() = default;

        public:

            XRef CreateItem(BID _ID)
            {
                // -----------------------------------------------------------------------------
                // Check if an item for this ID already exists.
                // -----------------------------------------------------------------------------
                if ((_ID < m_ItemsByID.size()) && (m_ItemsByID[_ID] != nullptr))
                {
                    return *m_ItemsByID[_ID];
                }

                XRef rItem = m_Items.AllocateItem();

                // -----------------------------------------------------------------------------
                // Register the new item in the vector by its ID. We do not store the items 
                // directly in the vector, because resizing of a vector implies that all 
                // pointers to an item become invalid.
                // -----------------------------------------------------------------------------
                if (_ID >= m_ItemsByID.size())
                {
                    m_ItemsByID.resize(_ID + 1);
                }

                m_ItemsByID[_ID] = &rItem;

                return rItem;
            }
            
            XRef GetItem(BID _ID)
            {
                assert(_ID < m_ItemsByID.size());

                return *m_ItemsByID[_ID];
            }

            XConstRef GetItem(BID _ID) const
            {
                assert(_ID < m_ItemsByID.size());

                return *m_ItemsByID[_ID];
            }

        public:

            void Clear()
            {
                XPtr pItem;

                const CItemVector::iterator ItemEndIterator = m_ItemsByID.end();

                for (typename CItemVector::iterator ItemIterator = m_ItemsByID.begin(); ItemIterator != ItemEndIterator; ++ ItemIterator)
                {
                    pItem = *ItemIterator;

                    if (pItem != nullptr)
                    {
                        m_Items.FreeItem(*pItem);
                    }
                }

                m_ItemsByID.clear();
            }

        private:

            using CItemPool = Core::CPool<T, 64 * sizeof(T)>;
            using CItemVector = std::vector<XPtr>;

        private:

            CItemPool   m_Items;
            CItemVector m_ItemsByID;
    };
} // namespace Core
