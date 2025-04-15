#pragma once

#include "../data/data_map.h"
#include "../data/data_meta_entity.h"
#include "../graphics/graphics_facets.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

namespace Graphics
{
    class CGraphicsPlayPhase
    {
    public:

        CGraphicsPlayPhase();
        ~CGraphicsPlayPhase();

        void Init();
        void Draw(sf::RenderWindow& _rWindow);
        void SetMap(Data::CMap* _pMap);

    private:

        void DrawEntityWithFacet(const Data::CEntity& _rEntity, sf::RenderWindow& _rWindow);

        Data::CMap* m_pMap;
        std::unordered_map<std::string, sf::Texture>  m_TextureCache;
    };
}