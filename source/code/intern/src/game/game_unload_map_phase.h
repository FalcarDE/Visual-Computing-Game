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

        CUnloadMapPhase(const CUnloadMapPhase&) = delete;
        CUnloadMapPhase& operator=(const CUnloadMapPhase&) = delete;
    };
}