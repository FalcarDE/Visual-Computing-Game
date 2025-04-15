#include "data_sector.h"
#include "data_entity.h"

namespace Data
{
    // -----------------------------------------------------------------------------

    void CSector::AddEntity(CEntity& _rEntity)
    {
        SEntityCategory::Enum Category = _rEntity.GetCategory();

        if (Category >= 0 && Category < SEntityCategory::NumberOfMembers)
        {
            m_Folders[Category].AddEntity(_rEntity);
        }
    }

    // -----------------------------------------------------------------------------

    void CSector::RemoveEntity(CEntity& _rEntity)
    {
        SEntityCategory::Enum Category = _rEntity.GetCategory();

        if (Category >= 0 && Category < SEntityCategory::NumberOfMembers)
        {
            m_Folders[Category].RemoveEntity(_rEntity);
        }
    }

    // -----------------------------------------------------------------------------

    CEntityFolder& CSector::GetFolder(SEntityCategory::Enum _Category)
    {
        return m_Folders[_Category];
    }
}