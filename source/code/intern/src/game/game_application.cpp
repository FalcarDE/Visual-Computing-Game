#include "game_application.h"
#include "game_finalize_phase.h"
#include "game_initialize_phase.h"
#include "game_load_map_phase.h"
#include "game_main_menu_phase.h"
#include "game_phase.h"
#include "game_play_phase.h"
#include "game_unload_map_phase.h"

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <list>
#include <memory>

using namespace std;
using namespace Game;

namespace
{
    class CApplication
    {
    public:

        static CApplication& GetInstance();

        void Startup();
        void Run();
        void Shutdown();

    private:

        CApplication();
        ~CApplication();

        bool RunPhases();

        int     m_IndexOfPhase;
        CPhase* m_pPhases[CPhase::NumberOfTypes];

        CApplication(const CApplication&) = delete;
        CApplication& operator=(const CApplication&) = delete;
    };
}

// -----------------------------------------------------------------------------
// Singleton-Instanz
// -----------------------------------------------------------------------------

CApplication& CApplication::GetInstance()
{
    static CApplication s_Instance;
    return s_Instance;
}

// -----------------------------------------------------------------------------
// Konstruktor
// -----------------------------------------------------------------------------

CApplication::CApplication()
    : m_IndexOfPhase(CPhase::Undefined)
    , m_pPhases{}
{
    m_pPhases[CPhase::Play] = &CPlayPhase::GetInstance();
}

// -----------------------------------------------------------------------------
// Destruktor
// -----------------------------------------------------------------------------

CApplication::~CApplication()
{
}

// -----------------------------------------------------------------------------
// Startup – Initialisiert das Spiel
// -----------------------------------------------------------------------------

void CApplication::Startup()
{
    std::cout << "[Startup] Phase-Registrierung startet...\n";

    m_pPhases[CPhase::MainMenu] = &CMainMenuPhase::GetInstance();
    m_pPhases[CPhase::Load] = &CLoadMapPhase::GetInstance();
    m_pPhases[CPhase::Initialize] = &CInitializePhase::GetInstance();
    m_pPhases[CPhase::Play] = &CPlayPhase::GetInstance();
    m_pPhases[CPhase::Unload] = &CUnloadMapPhase::GetInstance();
    m_pPhases[CPhase::Finalize] = &CFinalizePhase::GetInstance();

    m_IndexOfPhase = CPhase::MainMenu;

    assert(m_pPhases[CPhase::MainMenu] != nullptr && "MainMenu-Phase fehlt!");
    assert(m_pPhases[CPhase::Load] != nullptr && "LoadMap-Phase fehlt!");
    assert(m_pPhases[CPhase::Initialize] != nullptr && "Initialize-Phase fehlt!");
    assert(m_pPhases[CPhase::Play] != nullptr && "Play-Phase fehlt!");
    assert(m_pPhases[CPhase::Unload] != nullptr && "UnloadMap-Phase fehlt!");
    assert(m_pPhases[CPhase::Finalize] != nullptr && "Finalize-Phase fehlt!");

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

// -----------------------------------------------------------------------------
// Run – Hauptspielschleife
// -----------------------------------------------------------------------------

void CApplication::Run()
{
    std::cout << "[Run] Hauptschleife gestartet\n";

    for (;;)
    {
        bool HasEvent = false;

        if (HasEvent)
        {
            // später: OS/SFML Events
        }
        else
        {
            bool ShouldContinue = RunPhases();

            if (!ShouldContinue)
            {
                std::cout << "[Run] Beendet durch Undefined Phase\n";
                break;
            }
        }
    }

    std::cout << "[Run] Hauptschleife beendet\n";
}

// -----------------------------------------------------------------------------
// Shutdown – Aufräumen
// -----------------------------------------------------------------------------

void CApplication::Shutdown()
{
    std::cout << "[Shutdown] Spiel wird beendet. Aufräumen beginnt...\n";

    for (int Index = 0; Index < CPhase::NumberOfTypes; ++Index)
    {
        if (m_pPhases[Index] != nullptr)
        {
            std::cout << "[Shutdown] Entferne Phase [" << Index << "]\n";
            m_pPhases[Index] = nullptr;
        }
    }

    m_IndexOfPhase = CPhase::Undefined;

    std::cout << "[Shutdown] Alle Phasen entfernt. Shutdown abgeschlossen.\n";
}

// -----------------------------------------------------------------------------
// RunPhases – Phasenmanagement
// -----------------------------------------------------------------------------

bool CApplication::RunPhases()
{
    if (m_IndexOfPhase == CPhase::Undefined)
    {
        return false;
    }

    static bool FirstRun = true;

    if (FirstRun)
    {
        m_pPhases[m_IndexOfPhase]->OnEnter();
        FirstRun = false;
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

// -----------------------------------------------------------------------------
// Game::Application – Öffentliche API
// -----------------------------------------------------------------------------

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
