
#pragma once

#include "data_entity_category.h"
#include "data_entity_iterator.h"
#include "data_sector.h"
#include "../core/core_aabb.h"

using Core::AABB2Float;

namespace Data
{
    class CMap
    {
    public:

        CEntityIterator BeginEntity(Core::AABB2Float& _rAABB, SEntityCategory::Enum _Category);
        CEntityIterator NextEntity(CEntityIterator _Where, Core::AABB2Float& _rAABB, SEntityCategory::Enum _Category);

        CEntityIterator BeginEntity(Core::AABB2Float& _rAABB);
        CEntityIterator NextEntity(CEntityIterator _Where, Core::AABB2Float& _rAABB);

        CEntityIterator EndEntity();

        void AddEntity(CEntity& entity);

        CSector* GetSectorAt(int x, int y);

    private:
        static constexpr int NumColumns = 8;
        static constexpr int NumRows = 6;
        CSector m_Sectors[NumRows * NumColumns];
    };
}