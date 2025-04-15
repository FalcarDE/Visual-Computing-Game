#include "graphics_play_phase.h"
#include "graphics_facets.h"
#include "../data/data_entity.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <tinyxml2.h>


using namespace Graphics;
using namespace Data;

// -----------------------------------------------------------------------------

CGraphicsPlayPhase::CGraphicsPlayPhase() = default;

// -----------------------------------------------------------------------------

CGraphicsPlayPhase::~CGraphicsPlayPhase() = default;

// -----------------------------------------------------------------------------

void CGraphicsPlayPhase::SetMap(Data::CMap* _pMap)
{
    m_pMap = _pMap;
}

// -----------------------------------------------------------------------------

void CGraphicsPlayPhase::Init()
{
    // Placeholder – ggf. später initiale Textur-Ladeoperationen
}

// -----------------------------------------------------------------------------
void CGraphicsPlayPhase::Draw(sf::RenderWindow& _rWindow)
{
    try
    {
        if (!m_pMap)
        {
            std::cerr << "[WARN] Keine Map gesetzt\n";
            return;
        }

        _rWindow.clear(sf::Color::White);

        sf::Vector2u WindowSize = _rWindow.getSize();
        Core::AABB2Float View(0.0f, 0.0f, static_cast<float>(WindowSize.x), static_cast<float>(WindowSize.y));

        constexpr int NumColumns = 8;
        constexpr int NumRows = 6;

        // -----------------------------------------------------------------------------
        // === Boden zeichnen ===
        // -----------------------------------------------------------------------------
        for (int y = 0; y < NumRows; ++y)
        {
            for (int x = 0; x < NumColumns; ++x)
            {
                auto* pSector = m_pMap->GetSectorAt(x, y);
                if (!pSector) continue;

                auto& Folder = pSector->GetFolder(Data::SEntityCategory::Ground);
                for (auto It = Folder.Begin(); It != Folder.End(); ++It)
                {
                    const Data::CEntity& Entity = *It;
                    if (Entity.GetAABB().Intersects(View))
                    {
                        DrawEntityWithFacet(Entity, _rWindow);
                    }
                }
            }
        }

        // -----------------------------------------------------------------------------
        // === Hindernisse zeichnen ===
        // -----------------------------------------------------------------------------
        for (int y = 0; y < NumRows; ++y)
        {
            for (int x = 0; x < NumColumns; ++x)
            {
                auto* pSector = m_pMap->GetSectorAt(x, y);
                if (!pSector) continue;

                auto& Folder = pSector->GetFolder(Data::SEntityCategory::Obstacle);
                for (auto It = Folder.Begin(); It != Folder.End(); ++It)
                {
                    const Data::CEntity& Entity = *It;
                    if (Entity.GetAABB().Intersects(View))
                    {
                        DrawEntityWithFacet(Entity, _rWindow);
                    }
                }
            }
        }

        // -----------------------------------------------------------------------------
        // === Spieler zeichnen ===
        // -----------------------------------------------------------------------------
        for (int y = 0; y < NumRows; ++y)
        {
            for (int x = 0; x < NumColumns; ++x)
            {
                auto* pSector = m_pMap->GetSectorAt(x, y);
                if (!pSector) continue;

                auto& Folder = pSector->GetFolder(Data::SEntityCategory::Character);
                for (auto It = Folder.Begin(); It != Folder.End(); ++It)
                {
                    const Data::CEntity& Entity = *It;
                    if (Entity.GetAABB().Intersects(View))
                    {
                        DrawEntityWithFacet(Entity, _rWindow);
                    }
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "[EXCEPTION] Draw() gescheitert: " << e.what() << std::endl;
    }
}

// -----------------------------------------------------------------------------

void CGraphicsPlayPhase::DrawEntityWithFacet(const Data::CEntity& _rEntity, sf::RenderWindow& _rWindow)
{
    try
    {
        auto* pFacet = static_cast<Graphics::CFacet*>(_rEntity.GetFacet(Data::CEntity::GraphicsFacet));
        assert(pFacet && "GraphicsFacet darf nicht null sein!");
        if (!pFacet) return;

        auto* pMeta = pFacet->GetMetaFacet();
        assert(pMeta && "MetaFacet darf nicht null sein!");
        if (!pMeta) return;

        const std::string& XmlPath = pMeta->GetTexturePath();
        if (XmlPath.empty()) return;

        constexpr const char* RESOURCE_ROOT = "../../../../../ressources/";
        std::string FullXmlPath = std::string(RESOURCE_ROOT) + XmlPath;

        tinyxml2::XMLDocument Doc;
        if (Doc.LoadFile(FullXmlPath.c_str()) != tinyxml2::XML_SUCCESS)
        {
            std::cerr << "[ERROR] Konnte XML nicht laden: " << FullXmlPath << std::endl;
            return;
        }

        tinyxml2::XMLElement* pRoot = Doc.FirstChildElement("Graphic");
        if (!pRoot) return;

        const char* pTexFile = pRoot->FirstChildElement("Texture")->GetText();
        if (!pTexFile) return;

        std::string TexPath = pTexFile;
        std::string FullTexPath = std::string(RESOURCE_ROOT) + TexPath;

        sf::Texture& Texture = m_TextureCache[TexPath];
        if (Texture.getSize().x == 0)
        {
            if (!Texture.loadFromFile(FullTexPath))
            {
                std::cerr << "[ERROR] Konnte Textur nicht laden: " << FullTexPath << std::endl;
                return;
            }
        }

        sf::Sprite Sprite;
        Sprite.setTexture(Texture);
        Sprite.setPosition(pFacet->GetPosition().first, pFacet->GetPosition().second);
        Sprite.setScale(
            pFacet->GetSize().first / static_cast<float>(Texture.getSize().x),
            pFacet->GetSize().second / static_cast<float>(Texture.getSize().y)
        );

        _rWindow.draw(Sprite);
    }
    catch (const std::exception& e)
    {
        std::cerr << "[EXCEPTION] DrawEntityWithFacet() gescheitert: " << e.what() << std::endl;
    }
}

