#pragma once

#include "game_phase.h"
#include "../data/data_meta_entity.h"
#include "../graphics/graphics_facets.h"

#include <memory>

namespace Game
{
    class CInitializePhase : public CPhase
    {
    public:

        static CInitializePhase& GetInstance();

    private:

        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;

        CInitializePhase();
        ~CInitializePhase() override;

        CInitializePhase(const CInitializePhase&) = delete;
        CInitializePhase& operator=(const CInitializePhase&) = delete;

        std::unique_ptr<Data::CMetaEntity>   m_PlayerMeta;
        std::unique_ptr<Graphics::CMetaFacet> m_PlayerFacet;
    };
}
