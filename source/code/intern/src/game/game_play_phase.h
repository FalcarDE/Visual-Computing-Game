#pragma once

#include "game_phase.h"
#include "../data/data_map.h"
#include "../graphics/graphics_play_phase.h"
#include "../graphics/graphics_facets.h"
#include "../data/data_meta_entity.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include "../logic/logic_system.h"

namespace Game
{
    class CPlayPhase : public CPhase
    {
    public:
        static CPlayPhase& GetInstance();
        void SetMeta
        (
            Data::CMetaEntity* pGroundMeta,
            Graphics::CMetaFacet* pGroundFacet,
            Data::CMetaEntity* pObstacleMeta,
            Graphics::CMetaFacet* pObstacleFacet,
            Data::CMetaEntity* pPlayerMeta,
            Graphics::CMetaFacet* pPlayerFacet
        );

        void ResetWorld();


    private:
        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;

    private:
        CPlayPhase();
        ~CPlayPhase() override;

        CPlayPhase(const CPlayPhase&) = delete;
        CPlayPhase& operator = (const CPlayPhase&) = delete;

    private:
        std::unique_ptr<sf::RenderWindow> m_pWindow;

        sf::RectangleShape m_StartButton;
        sf::RectangleShape m_ExitButton;
        sf::Text m_StartText;
        sf::Text m_ExitText;
        sf::Font m_Font;

        std::unique_ptr<Data::CMap>                     m_pMap;
        std::unique_ptr<Graphics::CGraphicsPlayPhase>   m_pGfx;

        std::unique_ptr<Data::CMetaEntity>      m_GroundMeta;
        std::unique_ptr<Graphics::CMetaFacet>   m_GroundGraphicsMeta;

        std::unique_ptr<Data::CMetaEntity>      m_PlayerMeta;           
        std::unique_ptr<Graphics::CMetaFacet>   m_PlayerGraphicsMeta; 

        std::unique_ptr<Data::CMetaEntity>      m_ObstacleMeta;             
        std::unique_ptr<Graphics::CMetaFacet>   m_ObstacleGraphicsMeta;

        std::list<Data::CEntity> m_EntityStorage;
        bool m_EntitiesCreated = false;

        std::unique_ptr<Logic::CLogicSystem> m_pLogic;
    };
}
