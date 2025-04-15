#include "logic_facet.h"

namespace Logic
{
    CLogicFacet::CLogicFacet()
        : m_VelocityX(0.0f)
        , m_VelocityY(0.0f)
    {
    }

    float CLogicFacet::GetVelocityX() const 
    { 
        return m_VelocityX; 
    }
    
    void CLogicFacet::SetVelocityX(float vx) 
    { 
        m_VelocityX = vx; 
    }

    float CLogicFacet::GetVelocityY() const 
    { 
        return m_VelocityY; 
    }
    
    void CLogicFacet::SetVelocityY(float vy) 
    { 
        m_VelocityY = vy; 
    }
}
