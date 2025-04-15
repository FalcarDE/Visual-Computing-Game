#pragma once

#include "game_phase.h"
#include "../data/data_meta_entity.h"
#include "../graphics/graphics_facets.h"
#include <memory>

namespace Game
{
    class CLoadMapPhase : public CPhase
    {
    public:
        static CLoadMapPhase& GetInstance();

    private:
        CLoadMapPhase();
        ~CLoadMapPhase() override;

        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;

    private:
        std::unique_ptr<Data::CMetaEntity> m_GroundMeta;
        std::unique_ptr<Graphics::CMetaFacet> m_GroundFacet;

        std::unique_ptr<Data::CMetaEntity> m_ObstacleMeta;
        std::unique_ptr<Graphics::CMetaFacet> m_ObstacleFacet;

    };
}