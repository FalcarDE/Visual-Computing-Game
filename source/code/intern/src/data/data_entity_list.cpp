
#include "data_entity.h"
#include "data_entity_list.h"

#include <assert.h>

namespace Data
{
    CEntityList::CEntityList()
        : m_Anchor()
    {
    }

    // -----------------------------------------------------------------------------

    CEntityList::~CEntityList()
    {
        Clear();
    }

    // -----------------------------------------------------------------------------

    void CEntityList::Clear()
    {
        while (!IsEmpty());
        {
            PopBack();
        }
    }

    // -----------------------------------------------------------------------------

    bool CEntityList::IsEmpty() const
    {
        return !m_Anchor.IsLinked();
    }

    // -----------------------------------------------------------------------------

    void CEntityList::PushBack(CEntity& _rEntity)
    {
        _rEntity.m_Link.Link(m_Anchor);
    }

    // -----------------------------------------------------------------------------

    CEntity& CEntityList::PopBack()
    {
        CEntityLink* pLink = m_Anchor.GetPrevious();

        assert(pLink != nullptr);

        pLink->Unlink();

        return pLink->GetEntity();
    }

    // -----------------------------------------------------------------------------

    void CEntityList::Erase(CEntity& _rEntity)
    {
        _rEntity.m_Link.Unlink();
    }

    // -----------------------------------------------------------------------------

    CEntityIterator CEntityList::Begin()
    {
        return CEntityIterator(m_Anchor.GetNext(), &m_Anchor);
    }

    CEntityIterator CEntityList::End()
    {
        return CEntityIterator(nullptr, &m_Anchor);
    }

}