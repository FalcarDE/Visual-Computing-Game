#include "game_unload_map_phase.h"
#include "game_play_phase.h"

#include <iostream>

namespace Game
{
    // -----------------------------------------------------------------------------

    CUnloadMapPhase::CUnloadMapPhase() = default;

    // -----------------------------------------------------------------------------

    CUnloadMapPhase::~CUnloadMapPhase() = default;

    // -----------------------------------------------------------------------------

    CUnloadMapPhase& CUnloadMapPhase::GetInstance()
    {
        static CUnloadMapPhase s_Instance;
        return s_Instance;
    }

    // -----------------------------------------------------------------------------

    void CUnloadMapPhase::OnInternEnter()
    {
        // -----------------------------------------------------------------------------
        // Welt zurücksetzen und Ressourcen freigeben
        // -----------------------------------------------------------------------------
        std::cout << "[UnloadMap] OnInternEnter(): Welt und Ressourcen freigeben\n";
        CPlayPhase::GetInstance().ResetWorld();
    }

    // -----------------------------------------------------------------------------

    CPhase::EType CUnloadMapPhase::OnInternRun()
    {
        // -----------------------------------------------------------------------------
        // Rückkehr zum Hauptmenü
        // -----------------------------------------------------------------------------
        std::cout << "[Unload] Spielwelt wird zurückgesetzt...\n";
        std::cout << "[Unload] Welt entladen. Zurück zum Hauptmenü\n";

        return CPhase::MainMenu;
    }

    // -----------------------------------------------------------------------------

    void CUnloadMapPhase::OnInternLeave()
    {
        // -----------------------------------------------------------------------------
        // Abschlussmeldung
        // -----------------------------------------------------------------------------
        std::cout << "[UnloadMap] OnInternLeave(): abgeschlossen\n";
    }
}
