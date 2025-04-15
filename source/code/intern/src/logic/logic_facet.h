#pragma once

namespace Logic
{
    class CLogicFacet
    {
    public:
        CLogicFacet();
        ~CLogicFacet() = default;

        float GetVelocityX() const;
        void SetVelocityX(float vx);

        float GetVelocityY() const;
        void SetVelocityY(float vy);

    private:
        float m_VelocityX;
        float m_VelocityY;
    };
}
