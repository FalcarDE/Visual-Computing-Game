#include "game_application.h"  // Verwende deine echte Fassade!

#include <cassert>
#include <exception>
#include <iostream>

class CGameMainException : public std::exception
{
public:

    const char* what() const noexcept override
    {
        return "CGameMainException occurred";
    }
};

int main()
{
    try
    {
        // -----------------------------------------------------------------------------
        // Startup
        // -----------------------------------------------------------------------------
        std::cout << "[Main] Startup...\n";
        Game::Application::Startup();
        std::cout << "[Main] Startup erfolgreich\n";

        // -----------------------------------------------------------------------------
        // Run
        // -----------------------------------------------------------------------------
        std::cout << "[Main] Run...\n";
        Game::Application::Run();
        std::cout << "[Main] Run beendet\n";
    }
    catch (CGameMainException& e)
    {
        std::cerr << "[EXCEPTION] Benutzerdefiniert: " << e.what() << std::endl;
        assert(false && "CMyException wurde gefangen!");
    }
    catch (std::exception& e)
    {
        std::cerr << "[EXCEPTION] Standardfehler: " << e.what() << std::endl;
        assert(false && "std::exception wurde gefangen!");
    }
    catch (...)
    {
        std::cerr << "[EXCEPTION] Unbekannte Ausnahme w�hrend Startup/Run!\n";
        assert(false && "Unbekannte Ausnahme!");
    }

    try
    {
        // -----------------------------------------------------------------------------
        // Shutdown
        // -----------------------------------------------------------------------------
        std::cout << "[Main] Shutdown...\n";
        Game::Application::Shutdown();
        std::cout << "[Main] Shutdown abgeschlossen\n";
    }
    catch (CGameMainException& e)
    {
        std::cerr << "[EXCEPTION] Fehler beim Shutdown (CMyException): " << e.what() << std::endl;
        assert(false && "CMyException im Shutdown!");
    }
    catch (std::exception& e)
    {
        std::cerr << "[EXCEPTION] Fehler beim Shutdown: " << e.what() << std::endl;
        assert(false && "std::exception im Shutdown!");
    }
    catch (...)
    {
        std::cerr << "[EXCEPTION] Unbekannte Ausnahme beim Shutdown!\n";
        assert(false && "Unbekannte Ausnahme im Shutdown!");
    }

    std::cout << "[Main] Programm beendet\n";
    return 0;
}
