
#include "core_id_manager.h"

#include <assert.h>

namespace Core
{
    CIDManager::CIDManager()
        : m_IDsByName()
        , m_NamesByID()
    {
        m_NamesByID.reserve(256);
    }

    // -----------------------------------------------------------------------------

    CIDManager::~CIDManager()
    {
        Clear();
    }

    // -----------------------------------------------------------------------------

    CIDManager::BID CIDManager::Register(const std::string& _rString)
    {
        CIDsByNameIterator Iterator = m_IDsByName.find(_rString);

        if (Iterator == m_IDsByName.end())
        {
            // -----------------------------------------------------------------------------
            // It is a new name so add it.
            // -----------------------------------------------------------------------------
            Iterator = m_IDsByName.insert(SIDsByNameItem(_rString, static_cast<BID>(m_IDsByName.size()))).first;

            m_NamesByID.push_back(Iterator);
        }

        return Iterator->second;
    }

    // -----------------------------------------------------------------------------

    bool CIDManager::ContainsName(const std::string& _rString) const
    {
        return m_IDsByName.find(_rString) != m_IDsByName.end();
    }

    // -----------------------------------------------------------------------------

    const std::string& CIDManager::GetName(BID _ID) const
    {
        assert(_ID < m_NamesByID.size());

        return (*m_NamesByID.at(_ID)).first;
    }

    // -----------------------------------------------------------------------------

    size_t CIDManager::GetNumberOfNames() const
    {
        return m_NamesByID.size();
    }

    // -----------------------------------------------------------------------------

    void CIDManager::Clear()
    {
        m_IDsByName.clear();
        m_NamesByID.clear();
    }
} // namespace Core
