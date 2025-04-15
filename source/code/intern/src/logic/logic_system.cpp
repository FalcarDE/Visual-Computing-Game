#include "logic_system.h"
#include "../data/data_entity.h"
#include "../data/data_map.h"
#include "../core/core_aabb.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <cassert>
#include "../graphics/graphics_facets.h"

namespace Logic
{
    CLogicSystem::CLogicSystem()
        : m_pPlayer(nullptr), m_pMap(nullptr), m_pWindow(nullptr), m_MoveCooldown(0.0f), m_ShouldChangePhase(false)
    {
    }

    Data::CEntity* CLogicSystem::GetPlayer()
    {
        return m_pPlayer;
    }

    void CLogicSystem::SetPlayer(Data::CEntity* pPlayer)
    {
        m_pPlayer = pPlayer;
    }

    void CLogicSystem::SetMap(Data::CMap* pMap)
    {
        m_pMap = pMap;
    }

    void CLogicSystem::SetWindow(sf::RenderWindow* pWindow)
    {
        m_pWindow = pWindow;
    }

    bool CLogicSystem::ShouldTriggerPhaseChange() const
    {
        return m_ShouldChangePhase;
    }

    Game::CPhase::EType CLogicSystem::GetNextPhase() const
    {
        return Game::CPhase::MainMenu;
    }

    void CLogicSystem::Update(float delta)
    {
        if (!m_pPlayer || !m_pMap || !m_pWindow)
        {
            std::cerr << "[Logic] Fehlende Referenzen (Player/Map/Window)!\n";
            return;
        }

        m_MoveCooldown -= delta;
        if (m_MoveCooldown > 0.0f)
            return;

        constexpr float stepSize = 40.0f;
        Core::AABB2Float currentAABB = m_pPlayer->GetAABB();
        Core::AABB2Float newAABB = currentAABB;

        bool moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        if (!moveLeft && !moveRight)
            return;

        // Bewegung vorbereiten
        if (moveLeft)
        {
            newAABB.SetMin({ currentAABB.GetMin()[0] - stepSize, currentAABB.GetMin()[1] });
            newAABB.SetMax({ currentAABB.GetMax()[0] - stepSize, currentAABB.GetMax()[1] });
            std::cout << "[Logic] Spieler will nach links\n";
        }
        else if (moveRight)
        {
            newAABB.SetMin({ currentAABB.GetMin()[0] + stepSize, currentAABB.GetMin()[1] });
            newAABB.SetMax({ currentAABB.GetMax()[0] + stepSize, currentAABB.GetMax()[1] });
            std::cout << "[Logic] Spieler will nach rechts\n";
        }

        // Bildschirmgrenzen beachten
        float winWidth = static_cast<float>(m_pWindow->getSize().x);
        if (newAABB.GetMin()[0] < 0 || newAABB.GetMax()[0] > winWidth)
        {
            std::cout << "[Logic] Bewegung abgelehnt (Fensterrand erreicht)\n";
            return;
        }

        // Kollision mit Hindernis prüfen
        auto it = m_pMap->BeginEntity(newAABB, Data::SEntityCategory::Obstacle);
        while (it != m_pMap->EndEntity())
        {
            const auto& obstacle = *it;
            const auto& obstacleAABB = obstacle.GetAABB();

            if (obstacleAABB.Intersects(newAABB))
            {
                std::cout << "[Logic] Kollision mit Hindernis erkannt!\n";
                m_ShouldChangePhase = true;
                m_NextPhase = Game::CPhase::Unload;
                return; 
            }

            it = m_pMap->NextEntity(it, newAABB, Data::SEntityCategory::Obstacle);
        }

       
        m_pPlayer->SetAABB(newAABB);

        auto* pFacet = static_cast<Graphics::CFacet*>(m_pPlayer->GetFacet(Data::CEntity::GraphicsFacet));
        if (pFacet)
        {
            pFacet->SetPosition(newAABB.GetMin()[0], newAABB.GetMin()[1]);
        }

        std::cout << "[Logic] Spieler bewegt\n";

        m_MoveCooldown = 0.2f;
    }
}
