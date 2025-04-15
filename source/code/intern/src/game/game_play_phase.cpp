#include "game_play_phase.h"
#include "../data/data_meta_entity.h"
#include "../core/core_aabb.h"
#include "../graphics/graphics_facets.h"
#include "../graphics/graphics_play_phase.h"
#include "../data/data_entity.h"


#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <windows.h>
#include "../logic/logic_facet.h"  

using namespace Data;
using namespace Core;
using namespace Graphics;

namespace Game
{
    CPlayPhase::CPlayPhase()
    {
        m_pMap = std::make_unique<CMap>();
        m_pGfx = std::make_unique<CGraphicsPlayPhase>();
        m_pGfx->SetMap(m_pMap.get());
    }

    CPlayPhase::~CPlayPhase() = default;

    CPlayPhase& CPlayPhase::GetInstance()
    {
        static CPlayPhase instance;
        return instance;
    }

    void CPlayPhase::OnInternEnter()
    {
        std::cout << "[GamePhase] Enter\n";

        // Fenster erzeugen
        m_pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Spiel läuft");

        if (!m_Font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
        {
            std::cerr << "[ERROR] Konnte Schrift nicht laden!\n";
        }

        // === Map & Grafik vorbereiten ===
        m_pMap = std::make_unique<CMap>();
        m_pGfx = std::make_unique<CGraphicsPlayPhase>();
        m_pGfx->SetMap(m_pMap.get());

        // === Meta-Daten vorbereiten ===
        m_GroundMeta = std::make_unique<CMetaEntity>("Ground", SEntityCategory::Ground);
        m_GroundGraphicsMeta = std::make_unique<CMetaFacet>("graphics/textures/ground.xml");

        m_PlayerMeta = std::make_unique<CMetaEntity>("Player", SEntityCategory::Character);
        m_PlayerGraphicsMeta = std::make_unique<CMetaFacet>("graphics/textures/player.xml");

        // === Hindernis vorbereiten ===
        m_ObstacleMeta = std::make_unique<CMetaEntity>("Obstacle", SEntityCategory::Obstacle);
        m_ObstacleGraphicsMeta = std::make_unique<CMetaFacet>("graphics/textures/obstacle.xml");

        // Logiksystem initialisieren
        m_pLogic = std::make_unique<Logic::CLogicSystem>();
        m_pLogic->SetWindow(m_pWindow.get());

        std::cout << "[GamePhase] Setup done\n";
    }

    CPhase::EType CPlayPhase::OnInternRun()
    {
        if (!m_EntitiesCreated)
        {
            const float tileWidth = 40.0f;
            const float tileHeight = 40.0f;
            const float groundY = static_cast<float>(m_pWindow->getSize().y) - tileHeight;
            const int tileCount = 20;

            // Boden
            for (int i = 0; i < tileCount; ++i)
            {
                float x1 = i * tileWidth;
                float y1 = groundY;
                float x2 = x1 + tileWidth;
                float y2 = y1 + tileHeight;

                m_EntityStorage.emplace_back();
                CEntity& ent = m_EntityStorage.back();

                ent.SetMeta(m_GroundMeta.get());
                ent.SetAABB(AABB2Float(x1, y1, x2, y2));
                m_pMap->AddEntity(ent);

                auto* pFacet = new CFacet();
                pFacet->SetPosition(x1, y1);
                pFacet->SetSize(tileWidth, tileHeight);
                pFacet->SetMetaFacet(m_GroundGraphicsMeta.get());
                ent.SetFacet(CEntity::GraphicsFacet, pFacet);
            }

            // Spieler
            const float playerWidth = 30.0f;
            const float playerHeight = 40.0f;

            float px1 = (tileWidth - playerWidth) / 2.0f;
            float py1 = groundY - playerHeight;
            float px2 = px1 + playerWidth;
            float py2 = py1 + playerHeight;

            m_EntityStorage.emplace_back();
            CEntity& player = m_EntityStorage.back();

            player.SetMeta(m_PlayerMeta.get());
            player.SetAABB(AABB2Float(px1, py1, px2, py2));
            m_pMap->AddEntity(player);

            auto* pPlayerFacet = new CFacet();
            pPlayerFacet->SetPosition(px1, py1);
            pPlayerFacet->SetSize(playerWidth, playerHeight);
            pPlayerFacet->SetMetaFacet(m_PlayerGraphicsMeta.get());
            player.SetFacet(CEntity::GraphicsFacet, pPlayerFacet);

            auto* pLogicFacet = new Logic::CLogicFacet();
            player.SetFacet(CEntity::LogicFacet, pLogicFacet);

            // Hindernis in der Mitte
            int midIndex = tileCount / 2;
            float ox1 = midIndex * tileWidth;
            float oy1 = groundY - tileHeight;
            float ox2 = ox1 + tileWidth;
            float oy2 = oy1 + tileHeight;

            m_EntityStorage.emplace_back();
            CEntity& obstacle = m_EntityStorage.back();

            obstacle.SetMeta(m_ObstacleMeta.get());
            obstacle.SetAABB(AABB2Float(ox1, oy1, ox2, oy2));
            m_pMap->AddEntity(obstacle);

            auto* pObsFacet = new CFacet();
            pObsFacet->SetPosition(ox1, oy1);
            pObsFacet->SetSize(tileWidth, tileHeight);
            pObsFacet->SetMetaFacet(m_ObstacleGraphicsMeta.get());
            obstacle.SetFacet(CEntity::GraphicsFacet, pObsFacet);

            // Logic-Verbindungen setzen
            m_pLogic->SetMap(m_pMap.get());
            m_pLogic->SetPlayer(&player);
            m_pLogic->SetWindow(m_pWindow.get());

            m_EntitiesCreated = true;
            std::cout << "[GamePhase] Welt, Spieler und mittiges Hindernis erzeugt\n";
        }

        // Eingabe + Logik
        m_pLogic->Update(1.0f / 60.0f);

        // Abbruchbedingung prüfen
        if (m_pLogic->ShouldTriggerPhaseChange())
        {
            Game::CPhase::EType next = m_pLogic->GetNextPhase();

            // Spezialfall: Wir wollen zuerst UnloadMap → dann MainMenu
            if (next == Game::CPhase::MainMenu)
            {
                return Game::CPhase::Unload;
            }

            return next;
        }

        sf::Event event;
        while (m_pWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_pWindow->close();
        }

        m_pWindow->clear(sf::Color::White);
        m_pGfx->Draw(*m_pWindow);
        m_pWindow->display();

        return EType::Play;
    }

    void CPlayPhase::OnInternLeave()
    {
        std::cout << "[GamePhase] Leave\n";
    }

    void CPlayPhase::SetMeta(
        Data::CMetaEntity* pGroundMeta,
        Graphics::CMetaFacet* pGroundFacet,
        Data::CMetaEntity* pObstacleMeta,
        Graphics::CMetaFacet* pObstacleFacet,
        Data::CMetaEntity* pPlayerMeta,
        Graphics::CMetaFacet* pPlayerFacet)
    {
        if (pGroundMeta && pGroundFacet)
        {
            m_GroundMeta.reset(pGroundMeta);
            m_GroundGraphicsMeta.reset(pGroundFacet);
        }

        if (pObstacleMeta && pObstacleFacet)
        {
            m_ObstacleMeta.reset(pObstacleMeta);
            m_ObstacleGraphicsMeta.reset(pObstacleFacet);
        }

        if (pPlayerMeta && pPlayerFacet)
        {
            m_PlayerMeta.reset(pPlayerMeta);
            m_PlayerGraphicsMeta.reset(pPlayerFacet);
        }
    }


    void CPlayPhase::ResetWorld()
    {
        std::cout << "[GamePhase] ResetWorld → Welt wird zurückgesetzt...\n";


        // Spieler zurück auf Startposition
        if (m_pLogic && m_pLogic->GetPlayer())
        {
            CEntity* player = m_pLogic->GetPlayer();

            const float playerWidth = 30.0f;
            const float playerHeight = 40.0f;
            const float tileWidth = 40.0f;
            const float groundY = static_cast<float>(m_pWindow->getSize().y) - tileWidth;

            float px1 = (tileWidth - playerWidth) / 2.0f;
            float py1 = groundY - playerHeight;
            float px2 = px1 + playerWidth;
            float py2 = py1 + playerHeight;

            player->SetAABB(AABB2Float(px1, py1, px2, py2));

            // Sprite ebenfalls verschieben
            auto* pFacet = static_cast<Graphics::CFacet*>(player->GetFacet(CEntity::GraphicsFacet));
            if (pFacet)
            {
                pFacet->SetPosition(px1, py1);
            }

            m_pLogic->SetPlayer(player);  
        }

    }
}

