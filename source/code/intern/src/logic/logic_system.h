#pragma once

#include "../game/game_phase.h"
#include "../data/data_entity.h"
#include <SFML/Graphics.hpp>

namespace sf {
    class RenderWindow;
}

namespace Data {
    class CEntity;
    class CMap;
}

namespace Logic
{
    class CLogicSystem
    {
    public:
        CLogicSystem();

        void Update(float delta);
        void SetPlayer(Data::CEntity* pPlayer);
        void SetMap(Data::CMap* pMap);
        void SetWindow(sf::RenderWindow* pWindow);

        bool ShouldTriggerPhaseChange() const;
        Game::CPhase::EType GetNextPhase() const;

        Data::CEntity* GetPlayer();

    private:
        Data::CEntity* m_pPlayer = nullptr;
        Data::CMap* m_pMap = nullptr;
        sf::RenderWindow* m_pWindow = nullptr;
        bool m_ShouldChangePhase = false;
        Game::CPhase::EType m_NextPhase = Game::CPhase::Undefined;
        float m_MoveCooldown = 0.0f;
    };
}
