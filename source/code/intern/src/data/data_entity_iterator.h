#pragma once

namespace Data
{
    class CEntity;
    class CEntityLink;
    class CEntityList;

    class CEntityIterator
    {
    public:

        CEntityIterator();
        CEntityIterator(const CEntityIterator& _rOther);

        CEntityIterator& operator++();

        CEntity& operator*();
        CEntity* operator->();

        const CEntity& operator*() const;
        const CEntity* operator->() const;

        bool operator==(const CEntityIterator& _rOther) const;
        bool operator!=(const CEntityIterator& _rOther) const;

    private:

        CEntityLink* m_pLink = nullptr;
        CEntityLink* m_pAnchor = nullptr;

        CEntityIterator(CEntityLink* _pLink, CEntityLink* _pAnchor);

        friend class CEntityList;
    };
}