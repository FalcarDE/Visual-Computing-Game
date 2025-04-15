#include "game_finalize_phase.h"

#include <iostream>

namespace Game
{
    // -----------------------------------------------------------------------------

    CFinalizePhase::CFinalizePhase() = default;

    // -----------------------------------------------------------------------------

    CFinalizePhase::~CFinalizePhase() = default;

    // -----------------------------------------------------------------------------

    CFinalizePhase& CFinalizePhase::GetInstance()
    {
        static CFinalizePhase s_Instance;
        return s_Instance;
    }

    // -----------------------------------------------------------------------------

    void CFinalizePhase::OnInternEnter()
    {
        // -----------------------------------------------------------------------------
        // Phase startet – Spiel wird beendet.
        // -----------------------------------------------------------------------------
        std::cout << "[FinalizePhase] Spiel wird beendet. Auf Wiedersehen!\n";
    }

    // -----------------------------------------------------------------------------

    CPhase::EType CFinalizePhase::OnInternRun()
    {
        return CPhase::Undefined;
    }

    // -----------------------------------------------------------------------------

    void CFinalizePhase::OnInternLeave()
    {
        // -----------------------------------------------------------------------------
        // Phase wurde verlassen.
        // -----------------------------------------------------------------------------
        std::cout << "[FinalizePhase] Phase verlassen\n";
    }
}