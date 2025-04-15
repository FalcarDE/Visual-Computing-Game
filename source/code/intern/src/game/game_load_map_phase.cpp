#include "game_load_map_phase.h"
#include "../data/data_meta_entity.h"
#include "../graphics/graphics_facets.h"
#include "game_play_phase.h"

#include <iostream>
#include <cassert>

using namespace Game;
using namespace Data;
using namespace Graphics;

namespace Game
{
    CLoadMapPhase::CLoadMapPhase() = default;
    CLoadMapPhase::~CLoadMapPhase() = default;

    CLoadMapPhase& CLoadMapPhase::GetInstance()
    {
        static CLoadMapPhase instance;
        return instance;
    }

    void CLoadMapPhase::OnInternEnter()
    {
        std::cout << "[LoadMap] OnInternEnter() → Erzeuge Bodenobjekte...\n";

        // === Ground vorbereiten ===
        m_GroundMeta = std::make_unique<Data::CMetaEntity>("Ground", SEntityCategory::Ground);
        m_GroundFacet = std::make_unique<Graphics::CMetaFacet>("graphics/textures/ground.xml");

        // === Hindernisse vorbereiten ===
        m_ObstacleMeta = std::make_unique<Data::CMetaEntity>("Obstacle", SEntityCategory::Obstacle);
        m_ObstacleFacet = std::make_unique<Graphics::CMetaFacet>("graphics/textures/obstacle.xml");

        assert(m_GroundFacet && "[LoadMap] Boden-Facet ist null!");
        assert(!m_ObstacleFacet->GetTexturePath().empty() && "[LoadMap] TexturePath des Hindernisses darf nicht leer sein!");

        std::cout << "[LoadMap] Boden erfolgreich vorbereitet\n";
    }


    CPhase::EType CLoadMapPhase::OnInternRun()
    {
        std::cout << "[LoadMap] OnInternRun() → Übergabe Bodenobjekte an PlayPhase\n";

        Game::CPlayPhase::GetInstance().SetMeta(
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            m_ObstacleMeta.release(),
            m_ObstacleFacet.release()
        );

        return CPhase::Initialize;
    }

}

void CLoadMapPhase::OnInternLeave()
{
    std::cout << "[LoadMap] OnInternLeave() → Ressourcen ggf. freigeben\n";
}

