#include "logic_facet.h"

namespace Logic
{
    // -----------------------------------------------------------------------------

    CLogicFacet::CLogicFacet()
        : m_VelocityX(0.0f)
        , m_VelocityY(0.0f)
    {
    }

    // -----------------------------------------------------------------------------

    float CLogicFacet::GetVelocityX() const
    {
        return m_VelocityX;
    }

    // -----------------------------------------------------------------------------

    void CLogicFacet::SetVelocityX(float _Vx)
    {
        m_VelocityX = _Vx;
    }

    // -----------------------------------------------------------------------------

    float CLogicFacet::GetVelocityY() const
    {
        return m_VelocityY;
    }

    // -----------------------------------------------------------------------------

    void CLogicFacet::SetVelocityY(float _Vy)
    {
        m_VelocityY = _Vy;
    }
}
