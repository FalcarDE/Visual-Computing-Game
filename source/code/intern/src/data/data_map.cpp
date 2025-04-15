#include "data_map.h"
#include "data_entity.h"
#include <iostream>
#include <cassert>



using Core::AABB2Float;
using namespace std;

namespace Data
{
    CEntityIterator CMap::BeginEntity(Core::AABB2Float& _rAABB, SEntityCategory::Enum _Category)
    {
        try
        {
            constexpr int SECTOR_WIDTH = 100;
            constexpr int SECTOR_HEIGHT = 100;

            float minX = _rAABB.GetMin()[0];
            float minY = _rAABB.GetMin()[1];
            float maxX = _rAABB.GetMax()[0];
            float maxY = _rAABB.GetMax()[1];

            int startX = static_cast<int>(minX) / SECTOR_WIDTH;
            int startY = static_cast<int>(minY) / SECTOR_HEIGHT;
            int endX = static_cast<int>(maxX) / SECTOR_WIDTH;
            int endY = static_cast<int>(maxY) / SECTOR_HEIGHT;

            for (int y = startY; y <= endY; ++y)
            {
                for (int x = startX; x <= endX; ++x)
                {
                    CSector* pSector = GetSectorAt(x, y);
                    if (!pSector) continue;

                    CEntityFolder& folder = pSector->GetFolder(_Category);

                    for (CEntityIterator _Where = folder.Begin(); _Where != folder.End(); ++_Where)
                    {
                        CEntity& entity = *_Where;

                        assert(entity.GetMeta() != nullptr);

                        if (entity.GetAABB().Intersects(_rAABB))
                            return _Where;
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

    CSector* CMap::GetSectorAt(int x, int y)
    {
        try
        {
            if (x < 0 || x >= NumColumns || y < 0 || y >= NumRows)
                return nullptr;

            return &m_Sectors[y * NumColumns + x];
        }
        catch (...)
        {
            std::cerr << "[EXCEPTION] CMap::GetSectorAt: Ungültiger Zugriff!\n";
            return nullptr;
        }
    }

    // -----------------------------------------------------------------------------

    CEntityIterator CMap::NextEntity(CEntityIterator _Where, AABB2Float& _rAABB, SEntityCategory::Enum _Category)
    {
        try
        {
            ++_Where;

            while (_Where != EndEntity())
            {
                CEntity& entity = *_Where;

                assert(entity.GetMeta() != nullptr);

                if (entity.GetAABB().Intersects(_rAABB))
                    return _Where;

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

    CEntityIterator CMap::BeginEntity(AABB2Float& _rAABB)
    {
        (void)_rAABB;
        return EndEntity();
    }

    // -----------------------------------------------------------------------------

    CEntityIterator CMap::NextEntity(CEntityIterator _Where, AABB2Float& _rAABB)
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

    void CMap::AddEntity(CEntity& entity)
    {
        try
        {
            assert(entity.GetMeta() != nullptr && "CMap::AddEntity → Entity hat keine MetaEntity!");

            SEntityCategory::Enum category = entity.GetCategory();

            const auto& aabb = entity.GetAABB();
            const auto& center = aabb.GetCenter();
            float centerX = center[0];
            float centerY = center[1];

            constexpr int SECTOR_WIDTH = 100;
            constexpr int SECTOR_HEIGHT = 100;

            int sectorX = static_cast<int>(centerX) / SECTOR_WIDTH;
            int sectorY = static_cast<int>(centerY) / SECTOR_HEIGHT;

            CSector* pSector = GetSectorAt(sectorX, sectorY);
            if (!pSector)
            {
                std::cerr << "[ERROR] AddEntity: Ungültiger Sektor bei Position (" << centerX << ", " << centerY << ")\n";

                std::cerr << " → Entity AABB: Min("
                    << aabb.GetMin()[0] << ", " << aabb.GetMin()[1]
                    << ") Max(" << aabb.GetMax()[0] << ", " << aabb.GetMax()[1]
                    << ")\n";

                std::cerr << " → Berechneter Sektor: (" << sectorX << ", " << sectorY << ")\n";
                std::cerr << " → Mapgröße: Spalten = " << NumColumns << ", Reihen = " << NumRows << "\n";

                return;
            }

            pSector->GetFolder(category).AddEntity(entity);
        }
        catch (const std::exception& e)
        {
            std::cerr << "[EXCEPTION] CMap::AddEntity: " << e.what() << std::endl;
        }
    }
}
