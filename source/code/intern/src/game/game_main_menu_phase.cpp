#include "game_main_menu_phase.h"
#include <iostream>

namespace Game
{
    CMainMenuPhase::CMainMenuPhase() = default;
    CMainMenuPhase::~CMainMenuPhase() = default;

    CMainMenuPhase& CMainMenuPhase::GetInstance()
    {
        static CMainMenuPhase instance;
        return instance;
    }

    void CMainMenuPhase::OnInternEnter()
    {
        std::cout << "[MainMenu] Betreten\n";

        m_pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Main Menu");

        m_StartButton.setSize(sf::Vector2f(200, 60));
        m_StartButton.setFillColor(sf::Color(100, 200, 100));
        m_StartButton.setPosition(300, 200);

        m_ExitButton.setSize(sf::Vector2f(200, 60));
        m_ExitButton.setFillColor(sf::Color(200, 100, 100));
        m_ExitButton.setPosition(300, 300);

        if (!m_Font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
        {
            std::cerr << "[MainMenu] Schriftart konnte nicht geladen werden\n";
        }

        m_StartText.setFont(m_Font);
        m_StartText.setString("Start");
        m_StartText.setCharacterSize(24);
        m_StartText.setFillColor(sf::Color::Black);
        m_StartText.setPosition(370, 215);

        m_ExitText.setFont(m_Font);
        m_ExitText.setString("Exit");
        m_ExitText.setCharacterSize(24);
        m_ExitText.setFillColor(sf::Color::Black);
        m_ExitText.setPosition(375, 315);
    }

    CPhase::EType CMainMenuPhase::OnInternRun()
    {
        sf::Event event;
        while (m_pWindow->isOpen())
        {
            while (m_pWindow->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    return CPhase::Finalize;

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    auto mousePos = sf::Mouse::getPosition(*m_pWindow);
                    if (m_StartButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
                    {
                        std::cout << "[MainMenu] Start gedrückt → Wechsle zu LoadMap-Phase\n";
                        return CPhase::Load;
                    }

                    if (m_ExitButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
                        return CPhase::Finalize;
                }
            }

            m_pWindow->clear(sf::Color::White);
            m_pWindow->draw(m_StartButton);
            m_pWindow->draw(m_ExitButton);
            m_pWindow->draw(m_StartText);
            m_pWindow->draw(m_ExitText);
            m_pWindow->display();
        }

        return CPhase::Finalize;
    }

    void CMainMenuPhase::OnInternLeave()
    {
        std::cout << "[MainMenu] Verlassen\n";
        m_pWindow->close();
    }
}