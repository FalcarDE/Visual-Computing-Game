#include "game_initialize_phase.h"
#include "game_play_phase.h"

#include <iostream>
#include <cassert>

using namespace Data;
using namespace Graphics;

namespace Game
{
    CInitializePhase::CInitializePhase() = default;
    CInitializePhase::~CInitializePhase() = default;

    CInitializePhase& CInitializePhase::GetInstance()
    {
        static CInitializePhase s_Instance;
        return s_Instance;
    }

    void CInitializePhase::OnInternEnter()
    {
        std::cout << "[InitPhase] OnInternEnter() → Lade MetaEntities & Texturen\n";

        // === Player vorbereiten ===
        m_PlayerMeta = std::make_unique<CMetaEntity>("Player", SEntityCategory::Character);
        m_PlayerFacet = std::make_unique<CMetaFacet>("graphics/textures/player.xml");

        assert(!m_PlayerFacet->GetTexturePath().empty() && "[InitPhase] Player TexturePath darf nicht leer sein!");

        // Nur Player übergeben – Ground & Obstacle kommen aus LoadMap
        CPlayPhase::GetInstance().SetMeta(
            nullptr, nullptr,                                   // Ground
            m_PlayerMeta.release(), m_PlayerFacet.release(),    // Player
            nullptr, nullptr                                    // Obstacle
        );

        std::cout << "[InitPhase] Ground und Player Meta/Faces übergeben\n";
    }


    CPhase::EType CInitializePhase::OnInternRun()
    {
        std::cout << "[InitPhase] OnInternRun() → Weiter zu PlayPhase\n";
        return CPhase::Play;
    }

    void CInitializePhase::OnInternLeave()
    {
        std::cout << "[InitPhase] OnInternLeave() → Aufräumen falls nötig\n";
    }
}
