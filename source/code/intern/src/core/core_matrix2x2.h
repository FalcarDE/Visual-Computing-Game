
////////////////////////////////////////////////////////////////////////////////
/// \file    core_matrix2x2.h
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
} // namespace Core

namespace Core
{
    template <typename T>
    class CMatrix2x2
    {
        public:

            static const CMatrix2x2<T> s_Zero;
            static const CMatrix2x2<T> s_Identity;

        public:

            using CThis     = CMatrix2x2<T>;
            using CLine2    = CVector2<T>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;

        public:

            static constexpr size_t s_NumberOfRows       = 2;
            static constexpr size_t s_NumberOfColumns    = 2;
            static constexpr size_t s_NumberOfComponents = s_NumberOfRows * s_NumberOfColumns;

        public:

            enum EUninitialized  
            { 
                Uninitialized,
            };

        public:

            enum EIndices
            {
                A11, A12,
                A21, A22,
            };

        public:

            inline CMatrix2x2();
            inline CMatrix2x2(const CThis& _rMatrix);		
            inline explicit CMatrix2x2(EUninitialized);
            inline explicit CMatrix2x2(XConstPtr _pCoefficients);
            inline explicit CMatrix2x2(const CLine2* _pRows);
            inline CMatrix2x2(const CLine2& _rRow0, const CLine2& _rRow1);
            inline CMatrix2x2(X _11, X _12, X _21, X _22);

        public:

            inline CThis& operator = (const CThis& _rMatrix);

        public:

            inline CLine2& operator [] (size_t _Index);
            inline const CLine2& operator [] (size_t _Index) const;

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

            inline CThis operator - () const;

        public:

            inline bool operator == (const CThis& _rMatrix) const;
            inline bool operator != (const CThis& _rMatrix) const;

        public:

            inline CThis& Set(const CThis& _rMatrix);
            inline CThis& Set(XConstPtr _pCoefficients);
            inline CThis& Set(const CLine2* _pRows);
            inline CThis& Set(const CLine2& _rRow0, const CLine2& _rRow1);
            inline CThis& Set(X _11, X _12, X _21, X _22);

            inline CThis& SetZero();
            inline CThis& SetIdentity();

            inline CThis& SetRow(size_t _Index, X _A0, X _A1);
            inline CThis& SetRow(size_t _Index, const CLine2& _rVector);

            inline CLine2& GetRow(size_t _Index);
            inline const CLine2& GetRow(size_t _Index) const;

            inline CThis& SetColumn(size_t _Index, X _A0, X _A1);
            inline CThis& SetColumn(size_t _Index, const CLine2& _rVector);

            inline CLine2 GetColumn(size_t _Index) const;

        public:

            inline CThis& Transpose();
            inline CThis GetTransposed() const;

            inline CThis& Invert();
            inline CThis GetInverted() const;

        public:

            inline CThis& SetScale(X _Scale);
            inline CThis& SetScale(X _ScaleX, X _ScaleY);
            inline CThis& SetScale(const CLine2& _rScale);

            inline CLine2 GetScale() const;

            inline CThis& SetRotation(float _Angle);

        private:

            X m_A[s_NumberOfComponents];
    };
} // namespace Core

#include "core_vector2.h"

namespace Core
{
    template <typename T>
    const CMatrix2x2<T> CMatrix2x2<T>::s_Zero     = CMatrix2x2(T(0), T(0), T(0), T(0));
    template <typename T>
    const CMatrix2x2<T> CMatrix2x2<T>::s_Identity = CMatrix2x2(T(1), T(0), T(0), T(1));
} // namespace Core

namespace Core
{
    template <typename T>
    inline CMatrix2x2<T>::CMatrix2x2()
    {
        SetIdentity();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix2x2<T>::CMatrix2x2(const CThis& _rMatrix)
    {
        Set(_rMatrix);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix2x2<T>::CMatrix2x2(EUninitialized)
    {
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix2x2<T>::CMatrix2x2(XConstPtr _pCoefficients)
    {
        Set(_pCoefficients);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix2x2<T>::CMatrix2x2(const CLine2* _pRows)
    {
        Set(_pRows);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix2x2<T>::CMatrix2x2(const CLine2& _rRow0, const CLine2& _rRow1)
    {
        Set(_rRow0, _rRow1);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CMatrix2x2<T>::CMatrix2x2(X _11, X _12, X _21, X _22)
    {
        Set(_11, _12, _21, _22);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::operator = (const CThis& _rMatrix)
    {
        Set(_rMatrix);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CLine2& CMatrix2x2<T>::operator[] (size_t _Index)
    {
        return GetRow(_Index);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CMatrix2x2<T>::CLine2& CMatrix2x2<T>::operator[] (size_t _Index) const
    {
        return GetRow(_Index);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::operator += (const CThis& _rMatrix)
    {
        m_A[A11] += _rMatrix.m_A[A11]; m_A[A12] += _rMatrix.m_A[A12];
        m_A[A21] += _rMatrix.m_A[A21]; m_A[A22] += _rMatrix.m_A[A22];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::operator -= (const CThis& _rMatrix)
    {
        m_A[A11] -= _rMatrix.m_A[A11]; m_A[A12] -= _rMatrix.m_A[A12];
        m_A[A21] -= _rMatrix.m_A[A21]; m_A[A22] -= _rMatrix.m_A[A22];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::operator *= (const CThis& _rMatrix)
    {
        return Set((*this) * _rMatrix);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis CMatrix2x2<T>::operator + (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] + _rMatrix.m_A[A11]; A[A12] = m_A[A12] + _rMatrix.m_A[A12];
        A[A21] = m_A[A21] + _rMatrix.m_A[A21]; A[A22] = m_A[A22] + _rMatrix.m_A[A22];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis CMatrix2x2<T>::operator - (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] - _rMatrix.m_A[A11]; A[A12] = m_A[A12] - _rMatrix.m_A[A12];
        A[A21] = m_A[A21] - _rMatrix.m_A[A21]; A[A22] = m_A[A22] - _rMatrix.m_A[A22];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis CMatrix2x2<T>::operator * (const CThis& _rMatrix) const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11] * _rMatrix.m_A[A11] + m_A[A12] * _rMatrix.m_A[A21];
        A[A12] = m_A[A11] * _rMatrix.m_A[A12] + m_A[A12] * _rMatrix.m_A[A22];
        A[A21] = m_A[A21] * _rMatrix.m_A[A11] + m_A[A22] * _rMatrix.m_A[A21];
        A[A22] = m_A[A21] * _rMatrix.m_A[A12] + m_A[A22] * _rMatrix.m_A[A22];

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CLine2 CMatrix2x2<T>::operator * (const CLine2& _rVector) const
    {
        X V[CLine2::s_NumberOfComponents];

        V[0] = m_A[A11] * _rVector[0] + m_A[A12] * _rVector[1];
        V[1] = m_A[A21] * _rVector[0] + m_A[A22] * _rVector[1];

        return CLine2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CMatrix2x2<T>::operator == (const CThis& _rMatrix) const
    {
        return ((*this)[0] == _rMatrix[0]) && ((*this)[1] == _rMatrix[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CMatrix2x2<T>::operator != (const CThis& _rMatrix) const
    {
        return ((*this)[0] != _rMatrix[0]) || ((*this)[1] != _rMatrix[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::Set(const CThis& _rMatrix)
    {
        m_A[A11] = _rMatrix.m_A[A11]; m_A[A12] = _rMatrix.m_A[A12];
        m_A[A21] = _rMatrix.m_A[A21]; m_A[A22] = _rMatrix.m_A[A22];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::Set(XConstPtr _pCoefficients)
    {
        assert(_pCoefficients != 0);

        m_A[A11] = _pCoefficients[A11]; m_A[A12] = _pCoefficients[A12];
        m_A[A21] = _pCoefficients[A21]; m_A[A22] = _pCoefficients[A22];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::Set(const CLine2* _pRows)
    {
        assert(_pRows != 0);

        m_A[A11] = _pRows[0][0]; m_A[A12] = _pRows[0][1];
        m_A[A21] = _pRows[1][0]; m_A[A22] = _pRows[1][1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::Set(const CLine2& _rRow0, const CLine2& _rRow1)
    {
        m_A[A11] = _rRow0[0]; m_A[A12] = _rRow0[1];
        m_A[A21] = _rRow1[0]; m_A[A22] = _rRow1[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::Set(X _11, X _12, X _21, X _22)
    {
        m_A[A11] = _11; m_A[A12] = _12;
        m_A[A21] = _21; m_A[A22] = _22;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetRow(size_t _Index, X _A0, X _A1)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_A0, _A1);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetRow(size_t _Index, const CLine2& _rVector)
    {
        assert(_Index < s_NumberOfRows);

        (*this)[_Index].Set(_rVector);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CLine2& CMatrix2x2<T>::GetRow(size_t _Index)
    {
        assert(_Index < s_NumberOfRows);

        return *reinterpret_cast<CLine2*>(&m_A[_Index * s_NumberOfColumns]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CMatrix2x2<T>::CLine2& CMatrix2x2<T>::GetRow(size_t _Index) const
    {
        assert(_Index < s_NumberOfRows);

        return *reinterpret_cast<const CLine2*>(&m_A[_Index * s_NumberOfColumns]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetColumn(size_t _Index, X _A0, X _A1)
    {
        assert(_Index < s_NumberOfColumns);

        m_A[0 + _Index] = _A0;
        m_A[2 + _Index] = _A1;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetColumn(size_t _Index, const CLine2& _rVector)
    {
        return SetColumn(_Index, _rVector[0], _rVector[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CLine2 CMatrix2x2<T>::GetColumn(size_t _Index) const
    {
        X V[CLine2::s_NumberOfComponents];

        assert(_Index < s_NumberOfColumns);

        V[0] = m_A[0 + _Index];
        V[1] = m_A[2 + _Index];

        return CLine2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetZero()
    {
        return Set(s_Zero);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetIdentity()
    {
        return Set(s_Identity);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::Transpose()
    {
        Swap(m_A[A21], m_A[A12]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis CMatrix2x2<T>::GetTransposed() const
    {
        X A[s_NumberOfComponents];

        A[A11] = m_A[A11]; A[A12] = m_A[A21];
        A[A21] = m_A[A12]; A[A22] = m_A[A22];

        return CThis(A);
    }

    // ------------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::Invert()
    {
        X Determinant;
        X ReciprocalDeterminant;

        Determinant = m_A[A11] * m_A[A22] - m_A[A12] * m_A[A21];

        assert(!::Core::IsEqual(Determinant, static_cast<X>(0), SConstants<X>::s_Epsilon));

        ReciprocalDeterminant = static_cast<X>(1) / Determinant;

        Swap(m_A[A11], m_A[A22]);

        m_A[A11] *=  ReciprocalDeterminant; m_A[A12] *= -ReciprocalDeterminant;
        m_A[A21] *= -ReciprocalDeterminant; m_A[A22] *=  ReciprocalDeterminant;

        return *this;
    }

    // ------------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis CMatrix2x2<T>::GetInverted() const
    {
        X Determinant;
        X ReciprocalDeterminant;
        X A[s_NumberOfComponents];

        Determinant = m_A[A11] * m_A[A22] + m_A[A12] * m_A[A21];

        assert(!::Core::IsEqual(Determinant, static_cast<X>(0), SConstants<X>::s_Epsilon));

        ReciprocalDeterminant = static_cast<X>(1) / Determinant;

        A[A11] = m_A[A22] *   ReciprocalDeterminant ; A[A12] = m_A[A12] * (-ReciprocalDeterminant);
        A[A21] = m_A[A21] * (-ReciprocalDeterminant); A[A22] = m_A[A11] *   ReciprocalDeterminant ;

        return CThis(A);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetScale(X _Scale)
    {
        m_A[A11] = _Scale;
        m_A[A22] = _Scale;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetScale(X _ScaleX, X _ScaleY)
    {
        m_A[A11] = _ScaleX;
        m_A[A22] = _ScaleY;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CLine2 CMatrix2x2<T>::GetScale() const
    {
        return CLine2(m_A[A11], m_A[A22]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CMatrix2x2<T>::CThis& CMatrix2x2<T>::SetRotation(float _Angle)
    {
        float Rad;
        float Cosinus;
        float Sinus;

        Rad     = ::Core::DegreesToRadians(_Angle);
        Cosinus = ::Core::Cos(Rad);
        Sinus   = ::Core::Sin(Rad);

        m_A[A11] = m_A[A22] =  Cosinus;
        m_A[A12]            =  Sinus;
        m_A[A21]            = -Sinus;

        return *this;
    }
} // namespace Core
