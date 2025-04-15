#pragma once

#include "../data/data_entity.h"
#include "../game/game_phase.h"

#include <SFML/Graphics.hpp>

namespace sf
{
    class RenderWindow;
}

namespace Data
{
    class CEntity;
    class CMap;
}

namespace Logic
{
    class CLogicSystem
    {
    public:

        CLogicSystem();

        void Update(float _Delta);
        void SetPlayer(Data::CEntity* _pPlayer);
        void SetMap(Data::CMap* _pMap);
        void SetWindow(sf::RenderWindow* _pWindow);

        bool ShouldTriggerPhaseChange() const;
        Game::CPhase::EType GetNextPhase() const;

        Data::CEntity* GetPlayer();

    private:

        Data::CEntity* m_pPlayer = nullptr;
        Data::CMap* m_pMap = nullptr;
        sf::RenderWindow* m_pWindow = nullptr;

        bool               m_ShouldChangePhase = false;
        Game::CPhase::EType m_NextPhase = Game::CPhase::Undefined;

        float              m_MoveCooldown = 0.0f;
    };
}
