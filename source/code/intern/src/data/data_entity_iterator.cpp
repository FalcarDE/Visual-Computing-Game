
#include "data_entity_iterator.h"
#include "data_entity_link.h"

#include <assert.h>

#include "data_entity_iterator.h"
#include "data_entity_link.h"

#include <assert.h>

namespace Data
{
    // Standard-Konstruktor
    CEntityIterator::CEntityIterator()
        : m_pLink(nullptr), m_pAnchor(nullptr)
    {
    }

    // Copy-Konstruktor
    CEntityIterator::CEntityIterator(const CEntityIterator& _rOther)
        : m_pLink(_rOther.m_pLink), m_pAnchor(_rOther.m_pAnchor)
    {
    }

    // Konstruktor mit Link + Anker
    CEntityIterator::CEntityIterator(CEntityLink* _pLink, CEntityLink* _pAnchor)
        : m_pLink(_pLink), m_pAnchor(_pAnchor)
    {
        if (_pLink == _pAnchor)
            m_pLink = nullptr; // direkt Terminierung
    }

    // Dereferenzierung
    CEntity& CEntityIterator::operator*()
    {
        assert(m_pLink != nullptr);
        return m_pLink->GetEntity();
    }

    CEntity* CEntityIterator::operator->()
    {
        assert(m_pLink != nullptr);
        return &m_pLink->GetEntity();
    }

    // Vergleich
    bool CEntityIterator::operator==(const CEntityIterator& _rOther) const
    {
        return m_pLink == _rOther.m_pLink;
    }

    bool CEntityIterator::operator!=(const CEntityIterator& _rOther) const
    {
        return !(*this == _rOther);
    }

    // Vorwärts-Inkrement
    CEntityIterator& CEntityIterator::operator++()
    {
        if (m_pLink && m_pLink != m_pAnchor)
        {
            m_pLink = m_pLink->GetNext();

            if (m_pLink == m_pAnchor)
                m_pLink = nullptr; // Liste durchlaufen → fertig
        }

        return *this;
    }

    const CEntity& CEntityIterator::operator*() const
    {
        assert(m_pLink != nullptr);
        return m_pLink->GetEntity();
    }

    const CEntity* CEntityIterator::operator->() const
    {
        assert(m_pLink != nullptr);
        return &m_pLink->GetEntity();
    }
}
