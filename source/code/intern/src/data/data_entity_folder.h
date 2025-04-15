
#pragma once

#include "data_entity_list.h"

namespace Data
{
    class CEntity;
    class CSector;
}

namespace Data
{
    class CEntityFolder
    {
        public:

            void AddEntity(CEntity& _rEntity);
            void RemoveEntity(CEntity& _rEntity);
            CEntityIterator Begin();
            CEntityIterator End();

        private:

            CSector*    m_pOwner;
            CEntityList m_Entities;
    };
}
