#include "game_main_menu_phase.h"

#include <iostream>

namespace Game
{
    // -----------------------------------------------------------------------------

    CMainMenuPhase::CMainMenuPhase() = default;

    // -----------------------------------------------------------------------------

    CMainMenuPhase::~CMainMenuPhase() = default;

    // -----------------------------------------------------------------------------

    CMainMenuPhase& CMainMenuPhase::GetInstance()
    {
        static CMainMenuPhase s_Instance;
        return s_Instance;
    }

    // -----------------------------------------------------------------------------

    void CMainMenuPhase::OnInternEnter()
    {
        // -----------------------------------------------------------------------------
        // Fenster & UI initialisieren
        // -----------------------------------------------------------------------------
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

    // -----------------------------------------------------------------------------

    CPhase::EType CMainMenuPhase::OnInternRun()
    {
        // -----------------------------------------------------------------------------
        // Hauptereignisschleife des Hauptmenüs
        // -----------------------------------------------------------------------------
        sf::Event Event;

        while (m_pWindow->isOpen())
        {
            while (m_pWindow->pollEvent(Event))
            {
                if (Event.type == sf::Event::Closed)
                {
                    return CPhase::Finalize;
                }

                if (Event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i MousePos = sf::Mouse::getPosition(*m_pWindow);

                    if (m_StartButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePos)))
                    {
                        std::cout << "[MainMenu] Start gedrückt → Wechsle zu LoadMap-Phase\n";
                        return CPhase::Load;
                    }

                    if (m_ExitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(MousePos)))
                    {
                        return CPhase::Finalize;
                    }
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

    // -----------------------------------------------------------------------------

    void CMainMenuPhase::OnInternLeave()
    {
        // -----------------------------------------------------------------------------
        // Ressourcen schließen
        // -----------------------------------------------------------------------------
        std::cout << "[MainMenu] Verlassen\n";
        m_pWindow->close();
    }
}