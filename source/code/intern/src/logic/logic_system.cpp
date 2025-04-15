#include "logic_system.h"

#include "../core/core_aabb.h"
#include "../data/data_entity.h"
#include "../data/data_map.h"
#include "../graphics/graphics_facets.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cassert>
#include <iostream>

namespace Logic
{
    // -----------------------------------------------------------------------------

    CLogicSystem::CLogicSystem()
        : m_pPlayer(nullptr)
        , m_pMap(nullptr)
        , m_pWindow(nullptr)
        , m_MoveCooldown(0.0f)
        , m_ShouldChangePhase(false)
        , m_NextPhase(Game::CPhase::Undefined)
    {
    }

    // -----------------------------------------------------------------------------

    Data::CEntity* CLogicSystem::GetPlayer()
    {
        return m_pPlayer;
    }

    // -----------------------------------------------------------------------------d

    void CLogicSystem::SetPlayer(Data::CEntity* _pPlayer)
    {
        m_pPlayer = _pPlayer;
    }

    // -----------------------------------------------------------------------------

    void CLogicSystem::SetMap(Data::CMap* _pMap)
    {
        m_pMap = _pMap;
    }

    // -----------------------------------------------------------------------------

    void CLogicSystem::SetWindow(sf::RenderWindow* _pWindow)
    {
        m_pWindow = _pWindow;
    }

    // -----------------------------------------------------------------------------

    bool CLogicSystem::ShouldTriggerPhaseChange() const
    {
        return m_ShouldChangePhase;
    }

    // -----------------------------------------------------------------------------

    Game::CPhase::EType CLogicSystem::GetNextPhase() const
    {
        return Game::CPhase::MainMenu;
    }

    // -----------------------------------------------------------------------------

    void CLogicSystem::Update(float _Delta)
    {
        if (!m_pPlayer || !m_pMap || !m_pWindow)
        {
            std::cerr << "[Logic] Fehlende Referenzen (Player/Map/Window)!\n";
            return;
        }

        m_MoveCooldown -= _Delta;
        if (m_MoveCooldown > 0.0f)
        {
            return;
        }

        constexpr float StepSize = 40.0f;

        Core::AABB2Float CurrentAABB = m_pPlayer->GetAABB();
        Core::AABB2Float NewAABB = CurrentAABB;

        bool MoveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool MoveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        if (!MoveLeft && !MoveRight)
        {
            return;
        }

        // -----------------------------------------------------------------------------
        // Bewegung vorbereiten
        // -----------------------------------------------------------------------------
        if (MoveLeft)
        {
            NewAABB.SetMin({ CurrentAABB.GetMin()[0] - StepSize, CurrentAABB.GetMin()[1] });
            NewAABB.SetMax({ CurrentAABB.GetMax()[0] - StepSize, CurrentAABB.GetMax()[1] });

            std::cout << "[Logic] Spieler will nach links\n";
        }
        else if (MoveRight)
        {
            NewAABB.SetMin({ CurrentAABB.GetMin()[0] + StepSize, CurrentAABB.GetMin()[1] });
            NewAABB.SetMax({ CurrentAABB.GetMax()[0] + StepSize, CurrentAABB.GetMax()[1] });

            std::cout << "[Logic] Spieler will nach rechts\n";
        }

        // -----------------------------------------------------------------------------
        // Bildschirmgrenzen prüfen
        // -----------------------------------------------------------------------------
        float WinWidth = static_cast<float>(m_pWindow->getSize().x);
        if (NewAABB.GetMin()[0] < 0 || NewAABB.GetMax()[0] > WinWidth)
        {
            std::cout << "[Logic] Bewegung abgelehnt (Fensterrand erreicht)\n";
            return;
        }

        // -----------------------------------------------------------------------------
        // Kollision mit Hindernis prüfen
        // -----------------------------------------------------------------------------
        auto It = m_pMap->BeginEntity(NewAABB, Data::SEntityCategory::Obstacle);
        while (It != m_pMap->EndEntity())
        {
            const auto& Obstacle = *It;
            const auto& ObstacleAABB = Obstacle.GetAABB();

            if (ObstacleAABB.Intersects(NewAABB))
            {
                std::cout << "[Logic] Kollision mit Hindernis erkannt!\n";
                m_ShouldChangePhase = true;
                m_NextPhase = Game::CPhase::Unload;
                return;
            }

            It = m_pMap->NextEntity(It, NewAABB, Data::SEntityCategory::Obstacle);
        }

        // -----------------------------------------------------------------------------
        // Spielerposition aktualisieren
        // -----------------------------------------------------------------------------
        m_pPlayer->SetAABB(NewAABB);

        auto* pFacet = static_cast<Graphics::CFacet*>(m_pPlayer->GetFacet(Data::CEntity::GraphicsFacet));
        if (pFacet)
        {
            pFacet->SetPosition(NewAABB.GetMin()[0], NewAABB.GetMin()[1]);
        }

        std::cout << "[Logic] Spieler bewegt\n";

        m_MoveCooldown = 0.2f;
    }
}