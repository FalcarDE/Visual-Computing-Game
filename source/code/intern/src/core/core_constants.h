
////////////////////////////////////////////////////////////////////////////////
/// \file    core_constants.h
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

namespace Core
{
    template <typename T>
    struct SConstants
    {
        public:

            using X = T;

        public:

            static const X s_Pi;
            static const X s_HalfPi;
            static const X s_TwoPi;
            static const X s_SquareRootOfTwo;
            static const X s_Epsilon;
            static const X s_EpsilonSquare;
    };
} // namespace Core

namespace Core
{
    template <typename T>
    const typename SConstants<T>::X SConstants<T>::s_Pi              = static_cast<X>(3.1415926535897932384626433832795);
    template <typename T>
    const typename SConstants<T>::X SConstants<T>::s_HalfPi          = static_cast<X>(1.5707963267948966192313216916395);
    template <typename T>
    const typename SConstants<T>::X SConstants<T>::s_TwoPi           = static_cast<X>(6.2831853071795864769252867665590);
    template <typename T>
    const typename SConstants<T>::X SConstants<T>::s_SquareRootOfTwo = static_cast<X>(1.4142135623730950488016887242097);
    template <typename T>
    const typename SConstants<T>::X SConstants<T>::s_Epsilon         = static_cast<X>(0.000001);
    template <typename T>
    const typename SConstants<T>::X SConstants<T>::s_EpsilonSquare   = static_cast<X>(4) * s_Epsilon;
} // namespace Core
