#pragma once

namespace Logic
{
    class CLogicFacet
    {
    public:

        CLogicFacet();
        ~CLogicFacet() = default;

        float GetVelocityX() const;
        void SetVelocityX(float _Vx);

        float GetVelocityY() const;
        void SetVelocityY(float _Vy);

    private:

        float m_VelocityX;
        float m_VelocityY;
    };
}