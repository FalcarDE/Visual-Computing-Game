#pragma once

#include "data_entity_category.h"

#include <string>

namespace Data
{
    class CMetaEntity
    {
    public:

        CMetaEntity(const std::string& _Name, SEntityCategory::Enum _Category);

        const std::string& GetName() const;
        SEntityCategory::Enum GetCategory() const;

        void SetSize(float _Width, float _Height);
        void GetSize(float& _Width, float& _Height) const;

    private:

        std::string             m_Name;
        SEntityCategory::Enum   m_Category;

        float m_Width = 1.0f;
        float m_Height = 1.0f;
    };
}