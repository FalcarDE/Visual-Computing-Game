
#pragma once

namespace Data
{
    class CEntity;
    class CEntityLink;
    class CEntityList;
}

namespace Data
{
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
        CEntityLink* m_pLink;    
        CEntityLink* m_pAnchor;  

    
        friend class CEntityList;

        CEntityIterator(CEntityLink* _pLink, CEntityLink* _pAnchor);
    };
}
