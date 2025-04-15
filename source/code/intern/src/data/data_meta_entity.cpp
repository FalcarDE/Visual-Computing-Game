#include "data_meta_entity.h"

namespace Data
{
    CMetaEntity::CMetaEntity(const std::string& _Name, SEntityCategory::Enum _Category)
        : m_Name(_Name), m_Category(_Category)
    {}

    const std::string& CMetaEntity::GetName() const
    {
        return m_Name;
    }

    SEntityCategory::Enum CMetaEntity::GetCategory() const
    {
        return m_Category;
    }

    void CMetaEntity::SetSize(float _Width, float _Height)
    {
        m_Width = _Width;
        m_Height = _Height;
    }

    void CMetaEntity::GetSize(float& _Width, float& _Height) const
    {
        _Width = m_Width;
        _Height = m_Height;
    }
}
