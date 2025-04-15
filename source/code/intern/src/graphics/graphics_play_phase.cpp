#include "graphics_play_phase.h"
#include "graphics_facets.h"
#include "../data/data_entity.h"
#include <tinyxml2.h>
#include <iostream>
#include <cassert>
#include <sstream>

using namespace Graphics;
using namespace Data;

CGraphicsPlayPhase::CGraphicsPlayPhase() = default;
CGraphicsPlayPhase::~CGraphicsPlayPhase() = default;

void CGraphicsPlayPhase::SetMap(CMap* pMap)
{
    m_pMap = pMap;
}

void CGraphicsPlayPhase::Init()
{
}

void CGraphicsPlayPhase::Draw(sf::RenderWindow& window)
{
    try
    {
        if (!m_pMap)
        {
            std::cerr << "[WARN] Keine Map gesetzt\n";
            return;
        }

        window.clear(sf::Color::White);

        sf::Vector2u winSize = window.getSize();
        Core::AABB2Float view(0, 0, (float)winSize.x, (float)winSize.y);

        constexpr int NumColumns = 8;
        constexpr int NumRows = 6;

        // === Boden zeichnen ===
        for (int y = 0; y < NumRows; ++y)
        {
            for (int x = 0; x < NumColumns; ++x)
            {
                auto* sector = m_pMap->GetSectorAt(x, y);
                if (!sector) continue;

                auto& folder = sector->GetFolder(SEntityCategory::Ground);
                for (auto it = folder.Begin(); it != folder.End(); ++it)
                {
                    const CEntity& e = *it;
                    if (e.GetAABB().Intersects(view))
                        DrawEntityWithFacet(e, window);
                }
            }
        }

        // === Hindernisse zeichnen ===
        for (int y = 0; y < NumRows; ++y)
        {
            for (int x = 0; x < NumColumns; ++x)
            {
                auto* sector = m_pMap->GetSectorAt(x, y);
                if (!sector) continue;

                auto& folder = sector->GetFolder(SEntityCategory::Obstacle);
                for (auto it = folder.Begin(); it != folder.End(); ++it)
                {
                    const CEntity& e = *it;
                    if (e.GetAABB().Intersects(view))
                        DrawEntityWithFacet(e, window);
                }
            }
        }

        // === Spieler zeichnen ===
        for (int y = 0; y < NumRows; ++y)
        {
            for (int x = 0; x < NumColumns; ++x)
            {
                auto* sector = m_pMap->GetSectorAt(x, y);
                if (!sector) continue;

                auto& folder = sector->GetFolder(SEntityCategory::Character);
                for (auto it = folder.Begin(); it != folder.End(); ++it)
                {
                    const CEntity& e = *it;
                    if (e.GetAABB().Intersects(view))
                        DrawEntityWithFacet(e, window);
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "[EXCEPTION] Draw() gescheitert: " << e.what() << std::endl;
    }
}

void CGraphicsPlayPhase::DrawEntityWithFacet(const Data::CEntity& entity, sf::RenderWindow& window)
{
    try
    {
        auto* pFacet = static_cast<Graphics::CFacet*>(entity.GetFacet(Data::CEntity::GraphicsFacet));
        assert(pFacet && "GraphicsFacet darf nicht null sein!");
        if (!pFacet) return;

        auto* pMeta = pFacet->GetMetaFacet();
        assert(pMeta && "MetaFacet darf nicht null sein!");
        if (!pMeta) return;

        const std::string& xmlPath = pMeta->GetTexturePath();
        if (xmlPath.empty()) return;

        constexpr const char* RESOURCE_ROOT = "../../../../../ressources/";
        std::string fullXmlPath = std::string(RESOURCE_ROOT) + xmlPath;

        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(fullXmlPath.c_str()) != tinyxml2::XML_SUCCESS)
        {
            std::cerr << "[ERROR] Konnte XML nicht laden: " << fullXmlPath << std::endl;
            return;
        }

        tinyxml2::XMLElement* root = doc.FirstChildElement("Graphic");
        if (!root) return;

        const char* texFile = root->FirstChildElement("Texture")->GetText();
        if (!texFile) return;

        std::string texPath = texFile;
        std::string fullPngPath = std::string(RESOURCE_ROOT) + texPath;

        sf::Texture& texture = m_TextureCache[texPath];
        if (texture.getSize().x == 0)
        {
            if (!texture.loadFromFile(fullPngPath))
            {
                std::cerr << "[ERROR] Konnte Textur nicht laden: " << fullPngPath << std::endl;
                return;
            }
        }

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(pFacet->GetPosition().first, pFacet->GetPosition().second);
        sprite.setScale(
            pFacet->GetSize().first / texture.getSize().x,
            pFacet->GetSize().second / texture.getSize().y
        );

        window.draw(sprite);
    }
    catch (const std::exception& e)
    {
        std::cerr << "[EXCEPTION] DrawEntityWithFacet() gescheitert: " << e.what() << std::endl;
    }
}
