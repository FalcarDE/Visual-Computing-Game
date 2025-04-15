#include "data_map.h"
#include "data_entity.h"

#include <cassert>
#include <iostream>

namespace Data
{
    // -----------------------------------------------------------------------------

    CEntityIterator CMap::BeginEntity(Core::AABB2Float& _rAABB, SEntityCategory::Enum _Category)
    {
        try
        {
            constexpr int SectorWidth = 100;
            constexpr int SectorHeight = 100;

            float MinX = _rAABB.GetMin()[0];
            float MinY = _rAABB.GetMin()[1];
            float MaxX = _rAABB.GetMax()[0];
            float MaxY = _rAABB.GetMax()[1];

            int StartX = static_cast<int>(MinX) / SectorWidth;
            int StartY = static_cast<int>(MinY) / SectorHeight;
            int EndX = static_cast<int>(MaxX) / SectorWidth;
            int EndY = static_cast<int>(MaxY) / SectorHeight;

            for (int y = StartY; y <= EndY; ++y)
            {
                for (int x = StartX; x <= EndX; ++x)
                {
                    CSector* pSector = GetSectorAt(x, y);
                    if (!pSector)
                    {
                        continue;
                    }

                    CEntityFolder& Folder = pSector->GetFolder(_Category);

                    for (CEntityIterator It = Folder.Begin(); It != Folder.End(); ++It)
                    {
                        CEntity& Entity = *It;
                        assert(Entity.GetMeta() != nullptr);

                        if (Entity.GetAABB().Intersects(_rAABB))
                        {
                            return It;
                        }
                    }
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "[EXCEPTION] CMap::BeginEntity: " << e.what() << std::endl;
        }

        return EndEntity();
    }

    // -----------------------------------------------------------------------------

    CEntityIterator CMap::NextEntity(CEntityIterator _Where, Core::AABB2Float& _rAABB, SEntityCategory::Enum _Category)
    {
        try
        {
            ++_Where;

            while (_Where != EndEntity())
            {
                CEntity& Entity = *_Where;
                assert(Entity.GetMeta() != nullptr);

                if (Entity.GetAABB().Intersects(_rAABB))
                {
                    return _Where;
                }

                ++_Where;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "[EXCEPTION] CMap::NextEntity: " << e.what() << std::endl;
        }

        return EndEntity();
    }

    // -----------------------------------------------------------------------------

    CEntityIterator CMap::BeginEntity(Core::AABB2Float& _rAABB)
    {
        (void)_rAABB;
        return EndEntity();
    }

    // -----------------------------------------------------------------------------

    CEntityIterator CMap::NextEntity(CEntityIterator _Where, Core::AABB2Float& _rAABB)
    {
        (void)_Where;
        (void)_rAABB;
        return EndEntity();
    }

    // -----------------------------------------------------------------------------

    CEntityIterator CMap::EndEntity()
    {
        return CEntityIterator();
    }

    // -----------------------------------------------------------------------------

    CSector* CMap::GetSectorAt(int _X, int _Y)
    {
        try
        {
            if (_X < 0 || _X >= NumColumns || _Y < 0 || _Y >= NumRows)
            {
                return nullptr;
            }

            return &m_Sectors[_Y * NumColumns + _X];
        }
        catch (...)
        {
            std::cerr << "[EXCEPTION] CMap::GetSectorAt: Ungültiger Zugriff!\n";
            return nullptr;
        }
    }

    // -----------------------------------------------------------------------------

    void CMap::AddEntity(CEntity& _rEntity)
    {
        try
        {
            assert(_rEntity.GetMeta() != nullptr && "CMap::AddEntity → Entity hat keine MetaEntity!");

            SEntityCategory::Enum Category = _rEntity.GetCategory();
            const auto& AABB = _rEntity.GetAABB();
            const auto& Center = AABB.GetCenter();

            float CenterX = Center[0];
            float CenterY = Center[1];

            constexpr int SectorWidth = 100;
            constexpr int SectorHeight = 100;

            int SectorX = static_cast<int>(CenterX) / SectorWidth;
            int SectorY = static_cast<int>(CenterY) / SectorHeight;

            CSector* pSector = GetSectorAt(SectorX, SectorY);
            if (!pSector)
            {
                std::cerr << "[ERROR] AddEntity: Ungültiger Sektor bei Position (" << CenterX << ", " << CenterY << ")\n";
                std::cerr << " → Entity AABB: Min(" << AABB.GetMin()[0] << ", " << AABB.GetMin()[1]
                    << ") Max(" << AABB.GetMax()[0] << ", " << AABB.GetMax()[1] << ")\n";
                std::cerr << " → Berechneter Sektor: (" << SectorX << ", " << SectorY << ")\n";
                std::cerr << " → Mapgröße: Spalten = " << NumColumns << ", Reihen = " << NumRows << "\n";
                return;
            }

            pSector->GetFolder(Category).AddEntity(_rEntity);
        }
        catch (const std::exception& e)
        {
            std::cerr << "[EXCEPTION] CMap::AddEntity: " << e.what() << std::endl;
        }
    }
}