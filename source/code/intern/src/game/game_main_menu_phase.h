#pragma once

#include "game_phase.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace Game
{
    class CMainMenuPhase : public CPhase
    {
    public:
        static CMainMenuPhase& GetInstance();

    private:
        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;

    private:
        CMainMenuPhase();
        ~CMainMenuPhase() override;

        CMainMenuPhase(const CMainMenuPhase&) = delete;
        CMainMenuPhase& operator=(const CMainMenuPhase&) = delete;

    private:
        std::unique_ptr<sf::RenderWindow> m_pWindow;

        sf::Font m_Font;
        sf::RectangleShape m_StartButton;
        sf::RectangleShape m_ExitButton;
        sf::Text m_StartText;
        sf::Text m_ExitText;
    };
}