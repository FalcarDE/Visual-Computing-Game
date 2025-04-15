#pragma once

#include "data_entity_category.h"
#include "data_entity_link.h"
#include "data_meta_entity.h"

#include "../core/core_aabb.h"

#include <array>

namespace Data
{
    class CEntityList;

    class CEntity
    {
    public:

        enum EFacet
        {
            GraphicsFacet,
            LogicFacet,
            NumberOfFacets
        };

        void SetFacet(EFacet _Type, void* _pFacet);
        void* GetFacet(EFacet _Type) const;

        void SetMeta(CMetaEntity* _pMeta);
        CMetaEntity* GetMeta() const;

        SEntityCategory::Enum GetCategory() const;

        const Core::AABB2Float& GetAABB() const;
        void SetAABB(const Core::AABB2Float& _AABB);

    private:

        using CFacetArray = std::array<void*, NumberOfFacets>;

        Core::AABB2Float m_AABB;
        CFacetArray      m_Facets{};
        CEntityLink      m_Link;
        CMetaEntity* m_pMeta = nullptr;

        friend class CEntityLink;
        friend class CEntityList;
    };
}
