#pragma once

#include "data_entity_link.h"
#include "data_meta_entity.h"
#include "data_entity_category.h"
#include <array>
#include "../core/core_aabb.h"

namespace Data
{
    class CEntityList;
};

namespace Data
{
    class CEntity
    {
    public:

        enum EFacet
        {
            GraphicsFacet,
            LogicFacet,
            NumberOfFacets
        };

    public:

        void SetFacet(EFacet _Type, void* _pFacet);
        void* GetFacet(EFacet _Type) const;
        void SetMeta(CMetaEntity* _pMeta);
        SEntityCategory::Enum GetCategory() const;
        CMetaEntity* GetMeta() const;
        const Core::AABB2Float& GetAABB() const;
        void SetAABB(const Core::AABB2Float& aabb);

    private:

        using CFacetArray = std::array<void*, NumberOfFacets>;
        Core::AABB2Float m_AABB;

    private:

        CFacetArray m_Facets{};
        CEntityLink m_Link;
        CMetaEntity* m_pMeta = nullptr;

    private:

        friend class CEntityLink;
        friend class CEntityList;
    };
}