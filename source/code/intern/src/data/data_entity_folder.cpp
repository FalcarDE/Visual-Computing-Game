#include "data_entity_folder.h"
#include "data_entity.h"

namespace Data
{
    void CEntityFolder::AddEntity(CEntity& _rEntity)
    {
        m_Entities.PushBack(_rEntity);
    }

    void CEntityFolder::RemoveEntity(CEntity& _rEntity)
    {
        m_Entities.Erase(_rEntity);
    }

    CEntityIterator CEntityFolder::Begin()
    {
        return m_Entities.Begin();
    }

    CEntityIterator CEntityFolder::End()
    {
        return m_Entities.End();
    }
}
