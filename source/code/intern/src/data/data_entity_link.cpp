#include "data_entity.h"
#include "data_entity_link.h"

#include <stdlib.h>

namespace Data
{
    CEntity& CEntityLink::GetEntity(CEntityLink& _rLink, const CEntityLink CEntity::* _Mtr)
    {
        return *reinterpret_cast<CEntity*>(reinterpret_cast<ptrdiff_t>(&_rLink) - (reinterpret_cast<ptrdiff_t>(&(static_cast<CEntity*>(nullptr) ->*(_Mtr))) - reinterpret_cast<ptrdiff_t>(static_cast<void*>(nullptr))));
    }

    // -----------------------------------------------------------------------------

    const CEntity& CEntityLink::GetEntity(const CEntityLink& _rLink, const CEntityLink CEntity::* _Mtr)
    {
        return *reinterpret_cast<CEntity*>(reinterpret_cast<ptrdiff_t>(&_rLink) - (reinterpret_cast<ptrdiff_t>(&(static_cast<CEntity*>(nullptr) ->*(_Mtr))) - reinterpret_cast<ptrdiff_t>(static_cast<void*>(nullptr))));
    }
}

namespace Data
{
    CEntityLink::CEntityLink()
    {
        m_pNext     = this;
        m_pPrevious = this;
    }

    // -----------------------------------------------------------------------------

    void CEntityLink::Link(CEntityLink& _rNextLink)
    {
        m_pNext     = &_rNextLink;
        m_pPrevious = _rNextLink.m_pPrevious;

        _rNextLink.m_pPrevious->m_pNext = this;
        _rNextLink.m_pPrevious          = this;
    }

    // -----------------------------------------------------------------------------

    void CEntityLink::Unlink()
    {
        m_pPrevious->m_pNext = m_pNext;
        m_pNext->m_pPrevious = m_pPrevious;

        m_pNext     = this;
        m_pPrevious = this;
    }

    // -----------------------------------------------------------------------------

    bool CEntityLink::IsLinked() const
    {
        return m_pNext != m_pNext->m_pNext;
    }

    // -----------------------------------------------------------------------------

    CEntity& CEntityLink::GetEntity()
    {
        return GetEntity(*this, &CEntity::m_Link);
    }

    // -----------------------------------------------------------------------------

    const CEntity& CEntityLink::GetEntity() const
    {
        return CEntityLink::GetEntity(*this, &CEntity::m_Link);
    }

    // -----------------------------------------------------------------------------

    void CEntityLink::SetNext(CEntityLink* _pLink)
    {
        m_pNext = _pLink;
    }

    // -----------------------------------------------------------------------------

    CEntityLink* CEntityLink::GetNext()
    {
        return m_pNext;
    }

    // -----------------------------------------------------------------------------

    void CEntityLink::SetPrevious(CEntityLink* _pLink)
    {
        m_pPrevious = _pLink;
    }

    // -----------------------------------------------------------------------------

    CEntityLink* CEntityLink::GetPrevious()
    {
        return m_pPrevious;
    }
}
