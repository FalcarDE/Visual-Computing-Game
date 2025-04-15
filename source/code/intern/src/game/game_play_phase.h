#pragma once

#include "../data/data_map.h"
#include "../data/data_meta_entity.h"
#include "../graphics/graphics_facets.h"
#include "../graphics/graphics_play_phase.h"
#include "../logic/logic_system.h"
#include "game_phase.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

namespace Game
{
    class CPlayPhase : public CPhase
    {
    public:

        static CPlayPhase& GetInstance();

        void SetMeta(
            Data::CMetaEntity* _pGroundMeta,
            Graphics::CMetaFacet* _pGroundFacet,
            Data::CMetaEntity* _pObstacleMeta,
            Graphics::CMetaFacet* _pObstacleFacet,
            Data::CMetaEntity* _pPlayerMeta,
            Graphics::CMetaFacet* _pPlayerFacet
        );

        void ResetWorld();

    private:

        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;

        CPlayPhase();
        ~CPlayPhase() override;

        CPlayPhase(const CPlayPhase&) = delete;
        CPlayPhase& operator=(const CPlayPhase&) = delete;

        std::unique_ptr<sf::RenderWindow>            m_pWindow;

        sf::RectangleShape                           m_StartButton;
        sf::RectangleShape                           m_ExitButton;
        sf::Text                                     m_StartText;
        sf::Text                                     m_ExitText;
        sf::Font                                     m_Font;

        std::unique_ptr<Data::CMap>                  m_pMap;
        std::unique_ptr<Graphics::CGraphicsPlayPhase> m_pGfx;

        std::unique_ptr<Data::CMetaEntity>           m_GroundMeta;
        std::unique_ptr<Graphics::CMetaFacet>        m_GroundGraphicsMeta;

        std::unique_ptr<Data::CMetaEntity>           m_PlayerMeta;
        std::unique_ptr<Graphics::CMetaFacet>        m_PlayerGraphicsMeta;

        std::unique_ptr<Data::CMetaEntity>           m_ObstacleMeta;
        std::unique_ptr<Graphics::CMetaFacet>        m_ObstacleGraphicsMeta;

        std::list<Data::CEntity>                     m_EntityStorage;
        bool                                         m_EntitiesCreated = false;

        std::unique_ptr<Logic::CLogicSystem>         m_pLogic;
    };
}
