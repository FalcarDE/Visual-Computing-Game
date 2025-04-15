#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "../data/data_map.h"
#include "../graphics/graphics_facets.h"
#include "../data/data_meta_entity.h"  

namespace Graphics
{
    class CGraphicsPlayPhase
    {
    public:
        CGraphicsPlayPhase();
        ~CGraphicsPlayPhase();

        void Init();
        void Draw(sf::RenderWindow& window);
        void SetMap(Data::CMap* pMap);

    private:
        void DrawEntityWithFacet(const Data::CEntity& entity, sf::RenderWindow& window);

    private:
        Data::CMap* m_pMap = nullptr;
        std::unordered_map<std::string, sf::Texture> m_TextureCache;
         
    };
}
