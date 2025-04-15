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

        void OnInternEnter() override;
        EType OnInternRun() override;
        void OnInternLeave() override;

        CLoadMapPhase();
        ~CLoadMapPhase() override;

        CLoadMapPhase(const CLoadMapPhase&) = delete;
        CLoadMapPhase& operator=(const CLoadMapPhase&) = delete;

        std::unique_ptr<Data::CMetaEntity>    m_GroundMeta;
        std::unique_ptr<Graphics::CMetaFacet> m_GroundFacet;

        std::unique_ptr<Data::CMetaEntity>    m_ObstacleMeta;
        std::unique_ptr<Graphics::CMetaFacet> m_ObstacleFacet;
    };
}
