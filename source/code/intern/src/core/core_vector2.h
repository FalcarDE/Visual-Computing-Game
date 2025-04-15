
////////////////////////////////////////////////////////////////////////////////
/// \file    core_vector2.h
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

#include <assert.h>

namespace Core
{
    template <typename T>
    class CMatrix2x2;
    template <typename T>
    class CMatrix3x3;
} // namespace Core

namespace Core
{
    template <typename T>
    class CVector2
    {
        public:

            static const CVector2<T> s_Zero;
            static const CVector2<T> s_One;
            static const CVector2<T> s_AxisX;
            static const CVector2<T> s_AxisY;

        public:

            using CThis = CVector2<T>;
            using X     = T;

        public:

            static constexpr size_t s_NumberOfComponents = 2;

        public:

            enum EUninitialized  
            { 
                Uninitialized,
            };

        public:

            inline CVector2();
            inline CVector2(const CThis& _rVector);
            inline explicit CVector2(EUninitialized);
            inline explicit CVector2(X _Value);
            inline CVector2(X _Value0, X _Value1);

        public:

            inline CThis& operator = (const CThis& _rVector);

        public:

            inline X& operator [] (size_t _Index);
            inline const X& operator [] (size_t _Index) const;

        public:

            inline CThis& operator += (const CThis& _rVector);
            inline CThis& operator -= (const CThis& _rVector);
            inline CThis& operator *= (const CThis& _rVector);
            inline CThis& operator /= (const CThis& _rVector);

            inline CThis& operator *= (X _Scalar);
            inline CThis& operator /= (X _Scalar);

            inline CThis& operator *= (const CMatrix2x2<X>& _rMatrix);
            inline CThis& operator *= (const CMatrix3x3<X>& _rMatrix);

            inline CThis operator + (const CThis& _rVector) const;
            inline CThis operator - (const CThis& _rVector) const;
            inline CThis operator * (const CThis& _rVector) const;
            inline CThis operator / (const CThis& _rVector) const;

            inline CThis operator * (X _Scalar) const;
            inline CThis operator / (X _Scalar) const;

            inline CThis operator * (const CMatrix2x2<X>& _rMatrix) const;
            inline CThis operator * (const CMatrix3x3<X>& _rMatrix) const;

            inline CThis operator - () const;

        public:

            inline bool operator == (const CThis& _rVector) const;
            inline bool operator != (const CThis& _rVector) const;
            inline bool operator <  (const CThis& _rVector) const;
            inline bool operator <= (const CThis& _rVector) const;
            inline bool operator >  (const CThis& _rVector) const;
            inline bool operator >= (const CThis& _rVector) const;

        public:

            inline CThis& Set(const CThis& _rVector);
            inline CThis& Set(X _Value);
            inline CThis& Set(X _Value0, X _Value1);

        public:

            inline CThis& Normalize();
            inline CThis& Normalize2();
            inline CThis GetNormalized() const;
            inline CThis GetNormalized2() const;

            inline bool IsNormalized() const;

            inline X GetLength() const;
            inline X GetLength2() const;

            inline X GetSquaredLength() const;
            inline X GetSquaredLength2() const;

            inline CThis& Reciprocal();
            inline CThis GetReciprocal() const;

            inline CThis& Round();
            inline CThis GetRounded() const;

            inline CThis& Clamp(const CThis& _rMin, const CThis& _rMax);
            inline CThis GetClamped(const CThis& _rMin, const CThis& _rMax) const;

            inline CThis& Saturate();
            inline CThis GetSaturated() const;

            inline CThis& Min(const CThis& _rVector);
            inline CThis GetMin(const CThis& _rVector) const;

            inline CThis& Max(const CThis& _rVector);
            inline CThis GetMax(const CThis& _rVector) const;

            inline CThis& Neg();
            inline CThis GetNeg() const;

            inline CThis& MulAdd(const CThis& _rVector1, const CThis& _rVector2);
            inline CThis GetMulAdd(const CThis& _rVector1, const CThis& _rVector2) const;

            inline CThis& MulSub(const CThis& _rVector1, const CThis& _rVector2);
            inline CThis GetMulSub(const CThis& _rVector1, const CThis& _rVector2) const;

            inline CThis& Lerp(const CThis& _rTarget, const CThis& _rWeight);
            inline CThis GetLerped(const CThis& _rTarget, const CThis& _rWeight) const;
            inline CThis& Lerp(const CThis& _rTarget, X _Weight);
            inline CThis GetLerped(const CThis& _rTarget, X _Weight) const;

            inline CThis& Splat(X _Value);
            inline CThis GetSplatted(X _Value) const;

            inline X GetDotProduct(const CThis& _rVector) const;
            inline X GetDotProduct2(const CThis& _rVector) const;

            template <size_t TIndex0, size_t TIndex1>
            inline CThis& Swizzle();
            template <size_t TIndex0, size_t TIndex1>
            inline CThis GetSwizzled() const;

            template <size_t TIndex0, size_t TIndex1>
            inline CThis& Permute(const CThis& _rVector);
            template <size_t TIndex0, size_t TIndex1>
            inline CThis GetPermuted(const CThis& _rVector) const;

            inline CThis& TestEqual(const CThis& _rVector);
            inline CThis GetTestEqual(const CThis& _rVector) const;

            inline CThis& TestNotEqual(const CThis& _rVector);
            inline CThis GetTestNotEqual(const CThis& _rVector) const;

            inline CThis& TestLesser(const CThis& _rVector);
            inline CThis GetTestLesser(const CThis& _rVector) const;

            inline CThis& TestLesserEqual(const CThis& _rVector);
            inline CThis GetTestLesserEqual(const CThis& _rVector) const;

            inline CThis& TestGreater(const CThis& _rVector);
            inline CThis GetTestGreater(const CThis& _rVector) const;

            inline CThis& TestGreaterEqual(const CThis& _rVector);
            inline CThis GetTestGreaterEqual(const CThis& _rVector) const;

        private:

            X m_V[s_NumberOfComponents];
    };
} // namespace Core

namespace Core
{
    using SChar2     = CVector2<signed char>;
    using UChar2     = CVector2<unsigned char>;
    using SShort2    = CVector2<signed short>;
    using UShort2    = CVector2<unsigned short>;
    using SInt2      = CVector2<signed int>;
    using UInt2      = CVector2<unsigned int>;
    using SLong2     = CVector2<signed long>;
    using ULong2     = CVector2<unsigned long>;
    using SLongLong2 = CVector2<signed long long>;
    using ULongLong2 = CVector2<unsigned long>;
    using Float2     = CVector2<float>;
    using Double2    = CVector2<double>;
} // namespace Core

#include "core_matrix2x2.h"
#include "core_matrix3x3.h"

namespace Core
{
    template <typename T>
    const CVector2<T> CVector2<T>::s_Zero  = CVector2(T(0));
    template <typename T>
    const CVector2<T> CVector2<T>::s_One   = CVector2(T(1));
    template <typename T>
    const CVector2<T> CVector2<T>::s_AxisX = CVector2(T(1), T(0));
    template <typename T>
    const CVector2<T> CVector2<T>::s_AxisY = CVector2(T(0), T(1));
} // namespace Core

namespace Core
{
    template <typename T>
    inline CVector2<T>::CVector2()
    {
        m_V[0] = 0;
        m_V[1] = 0;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CVector2<T>::CVector2(const CThis& _rVector)
    {
        m_V[0] = _rVector.m_V[0];
        m_V[1] = _rVector.m_V[1];
   }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CVector2<T>::CVector2(EUninitialized)
    {
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CVector2<T>::CVector2(X _Value)
    {
        m_V[0] = _Value;
        m_V[1] = _Value;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CVector2<T>::CVector2(X _Value0, X _Value1)
    {
        m_V[0] = _Value0;
        m_V[1] = _Value1;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator = (const CThis& _rVector)
    {
        m_V[0] = _rVector.m_V[0];
        m_V[1] = _rVector.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::X& CVector2<T>::operator [] (size_t _Index)
    {
        assert(_Index < s_NumberOfComponents);

        return m_V[_Index];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CVector2<T>::X& CVector2<T>::operator [] (size_t _Index) const
    {
        assert(_Index < s_NumberOfComponents);

        return m_V[_Index];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator += (const CThis& _rVector)
    {
        m_V[0] += _rVector.m_V[0];
        m_V[1] += _rVector.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator -= (const CThis& _rVector)
    {
        m_V[0] -= _rVector.m_V[0];
        m_V[1] -= _rVector.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator *= (const CThis& _rVector)
    {
        m_V[0] *= _rVector.m_V[0];
        m_V[1] *= _rVector.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator /= (const CThis& _rVector)
    {
        m_V[0] /= _rVector.m_V[0];
        m_V[1] /= _rVector.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator *= (X _Scalar)
    {
        m_V[0] *= _Scalar;
        m_V[1] *= _Scalar;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator /= (X _Scalar)
    {
        m_V[0] /= _Scalar;
        m_V[1] /= _Scalar;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator *= (const CMatrix2x2<X>& _rMatrix)
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _rMatrix[0][0] + m_V[1] * _rMatrix[1][0];
        V[1] = m_V[0] * _rMatrix[0][1] + m_V[1] * _rMatrix[1][1];

        return Set(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::operator *= (const CMatrix3x3<X>& _rMatrix)
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _rMatrix[0][0] + m_V[1] * _rMatrix[1][0] + _rMatrix[2][0];
        V[1] = m_V[0] * _rMatrix[0][1] + m_V[1] * _rMatrix[1][1] + _rMatrix[2][1];

        return Set(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator + (const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] + _rVector.m_V[0];
        V[1] = m_V[1] + _rVector.m_V[1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator - (const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] - _rVector.m_V[0];
        V[1] = m_V[1] - _rVector.m_V[1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator * (const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _rVector.m_V[0];
        V[1] = m_V[1] * _rVector.m_V[1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator / (const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] / _rVector.m_V[0];
        V[1] = m_V[1] / _rVector.m_V[1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator * (X _Scalar) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _Scalar;
        V[1] = m_V[1] * _Scalar;

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator / (X _Scalar) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] / _Scalar;
        V[1] = m_V[1] / _Scalar;

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator * (const CMatrix2x2<X>& _rMatrix) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _rMatrix[0][0] + m_V[1] * _rMatrix[1][0];
        V[1] = m_V[0] * _rMatrix[0][1] + m_V[1] * _rMatrix[1][1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator * (const CMatrix3x3<X>& _rMatrix) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _rMatrix[0][0] + m_V[1] * _rMatrix[1][0] + _rMatrix[2][0];
        V[1] = m_V[0] * _rMatrix[0][1] + m_V[1] * _rMatrix[1][1] + _rMatrix[2][1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::operator - () const
    {
        return GetNeg();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CVector2<T>::operator == (const CThis& _rVector) const
    {
        return (m_V[0] == _rVector.m_V[0]) && (m_V[1] == _rVector.m_V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CVector2<T>::operator != (const CThis& _rVector) const
    {
        return (m_V[0] != _rVector.m_V[0]) || (m_V[1] != _rVector.m_V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CVector2<T>::operator < (const CThis& _rVector) const
    {
        return (m_V[0] < _rVector.m_V[0]) && (m_V[1] < _rVector.m_V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CVector2<T>::operator <= (const CThis& _rVector) const
    {
        return (m_V[0] <= _rVector.m_V[0]) && (m_V[1] <= _rVector.m_V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CVector2<T>::operator > (const CThis& _rVector) const
    {
        return (m_V[0] > _rVector.m_V[0]) && (m_V[1] > _rVector.m_V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CVector2<T>::operator >= (const CThis& _rVector) const
    {
        return (m_V[0] >= _rVector.m_V[0]) && (m_V[1] >= _rVector.m_V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Set(const CThis& _rVector)
    {
        m_V[0] = _rVector.m_V[0];
        m_V[1] = _rVector.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Set(X _Value)
    {
        m_V[0] = _Value;
        m_V[1] = _Value;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Set(X _Value0, X _Value1)
    {
        m_V[0] = _Value0;
        m_V[1] = _Value1;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Normalize()
    {
        return Normalize2();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Normalize2()
    {
        X Length;

        Length = GetLength2();

        m_V[0] /= Length;
        m_V[1] /= Length;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetNormalized() const
    {
        return GetNormalized2();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetNormalized2() const
    {
        X Length;
        X V[s_NumberOfComponents];

        Length = GetLength2();

        V[0] = m_V[0] / Length;
        V[1] = m_V[1] / Length;

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CVector2<T>::IsNormalized() const
    {
        X Length;

        Length = GetLength2();

        return ::Core::IsEqual(Length, static_cast<X>(1), SConstants<X>::s_EpsilonSquare);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::X CVector2<T>::GetLength() const
    {
        return GetLength2();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::X CVector2<T>::GetLength2() const
    {
        return SquareRoot(GetSquaredLength2());
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::X CVector2<T>::GetSquaredLength() const
    {
        return GetSquaredLength2();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::X CVector2<T>::GetSquaredLength2() const
    {
        return GetDotProduct2(*this);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Reciprocal()
    {
        assert(m_V[0] != static_cast<X>(0));
        assert(m_V[1] != static_cast<X>(0));

        m_V[0] = static_cast<X>(1) / m_V[0];
        m_V[1] = static_cast<X>(1) / m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetReciprocal() const
    {
        X V[s_NumberOfComponents];

        assert(m_V[0] != static_cast<X>(0));
        assert(m_V[1] != static_cast<X>(0));

        V[0] = static_cast<X>(1) / m_V[0];
        V[1] = static_cast<X>(1) / m_V[1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Round()
    {
        m_V[0] = ::Core::Round(m_V[0]);
        m_V[1] = ::Core::Round(m_V[1]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetRounded() const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Round(m_V[0]);
        V[1] = ::Core::Round(m_V[1]);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Clamp(const CThis& _rMin, const CThis& _rMax)
    {
        m_V[0] = ::Core::Clamp(m_V[0], _rMin.m_V[0], _rMax.m_V[0]);
        m_V[1] = ::Core::Clamp(m_V[1], _rMin.m_V[1], _rMax.m_V[1]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetClamped(const CThis& _rMin, const CThis& _rMax) const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Clamp(m_V[0], _rMin.m_V[0], _rMax.m_V[0]);
        V[1] = ::Core::Clamp(m_V[1], _rMin.m_V[1], _rMax.m_V[1]);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Saturate()
    {
        m_V[0] = ::Core::Clamp(m_V[0], static_cast<X>(0), static_cast<X>(1));
        m_V[1] = ::Core::Clamp(m_V[1], static_cast<X>(0), static_cast<X>(1));

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetSaturated() const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Clamp(m_V[0], static_cast<X>(0), static_cast<X>(1));
        V[1] = ::Core::Clamp(m_V[1], static_cast<X>(0), static_cast<X>(1));

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Min(const CThis& _rVector)
    {
        m_V[0] = ::Core::Min(m_V[0], _rVector.m_V[0]);
        m_V[1] = ::Core::Min(m_V[1], _rVector.m_V[1]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetMin(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Min(m_V[0], _rVector.m_V[0]);
        V[1] = ::Core::Min(m_V[1], _rVector.m_V[1]);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Max(const CThis& _rVector)
    {
        m_V[0] = ::Core::Max(m_V[0], _rVector.m_V[0]);
        m_V[1] = ::Core::Max(m_V[1], _rVector.m_V[1]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetMax(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Max(m_V[0], _rVector.m_V[0]);
        V[1] = ::Core::Max(m_V[1], _rVector.m_V[1]);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Neg()
    {
        m_V[0] = ::Core::Neg(m_V[0]);
        m_V[1] = ::Core::Neg(m_V[1]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetNeg() const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Neg(m_V[0]);
        V[1] = ::Core::Neg(m_V[1]);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::MulAdd(const CThis& _rVector1, const CThis& _rVector2)
    {
        m_V[0] = m_V[0] * _rVector1.m_V[0] + _rVector2.m_V[0];
        m_V[1] = m_V[1] * _rVector1.m_V[1] + _rVector2.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetMulAdd(const CThis& _rVector1, const CThis& _rVector2) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _rVector1.m_V[0] + _rVector2.m_V[0];
        V[1] = m_V[1] * _rVector1.m_V[1] + _rVector2.m_V[1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::MulSub(const CThis& _rVector1, const CThis& _rVector2)
    {
        m_V[0] = m_V[0] * _rVector1.m_V[0] - _rVector2.m_V[0];
        m_V[1] = m_V[1] * _rVector1.m_V[1] - _rVector2.m_V[1];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetMulSub(const CThis& _rVector1, const CThis& _rVector2) const
    {
        X V[s_NumberOfComponents];

        V[0] = m_V[0] * _rVector1.m_V[0] - _rVector2.m_V[0];
        V[1] = m_V[1] * _rVector1.m_V[1] - _rVector2.m_V[1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Lerp(const CThis& _rTarget, const CThis& _rWeight)
    {
        m_V[0] = ::Core::Lerp(m_V[0], _rTarget.m_V[0], _rWeight.m_V[0]);
        m_V[1] = ::Core::Lerp(m_V[1], _rTarget.m_V[1], _rWeight.m_V[1]);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetLerped(const CThis& _rTarget, const CThis& _rWeight) const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Lerp(m_V[0], _rTarget.m_V[0], _rWeight.m_V[0]);
        V[1] = ::Core::Lerp(m_V[1], _rTarget.m_V[1], _rWeight.m_V[1]);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Lerp(const CThis& _rTarget, X _Weight)
    {
        m_V[0] = ::Core::Lerp(m_V[0], _rTarget.m_V[0], _Weight);
        m_V[1] = ::Core::Lerp(m_V[1], _rTarget.m_V[1], _Weight);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetLerped(const CThis& _rTarget, X _Weight) const
    {
        X V[s_NumberOfComponents];

        V[0] = ::Core::Lerp(m_V[0], _rTarget.m_V[0], _Weight);
        V[1] = ::Core::Lerp(m_V[1], _rTarget.m_V[1], _Weight);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::Splat(const X _Value)
    {
        m_V[0] = _Value;
        m_V[1] = _Value;

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetSplatted(const X _Value) const
    {
        return CThis(_Value);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::X CVector2<T>::GetDotProduct(const CThis& _rVector) const
    {
        return GetDotProduct2(_rVector);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::X CVector2<T>::GetDotProduct2(const CThis& _rVector) const
    {
        return m_V[0] * _rVector.m_V[0] + m_V[1] * _rVector.m_V[1];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    template <size_t TIndex0, size_t TIndex1>
    inline typename CVector2<T>::CThis& CVector2<T>::Swizzle()
    {
        return (*this) = GetSwizzled<TIndex0, TIndex1>();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    template <size_t TIndex0, size_t TIndex1>
    inline typename CVector2<T>::CThis CVector2<T>::GetSwizzled() const
    {
        X V[s_NumberOfComponents];

        CORE_STATIC_ASSERT(TIndex0 < s_NumberOfComponents);
        CORE_STATIC_ASSERT(TIndex1 < s_NumberOfComponents);

        V[0] = m_V[TIndex0];
        V[1] = m_V[TIndex1];

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    template <size_t TIndex0, size_t TIndex1>
    inline typename CVector2<T>::CThis& CVector2<T>::Permute(const CThis& _rVector)
    {
        m_V[0] = (TIndex0 < s_NumberOfComponents) ? m_V[TIndex0] : _rVector.m_V[TIndex0 % s_NumberOfComponents];
        m_V[1] = (TIndex1 < s_NumberOfComponents) ? m_V[TIndex1] : _rVector.m_V[TIndex1 % s_NumberOfComponents];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    template <size_t TIndex0, size_t TIndex1>
    inline typename CVector2<T>::CThis CVector2<T>::GetPermuted(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = (TIndex0 < s_NumberOfComponents) ? m_V[TIndex0] : _rVector.m_V[TIndex0 % s_NumberOfComponents];
        V[1] = (TIndex1 < s_NumberOfComponents) ? m_V[TIndex1] : _rVector.m_V[TIndex1 % s_NumberOfComponents];

        return CVector2(V[0], V[1]);
    }

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::TestEqual(const CThis& _rVector)
    {
        m_V[0] = (m_V[0] == _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        m_V[1] = (m_V[1] == _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetTestEqual(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = (m_V[0] == _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        V[1] = (m_V[1] == _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::TestNotEqual(const CThis& _rVector)
    {
        m_V[0] = (m_V[0] != _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        m_V[1] = (m_V[1] != _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetTestNotEqual(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = (m_V[0] != _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        V[1] = (m_V[1] != _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::TestLesser(const CThis& _rVector)
    {
        m_V[0] = (m_V[0] < _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        m_V[1] = (m_V[1] < _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetTestLesser(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = (m_V[0] < _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        V[1] = (m_V[1] < _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::TestLesserEqual(const CThis& _rVector)
    {
        m_V[0] = (m_V[0] <= _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        m_V[1] = (m_V[1] <= _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetTestLesserEqual(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = (m_V[0] <= _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        V[1] = (m_V[1] <= _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::TestGreater(const CThis& _rVector)
    {
        m_V[0] = (m_V[0] > _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        m_V[1] = (m_V[1] > _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetTestGreater(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = (m_V[0] > _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        V[1] = (m_V[1] > _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return CVector2(V[0], V[1]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis& CVector2<T>::TestGreaterEqual(const CThis& _rVector)
    {
        m_V[0] = (m_V[0] >= _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        m_V[1] = (m_V[1] >= _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CVector2<T>::CThis CVector2<T>::GetTestGreaterEqual(const CThis& _rVector) const
    {
        X V[s_NumberOfComponents];

        V[0] = (m_V[0] >= _rVector.m_V[0]) ? static_cast<X>(1) : static_cast<X>(0);
        V[1] = (m_V[1] >= _rVector.m_V[1]) ? static_cast<X>(1) : static_cast<X>(0);

        return CVector2(V[0], V[1]);
    }
} // namespace Core
