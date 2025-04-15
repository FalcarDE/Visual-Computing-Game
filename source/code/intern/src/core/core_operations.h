
////////////////////////////////////////////////////////////////////////////////
/// \file    core_operations.h
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

#include <math.h>

namespace Core
{
    inline float Round(float _Value);
    inline double Round(double _Value);

    inline float RoundUp(float _Value);
    inline double RoundUp(double _Value);

    inline float RoundDown(float _Value);
    inline double RoundDown(double _Value);

    inline float Square(float _Value);
    inline double Square(double _Value);

    inline float SquareRoot(float _Value);
    inline double SquareRoot(double _Value);

    inline float ReciprocalSquareRoot(float _Value);
    inline double ReciprocalSquareRoot(double _Value);

    inline float Cos(float _Value);
    inline double Cos(double _Value);

    inline float Sin(float _Value);
    inline double Sin(double _Value);

    inline float Tan(float _Value);
    inline double Tan(double _Value);

    inline float ArcCos(float _Value);
    inline double ArcCos(double _Value);

    inline float ArcSin(float _Value);
    inline double ArcSin(double _Value);

    inline float ArcTan(float _Value);
    inline double ArcTan(double _Value);

    inline float ArcTan(float _Value1, float _Value2);
    inline double ArcTan(double _Value1, double _Value2);

    inline float RadiansToDegrees(float  _Radians) ;
    inline double RadiansToDegrees(double _Radians);
    inline float DegreesToRadians(float _Degrees);
    inline double DegreesToRadians(double _Degrees);

    inline bool IsEqual(float _Value1, float _Value2, float _Epsilon);
    inline bool IsEqual(double _Value1, double _Value2, double _Epsilon);

    template <typename T>
    inline T Min(T _Value1, T _Value2);
    template <typename T>
    inline T Max(T _Value1, T _Value2);

    template <typename T>
    inline T Abs(T _Value);

    template <typename T>
    inline T Neg(T _Value);

    template <typename T>
    inline T Clamp(T _Value, T _Min, T _Max);

    template <typename T>
    inline T Lerp(T _Start, T _End, T _Weight);
} // namespace Core

namespace Core
{
    inline float Round(float _Value)
    {
        return (_Value > 0.0f) ? RoundDown(_Value + 0.5f) : RoundUp(_Value - 0.5f); 
    }

    // -----------------------------------------------------------------------------

    inline double Round(double _Value)
    {
        return (_Value > 0.0) ? RoundDown(_Value + 0.5) : RoundUp(_Value - 0.5); 
    }

    // -----------------------------------------------------------------------------

    inline float RoundUp(float _Value)
    {
        return ceilf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double RoundUp(double _Value)
    {
        return ceil(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float RoundDown(float _Value)
    {
        return floorf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double RoundDown(double _Value)
    {
        return floor(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float Square(float _Value)
    { 
        return _Value * _Value;
    }

    // -----------------------------------------------------------------------------

    inline double Square(double _Value)
    { 
        return _Value * _Value;
    }

    // -----------------------------------------------------------------------------

    inline float SquareRoot(float _Value)
    { 
        return sqrtf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double SquareRoot(double _Value)
    { 
        return sqrt(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float ReciprocalSquareRoot(float _Value)
    {
        return 1.0f / SquareRoot(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double ReciprocalSquareRoot(double _Value)
    {
        return 1.0 / SquareRoot(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float Cos(float _Value)
    {
        return cosf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double Cos(double _Value)
    {
        return cos(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float Sin(float _Value)
    {
        return sinf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double Sin(double _Value)
    {
        return sin(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float Tan(float _Value)
    {
        return tanf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double Tan(double _Value)
    {
        return tan(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float ArcCos(float _Value)
    {
        return acosf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double ArcCos(double _Value)
    {
        return acos(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float ArcSin(float _Value)
    {
        return asinf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double ArcSin(double _Value)
    {
        return asin(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float ArcTan(float _Value)
    {
        return atanf(_Value);
    }

    // -----------------------------------------------------------------------------

    inline double ArcTan(double _Value)
    {
        return atan(_Value);
    }

    // -----------------------------------------------------------------------------

    inline float ArcTan(float _Value1, float _Value2)
    {
        return atan2f(_Value1, _Value2);
    }

    // -----------------------------------------------------------------------------

    inline double ArcTan(double _Value1, double _Value2)
    {
        return atan2(_Value1, _Value2);
    }

    // -----------------------------------------------------------------------------

    inline float RadiansToDegrees(float  _Radians) 
    { 
        return (180.0f / SConstants<float>::s_Pi) * _Radians; 
    }

    // -----------------------------------------------------------------------------

    inline double RadiansToDegrees(double _Radians) 
    { 
        return (180.0 / SConstants<double>::s_Pi) * _Radians; 
    }

    // -----------------------------------------------------------------------------

    inline float DegreesToRadians(float _Degrees) 
    { 
        return (SConstants<float>::s_Pi / 180.0f) * _Degrees; 
    }

    // -----------------------------------------------------------------------------

    inline double DegreesToRadians(double _Degrees) 
    { 
        return (SConstants<double>::s_Pi / 180.0) * _Degrees; 
    }

    // -----------------------------------------------------------------------------

    inline bool IsEqual(float _Value1, float _Value2, float _Epsilon)
    {
        return Abs(_Value2 - _Value1) <= _Epsilon;
    }

    // -----------------------------------------------------------------------------

    inline bool IsEqual(double _Value1, double _Value2, double _Epsilon)
    {
        return Abs(_Value2 - _Value1) <= _Epsilon;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline T Min(T _Value1, T _Value2)
    {
        return (_Value1 < _Value2) ? _Value1 : _Value2;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline T Max(T _Value1, T _Value2)
    {
        return (_Value1 > _Value2) ? _Value1 : _Value2;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline T Abs(T _Value)
    {
        return (_Value < 0) ? -_Value : _Value;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline T Neg(T _Value)
    {
        return -_Value;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline T Clamp(T _Value, T _Min, T _Max)
    {
        if (_Value < _Min) return _Min;
        if (_Value > _Max) return _Max;

        return _Value;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline T Lerp(T _Start, T _End, T _Weight)
    {
        return _Start + _Weight * (_End - _Start);
    }
} // namespace Core
