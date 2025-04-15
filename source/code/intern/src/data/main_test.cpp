#include "data_map.h"
#include "data_entity.h"
#include "data_meta_entity.h"
#include "../core/core_aabb.h"

#include <iostream>

using namespace Data;
using namespace Core;

int main()
{
    // Map initialisieren
    CMap map;

    // MetaEntity für Ground-Objekte
    CMetaEntity groundMeta("GroundBlock", SEntityCategory::Ground);

    // Entity erstellen
    CEntity ground;
    ground.SetMeta(&groundMeta);

    // AABB setzen – z. B. ein Block bei (50,50) bis (100,100)
    AABB2Float groundBox(50, 50, 100, 100);
    ground.SetAABB(groundBox);

    // Entity manuell in Sektor (0,0) einfügen
    CSector* pSector = map.GetSectorAt(0, 0);
    if (pSector)
    {
        std::cout << "[INFO] Füge Ground-Entity in Sektor (0,0) ein.\n";
        pSector->GetFolder(SEntityCategory::Ground).AddEntity(ground);
    }
    else
    {
        std::cout << "[ERROR] Sektor (0,0) nicht gefunden!\n";
        return 1;
    }

    // Sichtbereich / Suchbereich definieren (z. B. Kamera)
    AABB2Float searchBox(40, 40, 120, 120);

    std::cout << "[INFO] Suche nach Ground-Entities im AABB ("
        << searchBox.GetMin()[0] << ", " << searchBox.GetMin()[1] << ") → ("
        << searchBox.GetMax()[0] << ", " << searchBox.GetMax()[1] << ")\n";

    // BeginEntity aufrufen
    CEntityIterator it = map.BeginEntity(searchBox, SEntityCategory::Ground);
    if (it == map.EndEntity())
    {
        std::cout << "[WARNUNG] Keine Entity gefunden!\n";
    }

    // Treffer durchlaufen und ausgeben
    while (it != map.EndEntity())
    {
        CEntity& entity = *it;

        std::cout << "[TREFFER] Entity gefunden:\n";
        std::cout << "Min: (" << entity.GetAABB().GetMin()[0] << ", " << entity.GetAABB().GetMin()[1] << ") ";
        std::cout << "Max: (" << entity.GetAABB().GetMax()[0] << ", " << entity.GetAABB().GetMax()[1] << ")\n";

        it = map.NextEntity(it, searchBox, SEntityCategory::Ground);
    }

    return 0;
}