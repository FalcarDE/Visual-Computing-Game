
#include "game_application.h"
#include "game_phase.h"
#include "game_play_phase.h"
#include "game_initialize_phase.h"
#include "game_main_menu_phase.h"
#include "iostream"
#include "game_finalize_phase.h"
#include "game_load_map_phase.h"
#include "game_unload_map_phase.h"

using namespace std;
using namespace Game;

// 1. Run() startet die Game Loop
// 2. RunPhases() verwaltet den Phasenwechsel
// 3. OnEnter() wird bei Eintritt aufgerufen
// 4. OnRun() wird regelmäßig aufgerufen
// 5. OnLeave() wird beim Verlassen aufgerufen
// 6. Rückgabe Undefined = beenden


namespace // Anonymous namespace
{
    class CApplication
    {
        public:

            static CApplication& GetInstance();     // Game::CApplication::GetInstance

        public:

            void Startup();                         // Game::CApplication::Startup
            void Run();                             // Game::CApplication::Run
            void Shutdown();                        // Game::CApplication::Shutdown

        private:

            CApplication();
           ~CApplication();

        private:

            int     m_IndexOfPhase;
            CPhase* m_pPhases[CPhase::NumberOfTypes];

        private:

            bool RunPhases();

        private:

            CApplication(const CApplication&) = delete;
            CApplication& operator = (const CApplication&) = delete;
    };
}

namespace // Anonymous namespace
{
    CApplication& CApplication::GetInstance()
    {
        // Scott Meyers Singleton
        static CApplication s_Instance;

        return s_Instance;
    }

    CApplication::CApplication()
        : m_IndexOfPhase(CPhase::Undefined)
        , m_pPhases     {}
    {
        m_pPhases[CPhase::Play] = &CPlayPhase::GetInstance();
    }

    CApplication::~CApplication()
    {
    }

    void CApplication::Startup()
    {
        std::cout << "[Startup] Phase-Registrierung startet...\n";

        // === Phasen instanziieren ===
        m_pPhases[CPhase::MainMenu] = &CMainMenuPhase::GetInstance();       // Menüphase
        m_pPhases[CPhase::Load] = &CLoadMapPhase::GetInstance();        // Mapladephase
        m_pPhases[CPhase::Initialize] = &CInitializePhase::GetInstance();     // Vorbereitung Spieler, Boden und Hindernis
        m_pPhases[CPhase::Play] = &CPlayPhase::GetInstance();           // Spielphase
        m_pPhases[CPhase::Unload] = &CUnloadMapPhase::GetInstance();      // Mapunloadphase
        m_pPhases[CPhase::Finalize] = &CFinalizePhase::GetInstance();       // Beenden

        // === Startphase festlegen ===
        m_IndexOfPhase = CPhase::MainMenu;

        // === Validierung ===
        assert(m_pPhases[CPhase::MainMenu] != nullptr && "MainMenu-Phase fehlt!");
        assert(m_pPhases[CPhase::Load] != nullptr && "LoadMap-Phase fehlt!");
        assert(m_pPhases[CPhase::Initialize] != nullptr && "Initialize-Phase fehlt!");
        assert(m_pPhases[CPhase::Play] != nullptr && "Play-Phase fehlt!");
        assert(m_pPhases[CPhase::Unload] != nullptr && "UnloadMap-Phase fehlt!");
        assert(m_pPhases[CPhase::Finalize] != nullptr && "Finalize-Phase fehlt!");

        // === Ausgabe registrierter Phasen ===
        std::cout << "[Startup] Registrierte Phasen:\n";
        std::cout << "  [0] Undefined\n";
        std::cout << "  [1] Finalize\n";
        std::cout << "  [2] Initialize\n";
        std::cout << "  [3] LoadMap\n";
        std::cout << "  [4] MainMenu\n";
        std::cout << "  [5] Play\n";
        std::cout << "  [6] UnloadMap\n";

        std::cout << "[Startup] Phase-Registrierung abgeschlossen\n";
    }

    void CApplication::Run()
    {
        std::cout << "[Run] Hauptschleife gestartet\n";

        for (;;)
        {
            bool HasEvent = false;  // <<< Jetzt wird RunPhases() ausgeführt

            if (HasEvent)
            {
                // später: OS/SFML Events
            }
            else
            {
                bool ShouldQuit = RunPhases();
                if (!ShouldQuit)
                {
                    std::cout << "[Run] Beendet durch Undefined Phase\n";
                    break;
                }
            }
        }

        std::cout << "[Run] Hauptschleife beendet\n";
    }


    void CApplication::Shutdown()
    {
        std::cout << "[Shutdown] Spiel wird beendet. Aufräumen beginnt...\n";

        for (int i = 0; i < CPhase::NumberOfTypes; ++i)
        {
            if (m_pPhases[i] != nullptr)
            {
                std::cout << "[Shutdown] Entferne Phase [" << i << "]\n";
                m_pPhases[i] = nullptr;  // Optional, zur Sicherheit
            }
        }

        m_IndexOfPhase = CPhase::Undefined;

        std::cout << "[Shutdown] Alle Phasen entfernt. Shutdown abgeschlossen.\n";
    }

    bool CApplication::RunPhases()
    {
        if (m_IndexOfPhase == CPhase::Undefined)
        {
            return false;
        }

        static bool firstRun = true;
        if (firstRun)
        {
            m_pPhases[m_IndexOfPhase]->OnEnter();
            firstRun = false;
        }

        CPhase::EType IndexOfNextPhase = m_pPhases[m_IndexOfPhase]->OnRun();

        if (IndexOfNextPhase == CPhase::Undefined)
        {
            return false;
        }

        if (IndexOfNextPhase != m_IndexOfPhase)
        {
            m_pPhases[m_IndexOfPhase]->OnLeave();
            m_IndexOfPhase = IndexOfNextPhase;
            m_pPhases[m_IndexOfPhase]->OnEnter();
        }

        return true;
    }
}

namespace Game
{
namespace Application
{
    void Startup()
    {
        CApplication::GetInstance().Startup();
    }

    void Run()
    {
        CApplication::GetInstance().Run();
    }

    void Shutdown()
    {
        CApplication::GetInstance().Shutdown();
    }
}
}

