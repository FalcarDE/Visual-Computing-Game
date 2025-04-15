
#pragma once

#include "core_vector2.h"

#include <assert.h>

namespace Core
{
    template <typename T>
    class CAABB2
    {
        public:

            using CThis     = CAABB2<T>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;
            using CCorner   = CVector2<T>;

        public:

            enum EUninitialized  
            { 
                Uninitialized,
            };

        public:

            enum
            {
                Min             = 0,
                Max             = 1,
                NumberOfCorners = 2,
            };

        public:

            inline CAABB2();
            inline CAABB2(const CThis& _rAABB);
            inline explicit CAABB2(EUninitialized);
            inline CAABB2(X _X1, X _Y1, X _X2, X _Y2);
            inline CAABB2(const CCorner& _rMin, const CCorner& _rMax);

        public:

            inline CThis& operator = (const CThis& _rAABB);

        public:

            inline CCorner& operator [] (int _Index);
            inline const CCorner& operator [] (int _Index) const;

        public:

            inline bool operator == (const CThis& _rAABB) const;
            inline bool operator != (const CThis& _rAABB) const;

        public:

            inline void SetMin(const CCorner& _rMin);
            inline CCorner& GetMin();
            inline const CCorner& GetMin() const;

            inline void SetMax(const CCorner& _rMax);
            inline CCorner& GetMax();
            inline const CCorner& GetMax() const;

        public:

            inline bool Intersects(const CThis& _rAABB) const;
            inline bool Contains(const CThis& _rAABB) const;
            inline bool Contains(const CCorner& _rVector) const;

        public:

            inline CThis Union(const CThis& _rAABB) const;
            inline CThis Intersection(const CThis& _rAABB) const;

        public:

            inline CCorner GetCenter() const;

        private:

            enum
            {
                MinX               = 0,
                MinY               = 1,
                MaxX               = 2,
                MaxY               = 3,
                NumberOfComponents = 4,
            };

        private:

            X m_V[NumberOfComponents];

        private:

            inline explicit CAABB2(XConstPtr _pV);

        private:

            inline bool IsValid() const;
            inline bool IsValid(const CCorner& _rMin, const CCorner& _rMax) const;
    };
}

namespace Core
{
    template <typename T>
    inline CAABB2<T>::CAABB2() 
    {
        (*this)[Min] = CCorner();
        (*this)[Max] = CCorner();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB2<T>::CAABB2(const CThis& _rAABB) 
    {
        (*this)[Min] = _rAABB[Min];
        (*this)[Max] = _rAABB[Max];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB2<T>::CAABB2(EUninitialized) 
    {
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB2<T>::CAABB2(X _X1, X _Y1, X _X2, X _Y2)
    {
        (*this)[Min][0] = _X1;
        (*this)[Min][1] = _Y1;
        (*this)[Max][0] = _X2;
        (*this)[Max][1] = _Y2;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB2<T>::CAABB2(const CCorner& _rMin, const CCorner& _rMax) 
    {
        (*this)[Min] = _rMin;
        (*this)[Max] = _rMax;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB2<T>::CAABB2(XConstPtr _pV) 
    {
        m_V[MinX] = _pV[MinX];
        m_V[MinY] = _pV[MinY];
        m_V[MaxX] = _pV[MaxX];
        m_V[MaxY] = _pV[MaxY];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB2<T>::CThis& CAABB2<T>::operator = (const CThis& _rAABB)
    {
        (*this)[Min] = _rAABB[Min];
        (*this)[Max] = _rAABB[Max];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB2<T>::CCorner& CAABB2<T>::operator [] (int _Index)
    {
        return const_cast<CCorner&>(static_cast<const CThis&>(*this)[_Index]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CAABB2<T>::CCorner& CAABB2<T>::operator [] (int _Index) const
    {
        assert(_Index < NumberOfCorners);

        return *reinterpret_cast<const CCorner*>(&m_V[_Index * CCorner::s_NumberOfComponents]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CAABB2<T>::operator == (const CThis& _rAABB) const
    {
        return ((*this)[Min] == _rAABB[Min]) && ((*this)[Max] == _rAABB[Max]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CAABB2<T>::operator != (const CThis& _rAABB) const
    {
        return ((*this)[Min] != _rAABB[Min]) || ((*this)[Max] != _rAABB[Max]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline void CAABB2<T>::SetMin(const CCorner& _rMin)
    {
        (*this)[Min] = _rMin;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB2<T>::CCorner& CAABB2<T>::GetMin()
    {
        return (*this)[Min];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CAABB2<T>::CCorner& CAABB2<T>::GetMin() const
    {
        return (*this)[Min];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline void CAABB2<T>::SetMax(const CCorner& _rMax)
    {
        (*this)[Max] = _rMax;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB2<T>::CCorner& CAABB2<T>::GetMax()
    {
        return (*this)[Max];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CAABB2<T>::CCorner& CAABB2<T>::GetMax() const
    {
        return (*this)[Max];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    bool CAABB2<T>::Intersects(const CThis& _rAABB) const
    {
        assert(IsValid() && _rAABB.IsValid());

        return !((m_V[MaxX] < _rAABB.m_V[MinX]) || (m_V[MaxY] < _rAABB.m_V[MinY]) || (m_V[MinX] > _rAABB.m_V[MaxX]) || (m_V[MinY] > _rAABB.m_V[MaxY]));
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    bool CAABB2<T>::Contains(const CThis& _rAABB) const
    {
        assert(IsValid() && _rAABB.IsValid());

        return (m_V[MinX] <= _rAABB.m_V[MinX]) && (m_V[MinY] <= _rAABB.m_V[MinY]) && (m_V[MaxX] >= _rAABB.m_V[MaxX]) && (m_V[MaxY] >= _rAABB.m_V[MaxY]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    bool CAABB2<T>::Contains(const CCorner& _rVector) const
    {
        assert(IsValid());

        return (_rVector[0] >= m_V[MinX]) && (_rVector[1] >= m_V[MinY]) && (_rVector[0] <= m_V[MaxX]) && (_rVector[1] <= m_V[MaxY]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename CAABB2<T>::CThis CAABB2<T>::Union(const CThis& _rAABB) const
    {
        X V[NumberOfComponents];

        assert(IsValid() && _rAABB.IsValid());

        if (m_V[MinX] < _rAABB.m_V[MinX])
        {
            V[MinX] = m_V[MinX];
        }
        else
        {
            V[MinX] = _rAABB.m_V[MinX];
        }

        if (m_V[MinY] < _rAABB.m_V[MinY])
        {
            V[MinY] = m_V[MinY];
        }
        else
        {
            V[MinY] = _rAABB.m_V[MinY];
        }

        if (m_V[MaxX] > _rAABB.m_V[MaxX])
        {
            V[MaxX] = m_V[MaxX];
        }
        else
        {
            V[MaxX] = _rAABB.m_V[MaxX];
        }

        if (m_V[MaxY] > _rAABB.m_V[MaxY])
        {
            V[MaxY] = m_V[MaxY];
        }
        else
        {
            V[MaxY] = _rAABB.m_V[MaxY];
        }
        
        return CThis(V);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename CAABB2<T>::CThis CAABB2<T>::Intersection(const CThis& _rAABB) const
    {
        X V[NumberOfComponents];

        assert(IsValid() && _rAABB.IsValid());

        if (m_V[MinX] > _rAABB.m_V[MinX])
        {
            V[MinX] = m_V[MinX];
        }
        else
        {
            V[MinX] = _rAABB.m_V[MinX];
        }

        if (m_V[MinY] > _rAABB.m_V[MinY])
        {
            V[MinY] = m_V[MinY];
        }
        else
        {
            V[MinY] = _rAABB.m_V[MinY];
        }

        if (m_V[MaxX] < _rAABB.m_V[MaxX])
        {
            V[MaxX] = m_V[MaxX];
        }
        else
        {
            V[MaxX] = _rAABB.m_V[MaxX];
        }

        if (m_V[MaxY] < _rAABB.m_V[MaxY])
        {
            V[MaxY] = m_V[MaxY];
        }
        else
        {
            V[MaxY] = _rAABB.m_V[MaxY];
        }
        
        return CThis(V);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename CAABB2<T>::CCorner CAABB2<T>::GetCenter() const
    {
        assert(IsValid());

        return CCorner((m_V[MinX] + m_V[MaxX]) / X(2), (m_V[MinY] + m_V[MaxY]) / X(2));
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename bool CAABB2<T>::IsValid() const
    {
        return (m_V[MaxX] >= m_V[MinX]) && (m_V[MaxY] >= m_V[MinY]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CAABB2<T>::IsValid(const CCorner& _rMin, const CCorner& _rMax) const
    {
        return (_rMax[0] >= _rMin[0]) && (_rMax[1] >= _rMin[1]);
    }
} // namespace Core
