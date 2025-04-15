#pragma once

#include "game_phase.h"

namespace Game
{
    class CUnloadMapPhase : public CPhase
    {
    public:
        static CUnloadMapPhase& GetInstance();

    private:
        CUnloadMapPhase();
        ~CUnloadMapPhase() override;

        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;
    };
}
