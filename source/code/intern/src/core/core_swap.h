
////////////////////////////////////////////////////////////////////////////////
/// \file    core_swap.h
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
    inline void Swap(T& _rLeft, T& _rRight);
} // namespace Core

namespace Core
{
    template <typename T> 
    inline void Swap(T& _rLeft, T& _rRight)
    {
        if (&_rLeft != &_rRight)
        {
            T Tmp = _rLeft; _rLeft = _rRight; _rRight = Tmp;
        }
    }
} // namespace Core
