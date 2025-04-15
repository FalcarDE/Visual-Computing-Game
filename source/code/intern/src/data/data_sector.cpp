#include "data_sector.h"
#include "data_entity.h"

namespace Data
{
    void CSector::AddEntity(CEntity& _rEntity)
    {
        SEntityCategory::Enum category = _rEntity.GetCategory();

        if (category >= 0 && category < SEntityCategory::NumberOfMembers)
        {
            m_Folders[category].AddEntity(_rEntity);
        }
    }

    void CSector::RemoveEntity(CEntity& _rEntity)
    {
        SEntityCategory::Enum category = _rEntity.GetCategory();

        if (category >= 0 && category < SEntityCategory::NumberOfMembers)
        {
            m_Folders[category].RemoveEntity(_rEntity);
        }
    }

    CEntityFolder& CSector::GetFolder(SEntityCategory::Enum category)
    {
        return m_Folders[category];
    }
}
