#include "game_load_map_phase.h"
#include "../data/data_meta_entity.h"
#include "../graphics/graphics_facets.h"
#include "game_play_phase.h"

#include <cassert>
#include <iostream>

namespace Game
{
    // -----------------------------------------------------------------------------

    CLoadMapPhase::CLoadMapPhase() = default;

    // -----------------------------------------------------------------------------

    CLoadMapPhase::~CLoadMapPhase() = default;

    // -----------------------------------------------------------------------------

    CLoadMapPhase& CLoadMapPhase::GetInstance()
    {
        static CLoadMapPhase s_Instance;
        return s_Instance;
    }

    // -----------------------------------------------------------------------------

    void CLoadMapPhase::OnInternEnter()
    {
        // -----------------------------------------------------------------------------
        // OnInternEnter() → Erzeuge Bodenobjekte und Hindernisse
        // -----------------------------------------------------------------------------
        std::cout << "[LoadMap] OnInternEnter() → Erzeuge Bodenobjekte...\n";

        m_GroundMeta = std::make_unique<Data::CMetaEntity>("Ground", Data::SEntityCategory::Ground);
        m_GroundFacet = std::make_unique<Graphics::CMetaFacet>("graphics/textures/ground.xml");

        m_ObstacleMeta = std::make_unique<Data::CMetaEntity>("Obstacle", Data::SEntityCategory::Obstacle);
        m_ObstacleFacet = std::make_unique<Graphics::CMetaFacet>("graphics/textures/obstacle.xml");

        assert(m_GroundFacet && "[LoadMap] Boden-Facet ist null!");
        assert(!m_ObstacleFacet->GetTexturePath().empty() && "[LoadMap] TexturePath des Hindernisses darf nicht leer sein!");

        std::cout << "[LoadMap] Boden erfolgreich vorbereitet\n";
    }

    // -----------------------------------------------------------------------------

    CPhase::EType CLoadMapPhase::OnInternRun()
    {
        // -----------------------------------------------------------------------------
        // OnInternRun() → Übergabe an PlayPhase
        // -----------------------------------------------------------------------------
        std::cout << "[LoadMap] OnInternRun() → Übergabe Bodenobjekte an PlayPhase\n";

        CPlayPhase::GetInstance().SetMeta(
            m_GroundMeta.release(),
            m_GroundFacet.release(),
            nullptr,
            nullptr,
            m_ObstacleMeta.release(),
            m_ObstacleFacet.release()
        );

        return CPhase::Initialize;
    }

    // -----------------------------------------------------------------------------

    void CLoadMapPhase::OnInternLeave()
    {
        // -----------------------------------------------------------------------------
        // OnInternLeave() → Ressourcen ggf. freigeben
        // -----------------------------------------------------------------------------
        std::cout << "[LoadMap] OnInternLeave() → Ressourcen ggf. freigeben\n";
    }
}