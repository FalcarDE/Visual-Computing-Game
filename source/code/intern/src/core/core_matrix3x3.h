
////////////////////////////////////////////////////////////////////////////////
/// \file    core_matrix3x3.h
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
    class CVector2;
    template <typename T>
    class CVector3;
} // namespace Core

namespace Core
{
    template <typename T>
    class CMatrix3x3
    {
        public:

            static const CMatrix3x3<T> s_Zero;
            static const CMatrix3x3<T> s_Identity;

        public:

            using CThis     = CMatrix3x3<T>;
            using CLine2    = CVector2<T>;
            using CLine3    = CVector3<T>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;

        public:

            static constexpr size_t s_NumberOfRows       = 3;
            static constexpr size_t s_NumberOfColumns    = 3;
            static constexpr size_t s_NumberOfComponents = s_NumberOfRows * s_NumberOfColumns;

        public:

            enum EUninitialized  
            { 
                Uninitialized,
            };

        public:

            enum EIndices
            {
                A11, A12, A13,
                A21, A22, A23,
                A31, A32, A33,
            };

        public:

            inline CMatrix3x3();
            inline CMatrix3x3(const CThis& _rMatrix);		
            inline explicit CMatrix3x3(EUninitialized);
            inline explicit CMatrix3x3(XConstPtr _pCoefficients);
            inline explicit CMatrix3x3(const CLine3* _pRows);
            inline CMatrix3x3(const CLine3& _rRow0, const CLine3& _rRow1, const CLine3& _rRow2);
            inline CMatrix3x3(X _11, X _12, X _13, X _21, X _22, X _23, X _31, X _32, X _33);

        public:

            inline CThis& operator = (const CThis& _rMatrix);

        public:

            inline CLine3& operator [] (size_t _Index);
            inline const CLine3& operator [] (size_t _Index) const;

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

            inline CLine2 operator * (const CLine2& _rVector) const;
            inline CLine3 operator * (const CLine3& _rVector) const;

            inline CThis operator - () const;

        public:

            inline bool operator == (const CThis& _rMatrix) const;
            inline bool operator != (const CThis& _rMatrix) const;

        public:

            inline CThis& Set(const CThis& _rMatrix);
            inline CThis& Set(XConstPtr _pCoefficients);
            inline CThis& Set(const CLine3* _pRows);
            inline CThis& Set(const CLine3& _rRow0, const CLine3& _rRow1, const CLine3& _rRow2);
            inline CThis& Set(X _11, X _12, X _13, X _21, X _22, X _23, X _31, X _32, X _33);

            inline CThis& SetZero();
            inline CThis& SetIdentity();

            inline CThis& SetRow(size_t _Index, X _A0, X _A1, X _A2);
            inline CThis& SetRow(size_t _Index, const CLine3& _rVector);
            inline CThis& SetRow(size_t _Index, const CLine2& _rVector, X _A2 = 1);

            inline CLine3& GetRow(size_t _Index);
            inline const CLine3& GetRow(size_t _Index) const;

            inline CThis& SetColumn(size_t _Index, X _A0, X _A1, X _A2);
            inline CThis& SetColumn(size_t _Index, const CLine3& _rVector);
            inline CThis& SetColumn(size_t _Index, const CLine2& _rVector, X _A2 = 1);

            inline CLine3 GetColumn(size_t _Index) const;

        public:

            inline CThis& Transpose();
            inline CThis GetTransposed() const;

            inline CThis& Invert();
            inline CThis GetInverted() const;

        public:

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
            inline CThis& SetRotation(const CThis& _rMatrix);

            inline const CThis& GetRotation() const;

            inline void GetEulerAngles(float& _rAngleX, float& _rAngleY, float& _rAngleZ) const;
            inline CLine3 GetEulerAngles() const;

        private:

            X m_A[s_NumberOfComponents];
    };
} // namespace Core

#include "core_vector3.h"
#include "core_vector4.h"

namespace Core
{
    template <typename T>
    const CMatrix3x3<T> CMatrix3x3<T>::s_Zero     = CMatrix3x3(T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0), T(0));
    template <typename T>
    const CMatrix3x3<T> CMatrix3x3<T>::s_Identity = CMatrix3x3(T(1), T(0), T(0), T(0), T(1), T(0), T(0), T(0), T(1));
} // namespace Core

namespace Core
{
    template <typename T>
    inline CMatrix3x3<T>::CMatrix3x3()
    {
        SetIdentity();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix3x3<T>::CMatrix3x3(const CThis& _rMatrix)
    {
        Set(_rMatrix);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix3x3<T>::CMatrix3x3(EUninitialized)
    {
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix3x3<T>::CMatrix3x3(XConstPtr _pCoefficients)
    {
        Set(_pCoefficients);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix3x3<T>::CMatrix3x3(const CLine3* _pRows)
    {
        Set(_pRows);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix3x3<T>::CMatrix3x3(const CLine3& _rRow0, const CLine3& _rRow1, const CLine3& _rRow2)
    {
        Set(_rRow0, _rRow1, _rRow2);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix3x3<T>::CMatrix3x3(X _11, X _12, X _13, X _21, X _22, X _23, X _31, X _32, X _33)
    {
        Set(_11, _12, _13, _21, _22, _23, _31, _32, _33);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::operator = (const CThis& _rMatrix)
    {
        Set(_rMatrix);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CLine3& CMatrix3x3<T>::operator[] (size_t _Index)
    {
        return GetRow(_Index);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CMatrix3x3<T>::CLine3& CMatrix3x3<T>::operator[] (size_t _Index) const
    {
        return GetRow(_Index);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::operator += (const CThis& _rMatrix)
    {
        m_A[A11] += _rMatrix.m_A[A11]; m_A[A12] += _rMatrix.m_A[A12]; m_A[A13] += _rMatrix.m_A[A13];
        m_A[A21] += _rMatrix.m_A[A21]; m_A[A22] += _rMatrix.m_A[A22]; m_A[A23] += _rMatrix.m_A[A23];
        m_A[A31] += _rMatrix.m_A[A31]; m_A[A32] += _rMatrix.m_A[A32]; m_A[A33] += _rMatrix.m_A[A33];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::operator -= (const CThis& _rMatrix)
    {
        m_A[A11] -= _rMatrix.m_A[A11]; m_A[A12] -= _rMatrix.m_A[A12]; m_A[A13] -= _rMatrix.m_A[A13];
        m_A[A21] -= _rMatrix.m_A[A21]; m_A[A22] -= _rMatrix.m_A[A22]; m_A[A23] -= _rMatrix.m_A[A23];
        m_A[A31] -= _rMatrix.m_A[A31]; m_A[A32] -= _rMatrix.m_A[A32]; m_A[A33] -= _rMatrix.m_A[A33];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::operator *= (const CThis& _rMatrix)
    {
        return Set((*this) * _rMatrix);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis CMatrix3x3<T>::operator + (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] + _rMatrix.m_A[A11]; A[A12] = m_A[A12] + _rMatrix.m_A[A12]; A[A13] = m_A[A13] + _rMatrix.m_A[A13];
        A[A21] = m_A[A21] + _rMatrix.m_A[A21]; A[A22] = m_A[A22] + _rMatrix.m_A[A22]; A[A23] = m_A[A23] + _rMatrix.m_A[A23];
        A[A31] = m_A[A31] + _rMatrix.m_A[A31]; A[A32] = m_A[A32] + _rMatrix.m_A[A32]; A[A33] = m_A[A33] + _rMatrix.m_A[A33];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis CMatrix3x3<T>::operator - (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] - _rMatrix.m_A[A11]; A[A12] = m_A[A12] - _rMatrix.m_A[A12]; A[A13] = m_A[A13] - _rMatrix.m_A[A13];
        A[A21] = m_A[A21] - _rMatrix.m_A[A21]; A[A22] = m_A[A22] - _rMatrix.m_A[A22]; A[A23] = m_A[A23] - _rMatrix.m_A[A23];
        A[A31] = m_A[A31] - _rMatrix.m_A[A31]; A[A32] = m_A[A32] - _rMatrix.m_A[A32]; A[A33] = m_A[A33] - _rMatrix.m_A[A33];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis CMatrix3x3<T>::operator * (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] * _rMatrix.m_A[A11] + m_A[A12] * _rMatrix.m_A[A21] + m_A[A13] * _rMatrix.m_A[A31];
        A[A12] = m_A[A11] * _rMatrix.m_A[A12] + m_A[A12] * _rMatrix.m_A[A22] + m_A[A13] * _rMatrix.m_A[A32];
        A[A13] = m_A[A11] * _rMatrix.m_A[A13] + m_A[A12] * _rMatrix.m_A[A23] + m_A[A13] * _rMatrix.m_A[A33];
        A[A21] = m_A[A21] * _rMatrix.m_A[A11] + m_A[A22] * _rMatrix.m_A[A21] + m_A[A23] * _rMatrix.m_A[A31];
        A[A22] = m_A[A21] * _rMatrix.m_A[A12] + m_A[A22] * _rMatrix.m_A[A22] + m_A[A23] * _rMatrix.m_A[A32];
        A[A23] = m_A[A21] * _rMatrix.m_A[A13] + m_A[A22] * _rMatrix.m_A[A23] + m_A[A23] * _rMatrix.m_A[A33];
        A[A31] = m_A[A31] * _rMatrix.m_A[A11] + m_A[A32] * _rMatrix.m_A[A21] + m_A[A33] * _rMatrix.m_A[A31];
        A[A32] = m_A[A31] * _rMatrix.m_A[A12] + m_A[A32] * _rMatrix.m_A[A22] + m_A[A33] * _rMatrix.m_A[A32];
        A[A33] = m_A[A31] * _rMatrix.m_A[A13] + m_A[A32] * _rMatrix.m_A[A23] + m_A[A33] * _rMatrix.m_A[A33];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T> 
    inline typename CMatrix3x3<T>::CLine2 CMatrix3x3<T>::operator * (const CLine2& _rVector) const
    {
        X V[CLine2::s_NumberOfComponents];

        V[0] = m_A[A11] * _rVector[0] + m_A[A12] * _rVector[1] + m_A[A13];
        V[1] = m_A[A21] * _rVector[0] + m_A[A22] * _rVector[1] + m_A[A23];

        return CLine2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CLine3 CMatrix3x3<T>::operator * (const CLine3& _rVector) const
    {
        X V[CLine3::s_NumberOfComponents];

        V[0] = m_A[A11] * _rVector[0] + m_A[A12] * _rVector[1] + m_A[A13] * _rVector[2];
        V[1] = m_A[A21] * _rVector[0] + m_A[A22] * _rVector[1] + m_A[A23] * _rVector[2];
        V[2] = m_A[A31] * _rVector[0] + m_A[A32] * _rVector[1] + m_A[A33] * _rVector[2];

        return CLine3(V[0], V[1], V[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CMatrix3x3<T>::operator == (const CThis& _rMatrix) const
    {
        return ((*this)[0] == _rMatrix[0]) && ((*this)[1] == _rMatrix[1]) && ((*this)[2] == _rMatrix[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CMatrix3x3<T>::operator != (const CThis& _rMatrix) const
    {
        return ((*this)[0] != _rMatrix[0]) || ((*this)[1] != _rMatrix[1]) || ((*this)[2] != _rMatrix[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::Set(const CThis& _rMatrix)
    {
        m_A[A11] = _rMatrix.m_A[A11]; m_A[A12] = _rMatrix.m_A[A12]; m_A[A13] = _rMatrix.m_A[A13];
        m_A[A21] = _rMatrix.m_A[A21]; m_A[A22] = _rMatrix.m_A[A22]; m_A[A23] = _rMatrix.m_A[A23];
        m_A[A31] = _rMatrix.m_A[A31]; m_A[A32] = _rMatrix.m_A[A32]; m_A[A33] = _rMatrix.m_A[A33];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::Set(XConstPtr _pCoefficients)
    {
        assert(_pCoefficients != 0);

        m_A[A11] = _pCoefficients[A11]; m_A[A12] = _pCoefficients[A12]; m_A[A13] = _pCoefficients[A13];
        m_A[A21] = _pCoefficients[A21]; m_A[A22] = _pCoefficients[A22]; m_A[A23] = _pCoefficients[A23];
        m_A[A31] = _pCoefficients[A31]; m_A[A32] = _pCoefficients[A32]; m_A[A33] = _pCoefficients[A33];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::Set(const CLine3* _pRows)
    {
        assert(_pRows != 0);

        m_A[A11] = _pRows[0][0]; m_A[A12] = _pRows[0][1]; m_A[A13] = _pRows[0][2];
        m_A[A21] = _pRows[1][0]; m_A[A22] = _pRows[1][1]; m_A[A23] = _pRows[1][2];
        m_A[A31] = _pRows[2][0]; m_A[A32] = _pRows[2][1]; m_A[A33] = _pRows[2][2];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::Set(const CLine3& _rRow0, const CLine3& _rRow1, const CLine3& _rRow2)
    {
        m_A[A11] = _rRow0[0]; m_A[A12] = _rRow0[1]; m_A[A13] = _rRow0[2];
        m_A[A21] = _rRow1[0]; m_A[A22] = _rRow1[1]; m_A[A23] = _rRow1[2];
        m_A[A31] = _rRow2[0]; m_A[A32] = _rRow2[1]; m_A[A33] = _rRow2[2];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::Set(X _11, X _12, X _13, X _21, X _22, X _23, X _31, X _32, X _33)
    {
        m_A[A11] = _11; m_A[A12] = _12; m_A[A13] = _13;
        m_A[A21] = _21; m_A[A22] = _22; m_A[A23] = _23;
        m_A[A31] = _31; m_A[A32] = _32; m_A[A33] = _33;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRow(size_t _Index, X _A0, X _A1, X _A2)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_A0, _A1, _A2);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRow(size_t _Index, const CLine3& _rVector)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_rVector);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRow(size_t _Index, const CLine2& _rVector, X _A2)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_rVector[0], _rVector[1], _A2);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CLine3& CMatrix3x3<T>::GetRow(size_t _Index)
    {
        assert(_Index < s_NumberOfRows);

        return *reinterpret_cast<CLine3*>(&m_A[_Index * s_NumberOfColumns]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CMatrix3x3<T>::CLine3& CMatrix3x3<T>::GetRow(size_t _Index) const
    {
        assert(_Index < s_NumberOfRows);

        return *reinterpret_cast<const CLine3*>(&m_A[_Index * s_NumberOfColumns]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetColumn(size_t _Index, X _A0, X _A1, X _A2)
    {
        assert(_Index < s_NumberOfColumns);

        m_A[0 + _Index] = _A0;
        m_A[3 + _Index] = _A1;
        m_A[6 + _Index] = _A2;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetColumn(size_t _Index, const CLine3& _rVector)
    {
        return SetColumn(_Index, _rVector[0], _rVector[1], _rVector[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetColumn(size_t _Index, const CLine2& _rVector, X _A2)
    {
        return SetColumn(_Index, _rVector[0], _rVector[1], _A2);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CLine3 CMatrix3x3<T>::GetColumn(size_t _Index) const
    {
        X V[CLine3::s_NumberOfComponents];

        assert(_Index < s_NumberOfColumns);

        V[0] = m_A[0 + _Index];
        V[1] = m_A[3 + _Index];
        V[2] = m_A[6 + _Index];

        return CLine3(V[0], V[1], V[2]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetZero()
    {
        return Set(s_Zero);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetIdentity()
    {
        return Set(s_Identity);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::Transpose()
    {
        Swap(m_A[A21], m_A[A12]);
        Swap(m_A[A31], m_A[A13]);
        Swap(m_A[A32], m_A[A23]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis CMatrix3x3<T>::GetTransposed() const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11]; A[A12] = m_A[A21]; A[A13] = m_A[A31];
        A[A21] = m_A[A12]; A[A22] = m_A[A22]; A[A23] = m_A[A32];
        A[A31] = m_A[A13]; A[A32] = m_A[A23]; A[A33] = m_A[A33];

        return CThis(A);
    }

    // ------------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::Invert()
    {
        X Determinant;
        X ReciprocalDeterminant;
        X A[s_NumberOfComponents];

        A[A11] = m_A[A22] * m_A[A33] - m_A[A23] * m_A[A32];
        A[A12] = m_A[A13] * m_A[A32] - m_A[A12] * m_A[A33];
        A[A13] = m_A[A12] * m_A[A23] - m_A[A13] * m_A[A22];
        A[A21] = m_A[A23] * m_A[A31] - m_A[A21] * m_A[A33];
        A[A22] = m_A[A11] * m_A[A33] - m_A[A13] * m_A[A31];
        A[A23] = m_A[A13] * m_A[A21] - m_A[A11] * m_A[A23];
        A[A31] = m_A[A21] * m_A[A32] - m_A[A22] * m_A[A31];
        A[A32] = m_A[A12] * m_A[A31] - m_A[A11] * m_A[A32];
        A[A33] = m_A[A11] * m_A[A22] - m_A[A12] * m_A[A21];

        Determinant = m_A[A11] * A[A11] + m_A[A12] * A[A21] + m_A[A13] * A[A31];

        assert(!::Core::IsEqual(Determinant, static_cast<X>(0), SConstants<X>::s_Epsilon));

        ReciprocalDeterminant = static_cast<X>(1) / Determinant;

        m_A[A11] = A[A11] * ReciprocalDeterminant; m_A[A12] = A[A12] * ReciprocalDeterminant; m_A[A13] = A[A13] * ReciprocalDeterminant;
        m_A[A21] = A[A21] * ReciprocalDeterminant; m_A[A22] = A[A22] * ReciprocalDeterminant; m_A[A23] = A[A23] * ReciprocalDeterminant;
        m_A[A31] = A[A31] * ReciprocalDeterminant; m_A[A32] = A[A32] * ReciprocalDeterminant; m_A[A33] = A[A33] * ReciprocalDeterminant;

        return *this;
    }

    // ------------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis CMatrix3x3<T>::GetInverted() const
    {
        X Determinant;
        X ReciprocalDeterminant;
        X A[s_NumberOfComponents];

        A[A11] = m_A[A22] * m_A[A33] - m_A[A23] * m_A[A32];
        A[A12] = m_A[A13] * m_A[A32] - m_A[A12] * m_A[A33];
        A[A13] = m_A[A12] * m_A[A23] - m_A[A13] * m_A[A22];
        A[A21] = m_A[A23] * m_A[A31] - m_A[A21] * m_A[A33];
        A[A22] = m_A[A11] * m_A[A33] - m_A[A13] * m_A[A31];
        A[A23] = m_A[A13] * m_A[A21] - m_A[A11] * m_A[A23];
        A[A31] = m_A[A21] * m_A[A32] - m_A[A22] * m_A[A31];
        A[A32] = m_A[A12] * m_A[A31] - m_A[A11] * m_A[A32];
        A[A33] = m_A[A11] * m_A[A22] - m_A[A12] * m_A[A21];

        Determinant = m_A[A11] * A[A11] + m_A[A12] * A[A21] + m_A[A13] * A[A31];

        assert(!::Core::IsEqual(Determinant, static_cast<X>(0), SConstants<X>::s_Epsilon));

        ReciprocalDeterminant = static_cast<X>(1) / Determinant;

        A[A11] *= ReciprocalDeterminant; A[A12] *= ReciprocalDeterminant; A[A13] *= ReciprocalDeterminant;
        A[A21] *= ReciprocalDeterminant; A[A22] *= ReciprocalDeterminant; A[A23] *= ReciprocalDeterminant;
        A[A31] *= ReciprocalDeterminant; A[A32] *= ReciprocalDeterminant; A[A33] *= ReciprocalDeterminant;

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetScale(X _Scale)
    {
        m_A[A11] = _Scale;
        m_A[A22] = _Scale;
        m_A[A33] = _Scale;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetScale(X _ScaleX, X _ScaleY, X _ScaleZ)
    {
        m_A[A11] = _ScaleX;
        m_A[A22] = _ScaleY;
        m_A[A33] = _ScaleZ;

        return *this;
    }

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetScale(const CLine3& _rScale)
    {
        return SetScale(_rScale[0], _rScale[1], _rScale[2]);
    }

    // -----------------------------------------------------------------------------

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CLine3 CMatrix3x3<T>::GetScale() const
    {
        return CLine3(m_A[A11], m_A[A22], m_A[A33]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotationX(float _Angle)
    {
        float Rad     = ::Core::DegreesToRadians(_Angle);
        float Cosinus = ::Core::Cos(Rad);
        float Sinus   = ::Core::Sin(Rad);

        m_A[A11]                                  =  static_cast<X>(1);
        m_A[A12] = m_A[A21] = m_A[A13] = m_A[A31] =  static_cast<X>(0);
        m_A[A22] = m_A[A33]                       =  Cosinus;
        m_A[A23]                                  =  Sinus;
        m_A[A32]                                  = -Sinus;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotationY(float _Angle)
    {
        float Rad     = ::Core::DegreesToRadians(_Angle);
        float Cosinus = ::Core::Cos(Rad);
        float Sinus   = ::Core::Sin(Rad);

        m_A[A22]                                  =  static_cast<X>(1);
        m_A[A12] = m_A[A21] = m_A[A23] = m_A[A32] =  static_cast<X>(0);
        m_A[A11] = m_A[A33]                       =  Cosinus;
        m_A[A31]                                  =  Sinus;
        m_A[A13]                                  = -Sinus;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotationZ(float _Angle)
    {
        float Rad     = ::Core::DegreesToRadians(_Angle);
        float Cosinus = ::Core::Cos(Rad);
        float Sinus   = ::Core::Sin(Rad);

        m_A[A33]                                  =  static_cast<X>(1);
        m_A[A13] = m_A[A31] = m_A[A23] = m_A[A32] =  static_cast<X>(0);
        m_A[A11] = m_A[A22]                       =  Cosinus;
        m_A[A12]                                  =  Sinus;
        m_A[A21]                                  = -Sinus;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotation(float _AngleX, float _AngleY, float _AngleZ)
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
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotation(float _AxisX, float _AxisY, float _AxisZ, float _Angle)
    {
        static constexpr auto s_Epsilon = static_cast<X>(1E-3);

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
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotation(const CLine3& _rAxis, float _Angle)
    {
        return SetRotation(_rAxis[0], _rAxis[1], _rAxis[2], _Angle);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotation(const CLine3& _rVectorX, const CLine3& _rVectorY, const CLine3& _rVectorZ)
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
    inline typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::SetRotation(const CThis& _rMatrix)
    {
        return Set(_rMatrix);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CMatrix3x3<T>::CThis& CMatrix3x3<T>::GetRotation() const
    {
        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline void CMatrix3x3<T>::GetEulerAngles(float& _rAngleX, float& _rAngleY, float& _rAngleZ) const
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
    inline typename CMatrix3x3<T>::CLine3 CMatrix3x3<T>::GetEulerAngles() const
    {
        float AngleX;
        float AngleY;
        float AngleZ;

        GetEulerAngles(AngleX, AngleY, AngleZ);

        return CLine3(AngleX, AngleY, AngleZ);
    }
} // namespace Core
