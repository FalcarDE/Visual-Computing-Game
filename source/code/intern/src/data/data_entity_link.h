
#pragma once

namespace Data
{
    class CEntity;
}

namespace Data
{
    class CEntityLink
    {
        public:

            static CEntity& GetEntity(CEntityLink& _rLink, const CEntityLink CEntity::* _Mtr);
            static const CEntity& GetEntity(const CEntityLink& _rLink, const CEntityLink CEntity::* _Mtr);

        public:

            CEntityLink();

        public:

            void Link(CEntityLink& _rNextLink);
            void Unlink();

            bool IsLinked() const;

        public:

            CEntity& GetEntity();
            const CEntity& GetEntity() const;

        public:

            void SetNext(CEntityLink* _pLink);
            CEntityLink* GetNext();

            void SetPrevious(CEntityLink* _pLink);
            CEntityLink* GetPrevious();

        private:

            CEntityLink* m_pNext;
            CEntityLink* m_pPrevious;
    };
}
