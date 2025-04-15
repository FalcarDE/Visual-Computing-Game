#include "data_entity.h"


namespace Data
{
    void CEntity::SetFacet(EFacet _Type, void* _pFacet)
    {
        if (_Type >= 0 && _Type < NumberOfFacets)
        {
            m_Facets[_Type] = _pFacet;
        }
    }

    void* CEntity::GetFacet(EFacet _Type) const
    {
        if (_Type >= 0 && _Type < NumberOfFacets)
        {
            return m_Facets[_Type];
        }

        return nullptr;
    }

    void CEntity::SetMeta(CMetaEntity* _pMeta)
    {
        m_pMeta = _pMeta;
    }

    CMetaEntity* CEntity::GetMeta() const
    {
        return m_pMeta;
    }

    SEntityCategory::Enum CEntity::GetCategory() const
    {
        if (m_pMeta)
            return m_pMeta->GetCategory();

        return SEntityCategory::Undefined;
    }

    const Core::AABB2Float& CEntity::GetAABB() const
    {
        return m_AABB;
    }

    void CEntity::SetAABB(const Core::AABB2Float& aabb)
    {
        m_AABB = aabb;
    }

}
