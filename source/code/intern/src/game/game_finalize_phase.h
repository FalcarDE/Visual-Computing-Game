#pragma once

#include "game_phase.h"

namespace Game
{
    class CFinalizePhase : public CPhase
    {
    public:
        static CFinalizePhase& GetInstance();

    private:
        CFinalizePhase();
        ~CFinalizePhase() override;

        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;

        CFinalizePhase(const CFinalizePhase&) = delete;
        CFinalizePhase& operator=(const CFinalizePhase&) = delete;
    };
}