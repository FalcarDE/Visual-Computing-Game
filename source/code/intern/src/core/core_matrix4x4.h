
////////////////////////////////////////////////////////////////////////////////
/// \file    core_matrix4x4.h
///
/// \author  Joerg Sahm
/// \author  Copyright (c) Joerg Sahm. All rights reserved.
///
/// \date    2011
///
/// \version 1.0
///
/// \brief   A brief file description.
///
/// A detailed file description.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "core_constants.h"
#include "core_operations.h"
#include "core_swap.h"

#include <assert.h>

namespace Core
{
    template <typename T>
    class CMatrix3x3;
    template <typename T>
    class CVector3;
    template <typename T>
    class CVector4;
} // namespace Core

namespace Core
{
    template <typename T>
    class CMatrix4x4
    {
        public:

            static const CMatrix4x4<T> s_Zero;
            static const CMatrix4x4<T> s_Identity;

        public:

            using CThis     = CMatrix4x4<T>;
            using CLine3    = CVector3<T>;
            using CLine4    = CVector4<T>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;

        public:

            static constexpr size_t s_NumberOfRows       = 4;
            static constexpr size_t s_NumberOfColumns    = 4;
            static constexpr size_t s_NumberOfComponents = s_NumberOfRows * s_NumberOfColumns;

        public:

            enum EUninitialized  
            { 
                Uninitialized,
            };

        public:

            enum EIndices
            {
                A11, A12, A13, A14,
                A21, A22, A23, A24,
                A31, A32, A33, A34,
                A41, A42, A43, A44,
            };

        public:

            inline CMatrix4x4();
            inline CMatrix4x4(const CThis& _rMatrix);		
            inline explicit CMatrix4x4(EUninitialized);
            inline explicit CMatrix4x4(XConstPtr _pCoefficients);
            inline explicit CMatrix4x4(const CLine4* _pRows);
            inline CMatrix4x4(const CLine4& _rRow0, const CLine4& _rRow1, const CLine4& _rRow2, const CLine4& _rRow3);
            inline CMatrix4x4(X _11, X _12, X _13, X _14, X _21, X _22, X _23, X _24, X _31, X _32, X _33, X _34, X _41, X _42, X _43, X _44);

        public:

            inline CThis& operator = (const CMatrix3x3<X>& _rMatrix);
            inline CThis& operator = (const CThis& _rMatrix);

        public:

            inline CLine4& operator [] (size_t _Index);
            inline const CLine4& operator [] (size_t _Index) const;

        public:

            inline CThis& operator += (const CThis& _rMatrix);
            inline CThis& operator -= (const CThis& _rMatrix);
            inline CThis& operator *= (const CThis& _rMatrix);

            inline CThis& operator *= (X _Scalar);
            inline CThis& operator /= (X _Scalar);

            inline CThis operator + (const CThis& _rMatrix) const;
            inline CThis operator - (const CThis& _rMatrix) const;
            inline CThis operator * (const CThis& _rMatrix) const;

            inline CThis operator * (X _Scalar) const;
            inline CThis operator / (X _Scalar) const;

            inline CLine3 operator * (const CLine3& _rVector) const;
            inline CLine4 operator * (const CLine4& _rVector) const;

            inline CThis operator - () const;

        public:

            inline bool operator == (const CThis& _rMatrix) const;
            inline bool operator != (const CThis& _rMatrix) const;

        public:

            inline CThis& Set(const CThis& _rMatrix);
            inline CThis& Set(XConstPtr _pCoefficients);
            inline CThis& Set(const CLine4* _pRows);
            inline CThis& Set(const CLine4& _rRow0, const CLine4& _rRow1, const CLine4& _rRow2, const CLine4& _rRow3);
            inline CThis& Set(X _11, X _12, X _13, X _14, X _21, X _22, X _23, X _24, X _31, X _32, X _33, X _34, X _41, X _42, X _43, X _44);

            inline CThis& SetZero();
            inline CThis& SetIdentity();

            inline CThis& SetRow(size_t _Index, X _A0, X _A1, X _A2, X _A3);
            inline CThis& SetRow(size_t _Index, const CLine4& _rVector);
            inline CThis& SetRow(size_t _Index, const CLine3& _rVector, X _A3 = 1);

            inline CLine4& GetRow(size_t _Index);
            inline const CLine4& GetRow(size_t _Index) const;

            inline CThis& SetColumn(size_t _Index, X _A0, X _A1, X _A2, X _A3);
            inline CThis& SetColumn(size_t _Index, const CLine4& _rVector);
            inline CThis& SetColumn(size_t _Index, const CLine3& _rVector, X _A3 = 1);

            inline CLine4 GetColumn(size_t _Index) const;

        public:

            inline CThis& Transpose();
            inline CThis GetTransposed() const;

            inline CThis& Invert();
            inline CThis GetInverted() const;

        public:

            inline CThis& SetTranslation(float _X, float _Y, float _Z);
            inline CThis& SetTranslation(const CLine3& _rVector);
            inline CThis& SetTranslation(const CLine4& _rVector);

            inline CLine3 GetTranslation3() const;
            inline CLine4 GetTranslation4() const;

            inline CThis& SetScale(X _Scale);
            inline CThis& SetScale(X _ScaleX, X _ScaleY, X _ScaleZ);
            inline CThis& SetScale(const CLine3& _rScale);

            inline CLine3 GetScale() const;

            inline CThis& SetRotationX(float _Angle);
            inline CThis& SetRotationY(float _Angle);
            inline CThis& SetRotationZ(float _Angle);
            inline CThis& SetRotation(float _AngleX, float _AngleY, float _AngleZ);
            inline CThis& SetRotation(float _AxisX, float _AxisY, float _AxisZ, float _Angle);
            inline CThis& SetRotation(const CLine3& _rAxis, float _Angle);
            inline CThis& SetRotation(const CLine3& _rVectorX, const CLine3& _rVectorY, const CLine3& _rVectorZ);
            inline CThis& SetRotation(const CMatrix3x3<X>& _rMatrix);

            inline CMatrix3x3<T> GetRotation() const;

            inline void GetEulerAngles(float& _rAngleX, float& _rAngleY, float& _rAngleZ) const;
            inline CLine3 GetEulerAngles() const;

        public:

            inline CThis& SetPerspective(X _Width, X _Height, X _Near, X _Far);
            inline CThis& SetPerspective(X _Left, X _Right, X _Bottom, X _Top, X _Near, X _Far);
            inline CThis& SetFieldOfView(X _FOVY, X _Aspect, X _Near, X _Far);
            inline CThis& SetOrthographic(X _Width, X _Height, X _Near, X _Far);
            inline CThis& SetOrthographic(X _Left, X _Right, X _Bottom, X _Top, X _Near, X _Far);

        private:

            X m_A[s_NumberOfComponents];
    };
} // namespace Core

#include "core_matrix3x3.h"
#include "core_vector3.h"
#include "core_vector4.h"

namespace Core
{
    template <typename T>
    const CMatrix4x4<T> CMatrix4x4<T>::s_Zero     = CMatrix4x4(T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0));
    template <typename T>
    const CMatrix4x4<T> CMatrix4x4<T>::s_Identity = CMatrix4x4(T(1), T(0), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(0), T(1));
} // namespace Core

namespace Core
{
    template <typename T>
    inline CMatrix4x4<T>::CMatrix4x4()
    {
        SetIdentity();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix4x4<T>::CMatrix4x4(const CThis& _rMatrix)
    {
        Set(_rMatrix);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix4x4<T>::CMatrix4x4(EUninitialized)
    {
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix4x4<T>::CMatrix4x4(XConstPtr _pCoefficients)
    {
        Set(_pCoefficients);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix4x4<T>::CMatrix4x4(const CLine4* _pRows)
    {
        Set(_pRows);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix4x4<T>::CMatrix4x4(const CLine4& _rRow0, const CLine4& _rRow1, const CLine4& _rRow2, const CLine4& _rRow3)
    {
        Set(_rRow0, _rRow1, _rRow2, _rRow3);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix4x4<T>::CMatrix4x4(X _11, X _12, X _13, X _14, X _21, X _22, X _23, X _24, X _31, X _32, X _33, X _34, X _41, X _42, X _43, X _44)
    {
        Set(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::operator = (const CMatrix3x3<X>& _rMatrix)
    {
        using C3x3 = CMatrix3x3<X>;

        m_A[A11] = _rMatrix.m_A[C3x3::A11]; m_A[A12] = _rMatrix.m_A[C3x3::A12]; m_A[A13] = _rMatrix.m_A[C3x3::A13]; m_A[A14] = static_cast<X>(0);
        m_A[A21] = _rMatrix.m_A[C3x3::A21]; m_A[A22] = _rMatrix.m_A[C3x3::A22]; m_A[A23] = _rMatrix.m_A[C3x3::A23]; m_A[A24] = static_cast<X>(0);
        m_A[A31] = _rMatrix.m_A[C3x3::A31]; m_A[A32] = _rMatrix.m_A[C3x3::A32]; m_A[A33] = _rMatrix.m_A[C3x3::A33]; m_A[A34] = static_cast<X>(0);
        m_A[A41] = static_cast<X>(0);       m_A[A42] = static_cast<X>(0);       m_A[A43] = static_cast<X>(0);       m_A[A44] = static_cast<X>(1);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::operator = (const CThis& _rMatrix)
    {
        Set(_rMatrix);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine4& CMatrix4x4<T>::operator[] (size_t _Index)
    {
        return GetRow(_Index);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CMatrix4x4<T>::CLine4& CMatrix4x4<T>::operator[] (size_t _Index) const
    {
        return GetRow(_Index);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::operator += (const CThis& _rMatrix)
    {
        m_A[A11] += _rMatrix.m_A[A11]; m_A[A12] += _rMatrix.m_A[A12]; m_A[A13] += _rMatrix.m_A[A13]; m_A[A14] += _rMatrix.m_A[A14];
        m_A[A21] += _rMatrix.m_A[A21]; m_A[A22] += _rMatrix.m_A[A22]; m_A[A23] += _rMatrix.m_A[A23]; m_A[A24] += _rMatrix.m_A[A24];
        m_A[A31] += _rMatrix.m_A[A31]; m_A[A32] += _rMatrix.m_A[A32]; m_A[A33] += _rMatrix.m_A[A33]; m_A[A34] += _rMatrix.m_A[A34];
        m_A[A41] += _rMatrix.m_A[A41]; m_A[A42] += _rMatrix.m_A[A42]; m_A[A43] += _rMatrix.m_A[A43]; m_A[A44] += _rMatrix.m_A[A44];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::operator -= (const CThis& _rMatrix)
    {
        m_A[A11] -= _rMatrix.m_A[A11]; m_A[A12] -= _rMatrix.m_A[A12]; m_A[A13] -= _rMatrix.m_A[A13]; m_A[A14] -= _rMatrix.m_A[A14];
        m_A[A21] -= _rMatrix.m_A[A21]; m_A[A22] -= _rMatrix.m_A[A22]; m_A[A23] -= _rMatrix.m_A[A23]; m_A[A24] -= _rMatrix.m_A[A24];
        m_A[A31] -= _rMatrix.m_A[A31]; m_A[A32] -= _rMatrix.m_A[A32]; m_A[A33] -= _rMatrix.m_A[A33]; m_A[A34] -= _rMatrix.m_A[A34];
        m_A[A41] -= _rMatrix.m_A[A41]; m_A[A42] -= _rMatrix.m_A[A42]; m_A[A43] -= _rMatrix.m_A[A43]; m_A[A44] -= _rMatrix.m_A[A44];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::operator *= (const CThis& _rMatrix)
    {
        return Set((*this) * _rMatrix);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis CMatrix4x4<T>::operator + (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] + _rMatrix.m_A[A11]; A[A12] = m_A[A12] + _rMatrix.m_A[A12]; A[A13] = m_A[A13] + _rMatrix.m_A[A13]; A[A14] = m_A[A14] + _rMatrix.m_A[A14];
        A[A21] = m_A[A21] + _rMatrix.m_A[A21]; A[A22] = m_A[A22] + _rMatrix.m_A[A22]; A[A23] = m_A[A23] + _rMatrix.m_A[A23]; A[A24] = m_A[A24] + _rMatrix.m_A[A24];
        A[A31] = m_A[A31] + _rMatrix.m_A[A31]; A[A32] = m_A[A32] + _rMatrix.m_A[A32]; A[A33] = m_A[A33] + _rMatrix.m_A[A33]; A[A34] = m_A[A34] + _rMatrix.m_A[A34];
        A[A41] = m_A[A41] + _rMatrix.m_A[A41]; A[A42] = m_A[A42] + _rMatrix.m_A[A42]; A[A43] = m_A[A43] + _rMatrix.m_A[A43]; A[A44] = m_A[A44] + _rMatrix.m_A[A44];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis CMatrix4x4<T>::operator - (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] - _rMatrix.m_A[A11]; A[A12] = m_A[A12] - _rMatrix.m_A[A12]; A[A13] = m_A[A13] - _rMatrix.m_A[A13]; A[A14] = m_A[A14] - _rMatrix.m_A[A14];
        A[A21] = m_A[A21] - _rMatrix.m_A[A21]; A[A22] = m_A[A22] - _rMatrix.m_A[A22]; A[A23] = m_A[A23] - _rMatrix.m_A[A23]; A[A24] = m_A[A24] - _rMatrix.m_A[A24];
        A[A31] = m_A[A31] - _rMatrix.m_A[A31]; A[A32] = m_A[A32] - _rMatrix.m_A[A32]; A[A33] = m_A[A33] - _rMatrix.m_A[A33]; A[A34] = m_A[A34] - _rMatrix.m_A[A34];
        A[A41] = m_A[A41] - _rMatrix.m_A[A41]; A[A42] = m_A[A42] - _rMatrix.m_A[A42]; A[A43] = m_A[A43] - _rMatrix.m_A[A43]; A[A44] = m_A[A44] - _rMatrix.m_A[A44];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis CMatrix4x4<T>::operator * (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] * _rMatrix.m_A[A11] + m_A[A12] * _rMatrix.m_A[A21] + m_A[A13] * _rMatrix.m_A[A31] + m_A[A14] * _rMatrix.m_A[A41];
        A[A12] = m_A[A11] * _rMatrix.m_A[A12] + m_A[A12] * _rMatrix.m_A[A22] + m_A[A13] * _rMatrix.m_A[A32] + m_A[A14] * _rMatrix.m_A[A42];
        A[A13] = m_A[A11] * _rMatrix.m_A[A13] + m_A[A12] * _rMatrix.m_A[A23] + m_A[A13] * _rMatrix.m_A[A33] + m_A[A14] * _rMatrix.m_A[A43];
        A[A14] = m_A[A11] * _rMatrix.m_A[A14] + m_A[A12] * _rMatrix.m_A[A24] + m_A[A13] * _rMatrix.m_A[A34] + m_A[A14] * _rMatrix.m_A[A44];
        A[A21] = m_A[A21] * _rMatrix.m_A[A11] + m_A[A22] * _rMatrix.m_A[A21] + m_A[A23] * _rMatrix.m_A[A31] + m_A[A24] * _rMatrix.m_A[A41];
        A[A22] = m_A[A21] * _rMatrix.m_A[A12] + m_A[A22] * _rMatrix.m_A[A22] + m_A[A23] * _rMatrix.m_A[A32] + m_A[A24] * _rMatrix.m_A[A42];
        A[A23] = m_A[A21] * _rMatrix.m_A[A13] + m_A[A22] * _rMatrix.m_A[A23] + m_A[A23] * _rMatrix.m_A[A33] + m_A[A24] * _rMatrix.m_A[A43];
        A[A24] = m_A[A21] * _rMatrix.m_A[A14] + m_A[A22] * _rMatrix.m_A[A24] + m_A[A23] * _rMatrix.m_A[A34] + m_A[A24] * _rMatrix.m_A[A44];
        A[A31] = m_A[A31] * _rMatrix.m_A[A11] + m_A[A32] * _rMatrix.m_A[A21] + m_A[A33] * _rMatrix.m_A[A31] + m_A[A34] * _rMatrix.m_A[A41];
        A[A32] = m_A[A31] * _rMatrix.m_A[A12] + m_A[A32] * _rMatrix.m_A[A22] + m_A[A33] * _rMatrix.m_A[A32] + m_A[A34] * _rMatrix.m_A[A42];
        A[A33] = m_A[A31] * _rMatrix.m_A[A13] + m_A[A32] * _rMatrix.m_A[A23] + m_A[A33] * _rMatrix.m_A[A33] + m_A[A34] * _rMatrix.m_A[A43];
        A[A34] = m_A[A31] * _rMatrix.m_A[A14] + m_A[A32] * _rMatrix.m_A[A24] + m_A[A33] * _rMatrix.m_A[A34] + m_A[A34] * _rMatrix.m_A[A44];
        A[A41] = m_A[A41] * _rMatrix.m_A[A11] + m_A[A42] * _rMatrix.m_A[A21] + m_A[A43] * _rMatrix.m_A[A31] + m_A[A44] * _rMatrix.m_A[A41];
        A[A42] = m_A[A41] * _rMatrix.m_A[A12] + m_A[A42] * _rMatrix.m_A[A22] + m_A[A43] * _rMatrix.m_A[A32] + m_A[A44] * _rMatrix.m_A[A42];
        A[A43] = m_A[A41] * _rMatrix.m_A[A13] + m_A[A42] * _rMatrix.m_A[A23] + m_A[A43] * _rMatrix.m_A[A33] + m_A[A44] * _rMatrix.m_A[A43];
        A[A44] = m_A[A41] * _rMatrix.m_A[A14] + m_A[A42] * _rMatrix.m_A[A24] + m_A[A43] * _rMatrix.m_A[A34] + m_A[A44] * _rMatrix.m_A[A44];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T> 
    inline typename CMatrix4x4<T>::CLine3 CMatrix4x4<T>::operator * (const CLine3& _rVector) const
    {
        X V[CLine3::s_NumberOfComponents];

        V[0] = m_A[A11] * _rVector[0] + m_A[A12] * _rVector[1] + m_A[A13] * _rVector[2] + m_A[A14];
        V[1] = m_A[A21] * _rVector[0] + m_A[A22] * _rVector[1] + m_A[A23] * _rVector[2] + m_A[A24];
        V[2] = m_A[A31] * _rVector[0] + m_A[A32] * _rVector[1] + m_A[A33] * _rVector[2] + m_A[A34];

        return CLine3(V[0], V[1], V[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine4 CMatrix4x4<T>::operator * (const CLine4& _rVector) const
    {
        X V[CLine4::s_NumberOfComponents];

        V[0] = m_A[A11] * _rVector[0] + m_A[A12] * _rVector[1] + m_A[A13] * _rVector[2] + m_A[A14] * _rVector[3];
        V[1] = m_A[A21] * _rVector[0] + m_A[A22] * _rVector[1] + m_A[A23] * _rVector[2] + m_A[A24] * _rVector[3];
        V[2] = m_A[A31] * _rVector[0] + m_A[A32] * _rVector[1] + m_A[A33] * _rVector[2] + m_A[A34] * _rVector[3];
        V[3] = m_A[A41] * _rVector[0] + m_A[A42] * _rVector[1] + m_A[A43] * _rVector[2] + m_A[A44] * _rVector[3];

        return CLine4(V[0], V[1], V[2], V[3]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CMatrix4x4<T>::operator == (const CThis& _rMatrix) const
    {
        return ((*this)[0] == _rMatrix[0]) && ((*this)[1] == _rMatrix[1]) && ((*this)[2] == _rMatrix[2]) && ((*this)[3] == _rMatrix[3]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CMatrix4x4<T>::operator != (const CThis& _rMatrix) const
    {
        return ((*this)[0] != _rMatrix[0]) || ((*this)[1] != _rMatrix[1]) || ((*this)[2] != _rMatrix[2]) || ((*this)[3] != _rMatrix[3]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::Set(const CThis& _rMatrix)
    {
        m_A[A11] = _rMatrix.m_A[A11]; m_A[A12] = _rMatrix.m_A[A12]; m_A[A13] = _rMatrix.m_A[A13]; m_A[A14] = _rMatrix.m_A[A14];
        m_A[A21] = _rMatrix.m_A[A21]; m_A[A22] = _rMatrix.m_A[A22]; m_A[A23] = _rMatrix.m_A[A23]; m_A[A24] = _rMatrix.m_A[A24];
        m_A[A31] = _rMatrix.m_A[A31]; m_A[A32] = _rMatrix.m_A[A32]; m_A[A33] = _rMatrix.m_A[A33]; m_A[A34] = _rMatrix.m_A[A34];
        m_A[A41] = _rMatrix.m_A[A41]; m_A[A42] = _rMatrix.m_A[A42]; m_A[A43] = _rMatrix.m_A[A43]; m_A[A44] = _rMatrix.m_A[A44];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::Set(XConstPtr _pCoefficients)
    {
        assert(_pCoefficients != 0);

        m_A[A11] = _pCoefficients[A11]; m_A[A12] = _pCoefficients[A12]; m_A[A13] = _pCoefficients[A13]; m_A[A14] = _pCoefficients[A14];
        m_A[A21] = _pCoefficients[A21]; m_A[A22] = _pCoefficients[A22]; m_A[A23] = _pCoefficients[A23]; m_A[A24] = _pCoefficients[A24];
        m_A[A31] = _pCoefficients[A31]; m_A[A32] = _pCoefficients[A32]; m_A[A33] = _pCoefficients[A33]; m_A[A34] = _pCoefficients[A34];
        m_A[A41] = _pCoefficients[A41]; m_A[A42] = _pCoefficients[A42]; m_A[A43] = _pCoefficients[A43]; m_A[A44] = _pCoefficients[A44];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::Set(const CLine4* _pRows)
    {
        assert(_pRows != 0);

        m_A[A11] = _pRows[0][0]; m_A[A12] = _pRows[0][1]; m_A[A13] = _pRows[0][2]; m_A[A14] = _pRows[0][3];
        m_A[A21] = _pRows[1][0]; m_A[A22] = _pRows[1][1]; m_A[A23] = _pRows[1][2]; m_A[A24] = _pRows[1][3];
        m_A[A31] = _pRows[2][0]; m_A[A32] = _pRows[2][1]; m_A[A33] = _pRows[2][2]; m_A[A34] = _pRows[2][3];
        m_A[A41] = _pRows[3][0]; m_A[A42] = _pRows[3][1]; m_A[A43] = _pRows[3][2]; m_A[A44] = _pRows[3][3];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::Set(const CLine4& _rRow0, const CLine4& _rRow1, const CLine4& _rRow2, const CLine4& _rRow3)
    {
        m_A[A11] = _rRow0[0]; m_A[A12] = _rRow0[1]; m_A[A13] = _rRow0[2]; m_A[A14] = _rRow0[3];
        m_A[A21] = _rRow1[0]; m_A[A22] = _rRow1[1]; m_A[A23] = _rRow1[2]; m_A[A24] = _rRow1[3];
        m_A[A31] = _rRow2[0]; m_A[A32] = _rRow2[1]; m_A[A33] = _rRow2[2]; m_A[A34] = _rRow2[3];
        m_A[A41] = _rRow3[0]; m_A[A42] = _rRow3[1]; m_A[A43] = _rRow3[2]; m_A[A44] = _rRow3[3];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::Set(X _11, X _12, X _13, X _14, X _21, X _22, X _23, X _24, X _31, X _32, X _33, X _34, X _41, X _42, X _43, X _44)
    {
        m_A[A11] = _11; m_A[A12] = _12; m_A[A13] = _13; m_A[A14] = _14;
        m_A[A21] = _21; m_A[A22] = _22; m_A[A23] = _23; m_A[A24] = _24;
        m_A[A31] = _31; m_A[A32] = _32; m_A[A33] = _33; m_A[A34] = _34;
        m_A[A41] = _41; m_A[A42] = _42; m_A[A43] = _43; m_A[A44] = _44;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRow(size_t _Index, X _A0, X _A1, X _A2, X _A3)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_A0, _A1, _A2, _A3);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRow(size_t _Index, const CLine4& _rVector)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_rVector);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRow(size_t _Index, const CLine3& _rVector, X _A3)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_rVector[0], _rVector[1], _rVector[2], _A3);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine4& CMatrix4x4<T>::GetRow(size_t _Index)
    {
        assert(_Index < s_NumberOfRows);

        return *reinterpret_cast<CLine4*>(&m_A[_Index * s_NumberOfColumns]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CMatrix4x4<T>::CLine4& CMatrix4x4<T>::GetRow(size_t _Index) const
    {
        assert(_Index < s_NumberOfRows);

        return *reinterpret_cast<const CLine4*>(&m_A[_Index * s_NumberOfColumns]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetColumn(size_t _Index, X _A0, X _A1, X _A2, X _A3)
    {
        assert(_Index < s_NumberOfColumns);

        m_A[ 0 + _Index] = _A0;
        m_A[ 4 + _Index] = _A1;
        m_A[ 8 + _Index] = _A2;
        m_A[12 + _Index] = _A3;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetColumn(size_t _Index, const CLine4& _rVector)
    {
        return SetColumn(_Index, _rVector[0], _rVector[1], _rVector[2], _rVector[3]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetColumn(size_t _Index, const CLine3& _rVector, X _A3)
    {
        return SetColumn(_Index, _rVector[0], _rVector[1], _rVector[2], _A3);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine4 CMatrix4x4<T>::GetColumn(size_t _Index) const
    {
        X V[CLine4::s_NumberOfComponents];

        assert(_Index < s_NumberOfColumns);

        V[0] = m_A[ 0 + _Index];
        V[1] = m_A[ 4 + _Index];
        V[2] = m_A[ 8 + _Index];
        V[3] = m_A[12 + _Index];

        return CLine4(V[0], V[1], V[2], V[3]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetZero()
    {
        return Set(s_Zero);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetIdentity()
    {
        return Set(s_Identity);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::Transpose()
    {
        Swap(m_A[A21], m_A[A12]);
        Swap(m_A[A31], m_A[A13]);
        Swap(m_A[A32], m_A[A23]);
        Swap(m_A[A41], m_A[A14]);
        Swap(m_A[A42], m_A[A24]);
        Swap(m_A[A43], m_A[A34]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis CMatrix4x4<T>::GetTransposed() const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11]; A[A12] = m_A[A21]; A[A13] = m_A[A31]; A[A14] = m_A[A41];
        A[A21] = m_A[A12]; A[A22] = m_A[A22]; A[A23] = m_A[A32]; A[A24] = m_A[A42];
        A[A31] = m_A[A13]; A[A32] = m_A[A23]; A[A33] = m_A[A33]; A[A34] = m_A[A43];
        A[A41] = m_A[A14]; A[A42] = m_A[A24]; A[A43] = m_A[A34]; A[A44] = m_A[A44];

        return CThis(A);
    }

    // ------------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::Invert()
    {
        X Determinant;
        X ReciprocalDeterminant;
        X A[s_NumberOfComponents];
        X V[18];

        V[ 0] = m_A[A21] * m_A[A32] - m_A[A22] * m_A[A31];
        V[ 1] = m_A[A21] * m_A[A33] - m_A[A23] * m_A[A31];
        V[ 2] = m_A[A21] * m_A[A34] - m_A[A24] * m_A[A31];
        V[ 3] = m_A[A22] * m_A[A33] - m_A[A23] * m_A[A32];
        V[ 4] = m_A[A22] * m_A[A34] - m_A[A24] * m_A[A32];
        V[ 5] = m_A[A23] * m_A[A34] - m_A[A24] * m_A[A33];
        V[ 6] = m_A[A21] * m_A[A42] - m_A[A22] * m_A[A41];
        V[ 7] = m_A[A21] * m_A[A43] - m_A[A23] * m_A[A41];
        V[ 8] = m_A[A21] * m_A[A44] - m_A[A24] * m_A[A41];
        V[ 9] = m_A[A22] * m_A[A43] - m_A[A23] * m_A[A42];
        V[10] = m_A[A22] * m_A[A44] - m_A[A24] * m_A[A42];
        V[11] = m_A[A23] * m_A[A44] - m_A[A24] * m_A[A43];
        V[12] = m_A[A31] * m_A[A42] - m_A[A32] * m_A[A41];
        V[13] = m_A[A31] * m_A[A43] - m_A[A33] * m_A[A41];
        V[14] = m_A[A31] * m_A[A44] - m_A[A34] * m_A[A41];
        V[15] = m_A[A32] * m_A[A43] - m_A[A33] * m_A[A42];
        V[16] = m_A[A32] * m_A[A44] - m_A[A34] * m_A[A42];
        V[17] = m_A[A33] * m_A[A44] - m_A[A34] * m_A[A43];

        A[A11] = m_A[A22] * V[17] - m_A[A23] * V[16] + m_A[A24] * V[15];
        A[A12] = m_A[A13] * V[16] - m_A[A12] * V[17] - m_A[A14] * V[15];
        A[A13] = m_A[A12] * V[11] - m_A[A13] * V[10] + m_A[A14] * V[ 9];
        A[A14] = m_A[A13] * V[ 4] - m_A[A12] * V[ 5] - m_A[A14] * V[ 3];
        A[A21] = m_A[A23] * V[14] - m_A[A21] * V[17] - m_A[A24] * V[13];
        A[A22] = m_A[A11] * V[17] - m_A[A13] * V[14] + m_A[A14] * V[13];
        A[A23] = m_A[A13] * V[ 8] - m_A[A11] * V[11] - m_A[A14] * V[ 7];
        A[A24] = m_A[A11] * V[ 5] - m_A[A13] * V[ 2] + m_A[A14] * V[ 1];
        A[A31] = m_A[A21] * V[16] - m_A[A22] * V[14] + m_A[A24] * V[12];
        A[A32] = m_A[A12] * V[14] - m_A[A11] * V[16] - m_A[A14] * V[12];
        A[A33] = m_A[A11] * V[10] - m_A[A12] * V[ 8] + m_A[A14] * V[ 6];
        A[A34] = m_A[A12] * V[ 2] - m_A[A11] * V[ 4] - m_A[A14] * V[ 0];
        A[A41] = m_A[A22] * V[13] - m_A[A21] * V[15] - m_A[A23] * V[12];
        A[A42] = m_A[A11] * V[15] - m_A[A12] * V[13] + m_A[A13] * V[12];
        A[A43] = m_A[A12] * V[ 7] - m_A[A11] * V[ 9] - m_A[A13] * V[ 6];
        A[A44] = m_A[A11] * V[ 3] - m_A[A12] * V[ 1] + m_A[A13] * V[ 0];
        
        // ------------------------------------------------------------------------------
        // Calculate the determinant.
        // ------------------------------------------------------------------------------
        Determinant = m_A[A11] * A[A11] + m_A[A21] * A[A12] + m_A[A31] * A[A13] + m_A[A41] * A[A14];

        assert(!::Core::IsEqual(Determinant, static_cast<X>(0), SConstants<X>::s_Epsilon));

        ReciprocalDeterminant = static_cast<X>(1) / Determinant;

        m_A[A11] = A[A11] * ReciprocalDeterminant; m_A[A12] = A[A12] * ReciprocalDeterminant; m_A[A13] = A[A13] * ReciprocalDeterminant; m_A[A14] = A[A14] * ReciprocalDeterminant;
        m_A[A21] = A[A21] * ReciprocalDeterminant; m_A[A22] = A[A22] * ReciprocalDeterminant; m_A[A23] = A[A23] * ReciprocalDeterminant; m_A[A24] = A[A24] * ReciprocalDeterminant;
        m_A[A31] = A[A31] * ReciprocalDeterminant; m_A[A32] = A[A32] * ReciprocalDeterminant; m_A[A33] = A[A33] * ReciprocalDeterminant; m_A[A34] = A[A34] * ReciprocalDeterminant;
        m_A[A41] = A[A41] * ReciprocalDeterminant; m_A[A42] = A[A42] * ReciprocalDeterminant; m_A[A43] = A[A43] * ReciprocalDeterminant; m_A[A44] = A[A44] * ReciprocalDeterminant;

        return *this;
    }

    // ------------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis CMatrix4x4<T>::GetInverted() const
    {
        X Determinant;
        X ReciprocalDeterminant;
        X A[s_NumberOfComponents];
        X V[18];

        V[ 0] = m_A[A21] * m_A[A32] - m_A[A22] * m_A[A31];
        V[ 1] = m_A[A21] * m_A[A33] - m_A[A23] * m_A[A31];
        V[ 2] = m_A[A21] * m_A[A34] - m_A[A24] * m_A[A31];
        V[ 3] = m_A[A22] * m_A[A33] - m_A[A23] * m_A[A32];
        V[ 4] = m_A[A22] * m_A[A34] - m_A[A24] * m_A[A32];
        V[ 5] = m_A[A23] * m_A[A34] - m_A[A24] * m_A[A33];
        V[ 6] = m_A[A21] * m_A[A42] - m_A[A22] * m_A[A41];
        V[ 7] = m_A[A21] * m_A[A43] - m_A[A23] * m_A[A41];
        V[ 8] = m_A[A21] * m_A[A44] - m_A[A24] * m_A[A41];
        V[ 9] = m_A[A22] * m_A[A43] - m_A[A23] * m_A[A42];
        V[10] = m_A[A22] * m_A[A44] - m_A[A24] * m_A[A42];
        V[11] = m_A[A23] * m_A[A44] - m_A[A24] * m_A[A43];
        V[12] = m_A[A31] * m_A[A42] - m_A[A32] * m_A[A41];
        V[13] = m_A[A31] * m_A[A43] - m_A[A33] * m_A[A41];
        V[14] = m_A[A31] * m_A[A44] - m_A[A34] * m_A[A41];
        V[15] = m_A[A32] * m_A[A43] - m_A[A33] * m_A[A42];
        V[16] = m_A[A32] * m_A[A44] - m_A[A34] * m_A[A42];
        V[17] = m_A[A33] * m_A[A44] - m_A[A34] * m_A[A43];

        A[A11] = m_A[A22] * V[17] - m_A[A23] * V[16] + m_A[A24] * V[15];
        A[A12] = m_A[A13] * V[16] - m_A[A12] * V[17] - m_A[A14] * V[15];
        A[A13] = m_A[A12] * V[11] - m_A[A13] * V[10] + m_A[A14] * V[ 9];
        A[A14] = m_A[A13] * V[ 4] - m_A[A12] * V[ 5] - m_A[A14] * V[ 3];
        A[A21] = m_A[A23] * V[14] - m_A[A21] * V[17] - m_A[A24] * V[13];
        A[A22] = m_A[A11] * V[17] - m_A[A13] * V[14] + m_A[A14] * V[13];
        A[A23] = m_A[A13] * V[ 8] - m_A[A11] * V[11] - m_A[A14] * V[ 7];
        A[A24] = m_A[A11] * V[ 5] - m_A[A13] * V[ 2] + m_A[A14] * V[ 1];
        A[A31] = m_A[A21] * V[16] - m_A[A22] * V[14] + m_A[A24] * V[12];
        A[A32] = m_A[A12] * V[14] - m_A[A11] * V[16] - m_A[A14] * V[12];
        A[A33] = m_A[A11] * V[10] - m_A[A12] * V[ 8] + m_A[A14] * V[ 6];
        A[A34] = m_A[A12] * V[ 2] - m_A[A11] * V[ 4] - m_A[A14] * V[ 0];
        A[A41] = m_A[A22] * V[13] - m_A[A21] * V[15] - m_A[A23] * V[12];
        A[A42] = m_A[A11] * V[15] - m_A[A12] * V[13] + m_A[A13] * V[12];
        A[A43] = m_A[A12] * V[ 7] - m_A[A11] * V[ 9] - m_A[A13] * V[ 6];
        A[A44] = m_A[A11] * V[ 3] - m_A[A12] * V[ 1] + m_A[A13] * V[ 0];

        // ------------------------------------------------------------------------------
        // Calculate the determinant.
        // ------------------------------------------------------------------------------
        Determinant = m_A[A11] * A[A11] + m_A[A21] * A[A12] + m_A[A31] * A[A13] + m_A[A41] * A[A14];

        assert(!::Core::IsEqual(Determinant, static_cast<X>(0), SConstants<X>::s_Epsilon));

        ReciprocalDeterminant = static_cast<X>(1) / Determinant;

        A[A11] *= ReciprocalDeterminant; A[A12] *= ReciprocalDeterminant; A[A13] *= ReciprocalDeterminant; A[A14] *= ReciprocalDeterminant;
        A[A21] *= ReciprocalDeterminant; A[A22] *= ReciprocalDeterminant; A[A23] *= ReciprocalDeterminant; A[A24] *= ReciprocalDeterminant;
        A[A31] *= ReciprocalDeterminant; A[A32] *= ReciprocalDeterminant; A[A33] *= ReciprocalDeterminant; A[A34] *= ReciprocalDeterminant;
        A[A41] *= ReciprocalDeterminant; A[A42] *= ReciprocalDeterminant; A[A43] *= ReciprocalDeterminant; A[A44] *= ReciprocalDeterminant;

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetTranslation(float _X, float _Y, float _Z)
    {
        m_A[A41] = _X;
        m_A[A42] = _Y;
        m_A[A43] = _Z;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetTranslation(const CLine3& _rVector)
    {
        return SetTranslation(_rVector[0], _rVector[1], _rVector[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetTranslation(const CLine4& _rVector)
    {
        return SetTranslation(_rVector[0], _rVector[1], _rVector[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine3 CMatrix4x4<T>::GetTranslation3() const
    {
        return CLine3(m_A[A41], m_A[A42], m_A[A43]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine4 CMatrix4x4<T>::GetTranslation4() const
    {
        return CLine4(m_A[A41], m_A[A42], m_A[A43], static_cast<X>(1));
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetScale(X _Scale)
    {
        m_A[A11] = _Scale;
        m_A[A22] = _Scale;
        m_A[A33] = _Scale;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetScale(X _ScaleX, X _ScaleY, X _ScaleZ)
    {
        m_A[A11] = _ScaleX;
        m_A[A22] = _ScaleY;
        m_A[A33] = _ScaleZ;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetScale(const CLine3& _rScale)
    {
        return SetScale(_rScale[0], _rScale[1], _rScale[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine3 CMatrix4x4<T>::GetScale() const
    {
        return CLine3(m_A[A11], m_A[A22], m_A[A33]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotationX(float _Angle)
    {
        float Rad;
        float Cosinus;
        float Sinus;

        Rad     = ::Core::DegreesToRadians(_Angle);
        Cosinus = ::Core::Cos(Rad);
        Sinus   = ::Core::Sin(Rad);

        m_A[A11]                                  =  static_cast<X>(1);
        m_A[A12] = m_A[A21] = m_A[A13] = m_A[A31] =  static_cast<X>(0);
        m_A[A22] = m_A[A33]                       =  Cosinus;
        m_A[A23]                                  =  Sinus;
        m_A[A32]                                  = -Sinus;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotationY(float _Angle)
    {
        float Rad;
        float Cosinus;
        float Sinus;

        Rad     = ::Core::DegreesToRadians(_Angle);
        Cosinus = ::Core::Cos(Rad);
        Sinus   = ::Core::Sin(Rad);

        m_A[A22]                                  =  static_cast<X>(1);
        m_A[A12] = m_A[A21] = m_A[A23] = m_A[A32] =  static_cast<X>(0);
        m_A[A11] = m_A[A33]                       =  Cosinus;
        m_A[A31]                                  =  Sinus;
        m_A[A13]                                  = -Sinus;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotationZ(float _Angle)
    {
        float Rad;
        float Cosinus;
        float Sinus;

        Rad     = ::Core::DegreesToRadians(_Angle);
        Cosinus = ::Core::Cos(Rad);
        Sinus   = ::Core::Sin(Rad);

        m_A[A33]                                  =  static_cast<X>(1);
        m_A[A13] = m_A[A31] = m_A[A23] = m_A[A32] =  static_cast<X>(0);
        m_A[A11] = m_A[A22]                       =  Cosinus;
        m_A[A12]                                  =  Sinus;
        m_A[A21]                                  = -Sinus;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotation(float _AngleX, float _AngleY, float _AngleZ)
    {
        float RadX;
        float RadY;
        float RadZ;

        float SinX;
        float SinY;
        float SinZ;

        float CosX;
        float CosY;
        float CosZ;

        RadX = ::Core::DegreesToRadians(_AngleX);
        RadY = ::Core::DegreesToRadians(_AngleY);
        RadZ = ::Core::DegreesToRadians(_AngleZ);

        SinX = ::Core::Sin(RadX);
        SinY = ::Core::Sin(RadY);
        SinZ = ::Core::Sin(RadZ);

        CosX = ::Core::Cos(RadX);
        CosY = ::Core::Cos(RadY);
        CosZ = ::Core::Cos(RadZ);

        m_A[A11] =  CosY * CosZ;
        m_A[A21] =  SinX * SinY * CosZ - CosX * SinZ;
        m_A[A31] =  CosX * SinY * CosZ + SinX * SinZ;

        m_A[A12] =  CosY * SinZ;
        m_A[A22] =  SinX * SinY * SinZ + CosX * CosZ;
        m_A[A32] =  CosX * SinY * SinZ - SinX * CosZ;

        m_A[A13] = -SinY;
        m_A[A23] =  SinX * CosY;
        m_A[A33] =  CosX * CosY;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotation(float _AxisX, float _AxisY, float _AxisZ, float _Angle)
    {
        static const auto s_Epsilon = static_cast<X>(1E-3);

        float Rad;
        float Cosinus;
        float Sinus;
        float ComplCosinus;
        float SquareNorm;
        float ReciprocalSquareNorm;

        SquareNorm = ::Core::Square(_AxisX) + ::Core::Square(_AxisY) + ::Core::Square(_AxisZ);

        assert(SquareNorm >= s_Epsilon);

        if (::Core::Abs(SquareNorm - static_cast<X>(1)) > s_Epsilon)
        {
            ReciprocalSquareNorm = static_cast<X>(1) / ::Core::SquareRoot(SquareNorm);

            _AxisX *= ReciprocalSquareNorm;
            _AxisY *= ReciprocalSquareNorm;
            _AxisZ *= ReciprocalSquareNorm;
        }

        Rad          = ::Core::DegreesToRadians(_Angle);
        Cosinus      = ::Core::Cos(Rad);
        Sinus        = ::Core::Sin(Rad);
        ComplCosinus = static_cast<X>(1) - Cosinus;

        m_A[A11] = ComplCosinus * ::Core::Square(_AxisX) + Cosinus;
        m_A[A12] = ComplCosinus * _AxisX * _AxisY - Sinus * _AxisZ;
        m_A[A13] = ComplCosinus * _AxisX * _AxisZ + Sinus * _AxisY;
        m_A[A21] = ComplCosinus * _AxisX * _AxisY + Sinus * _AxisZ;
        m_A[A22] = ComplCosinus * ::Core::Square(_AxisY) + Cosinus;
        m_A[A23] = ComplCosinus * _AxisY * _AxisZ - Sinus * _AxisX;
        m_A[A31] = ComplCosinus * _AxisX * _AxisZ - Sinus * _AxisY;
        m_A[A32] = ComplCosinus * _AxisY * _AxisZ + Sinus * _AxisX;
        m_A[A33] = ComplCosinus * ::Core::Square(_AxisZ) + Cosinus;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotation(const CLine3& _rAxis, float _Angle)
    {
        return SetRotation(_rAxis[0], _rAxis[1], _rAxis[2], _Angle);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotation(const CLine3& _rVectorX, const CLine3& _rVectorY, const CLine3& _rVectorZ)
    {
        m_A[A11] = _rVectorX[0]; 
        m_A[A12] = _rVectorX[1];
        m_A[A13] = _rVectorX[2]; 

        m_A[A21] = _rVectorY[0]; 
        m_A[A22] = _rVectorY[1]; 
        m_A[A23] = _rVectorY[2]; 

        m_A[A31] = _rVectorZ[0]; 
        m_A[A32] = _rVectorZ[1]; 
        m_A[A33] = _rVectorZ[2]; 

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetRotation(const CMatrix3x3<X>& _rMatrix)
    {
        m_A[A11] = _rMatrix.m_A[A11]; 
        m_A[A12] = _rMatrix.m_A[A12]; 
        m_A[A13] = _rMatrix.m_A[A13]; 

        m_A[A21] = _rMatrix.m_A[A21];
        m_A[A22] = _rMatrix.m_A[A22];
        m_A[A23] = _rMatrix.m_A[A23];

        m_A[A31] = _rMatrix.m_A[A31];
        m_A[A32] = _rMatrix.m_A[A32];
        m_A[A33] = _rMatrix.m_A[A33];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix3x3<T> CMatrix4x4<T>::GetRotation() const
    {
        return CMatrix3x3<X>(m_A[A11], m_A[A12], m_A[A13], m_A[A21], m_A[A22], m_A[A23], m_A[A31], m_A[A32], m_A[A33]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline void CMatrix4x4<T>::GetEulerAngles(float& _rAngleX, float& _rAngleY, float& _rAngleZ) const
    {
        float RadianX;
        float RadianY;
        float RadianZ;

        if (::Core::Abs(m_A[A13]) < static_cast<X>(1))
        {
            RadianX = ::Core::ArcTan(m_A[A23], m_A[A33]);
            RadianY = ::Core::ArcSin(-m_A[A13]);
            RadianZ = ::Core::ArcTan(m_A[A12], m_A[A11]);
        }
        else
        {
            RadianX = static_cast<X>(0);
            RadianY = m_A[A13] >= static_cast<X>(1) ? -SConstants<X>::s_HalfPi : SConstants<X>::s_HalfPi;
            RadianZ = ::Core::ArcTan(-m_A[A32], m_A[A22]);
        }

        _rAngleX = ::Core::RadiansToDegrees(RadianX);
        _rAngleY = ::Core::RadiansToDegrees(RadianY);
        _rAngleZ = ::Core::RadiansToDegrees(RadianZ);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CLine3 CMatrix4x4<T>::GetEulerAngles() const
    {
        float AngleX;
        float AngleY;
        float AngleZ;

        GetEulerAngles(AngleX, AngleY, AngleZ);

        return CLine3(AngleX, AngleY, AngleZ);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetPerspective(X _Width, X _Height, X _Near, X _Far)
    {
        m_A[A11] = X(2) * _Near / _Width; m_A[A12] = X(0)                  ; m_A[A13] = X(0)                         ; m_A[A14] = X( 0);
        m_A[A21] = X(0)                 ; m_A[A22] = X(2) * _Near / _Height; m_A[A23] = X(0)                         ; m_A[A24] = X( 0);
        m_A[A31] = X(0)                 ; m_A[A32] = X(0)                  ; m_A[A33] = _Far / (_Near - _Far)        ; m_A[A34] = X(-1);
        m_A[A41] = X(0)                 ; m_A[A42] = X(0)                  ; m_A[A43] = _Near * _Far / (_Near - _Far); m_A[A44] = X( 0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetPerspective(X _Left, X _Right, X _Bottom, X _Top, X _Near, X _Far)
    {
        m_A[A11] = X(2) * _Near / (_Right - _Left)     ; m_A[A12] = X(0)                               ; m_A[A13] = X(0)                         ; m_A[A14] = X( 0);
        m_A[A21] = X(0)                                ; m_A[A22] = X(2) * _Near / (_Top - _Bottom)    ; m_A[A23] = X(0)                         ; m_A[A24] = X( 0);
        m_A[A31] = (_Left + _Right ) / (_Right - _Left); m_A[A32] = (_Top + _Bottom) / (_Top - _Bottom); m_A[A33] = _Far / (_Near - _Far)        ; m_A[A34] = X(-1);
        m_A[A41] = X(0)                                ; m_A[A42] = X(0)                               ; m_A[A43] = _Near * _Far / (_Near - _Far); m_A[A44] = X( 0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetFieldOfView(X _FOVY, X _Aspect, X _Near, X _Far)
    {
        X Radian;
        X ScaleX;
        X ScaleY;

        Radian = ::Core::DegreesToRadians(_FOVY) / 2.0f;
        ScaleY = ::Core::Cos(Radian) / ::Core::Sin(Radian);
        ScaleX = ScaleY / _Aspect;

        m_A[A11] = ScaleX; m_A[A12] = X(0)  ; m_A[A13] = X(0)                         ; m_A[A14] = X( 0); 
        m_A[A21] = X(0)  ; m_A[A22] = ScaleY; m_A[A23] = X(0)                         ; m_A[A24] = X( 0);
        m_A[A31] = X(0)  ; m_A[A32] = X(0)  ; m_A[A33] = _Far / (_Near - _Far)        ; m_A[A34] = X(-1); 
        m_A[A41] = X(0)  ; m_A[A42] = X(0)  ; m_A[A43] = _Near * _Far / (_Near - _Far); m_A[A44] = X( 0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetOrthographic(X _Width, X _Height, X _Near, X _Far)
    {
        m_A[A11] = X(2) / _Width; m_A[A12] = X(0)          ; m_A[A13] = X(0)                  ; m_A[A14] = X(0);
        m_A[A21] = X(0)         ; m_A[A22] = X(2) / _Height; m_A[A23] = X(0)                  ; m_A[A24] = X(0);
        m_A[A31] = X(0)         ; m_A[A32] = X(0)          ; m_A[A33] = X(1) / (_Near - _Far) ; m_A[A34] = X(0);
        m_A[A41] = X(0)         ; m_A[A42] = X(0)          ; m_A[A43] = _Near / (_Near - _Far); m_A[A44] = X(1);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix4x4<T>::CThis& CMatrix4x4<T>::SetOrthographic(X _Left, X _Right, X _Bottom, X _Top, X _Near, X _Far)
    {
        m_A[A11] = X(2) / (_Right - _Left)            ; m_A[A12] = X(0)                               ; m_A[A13] = X(0)                  ; m_A[A14] = X(0);
        m_A[A21] = X(0)                               ; m_A[A22] = X(2) / (_Top - _Bottom)            ; m_A[A23] = X(0)                  ; m_A[A24] = X(0);
        m_A[A31] = X(0)                               ; m_A[A32] = X(0)                               ; m_A[A33] = X(1) / (_Near - _Far) ; m_A[A34] = X(0);
        m_A[A41] = (_Left + _Right) / (_Left - _Right); m_A[A42] = (_Top + _Bottom) / (_Bottom - _Top); m_A[A43] = _Near / (_Near - _Far); m_A[A44] = X(1);

        return *this;
    }
} // namespace Core
