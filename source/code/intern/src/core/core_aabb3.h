
#pragma once

#include "core_vector3.h"

#include <assert.h>

namespace Core
{
    template <typename T>
    class CAABB3
    {
        public:

            using CThis     = CAABB3<T>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;
            using CCorner   = CVector3<T>;

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

            inline CAABB3();
            inline CAABB3(const CThis& _rAABB);
            inline explicit CAABB3(EUninitialized);
            inline CAABB3(const CCorner& _rMin, const CCorner& _rMax);

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

            inline CCorner GetCentre() const;
            inline float GetDistance(const CCorner& _rPosition) const;

        private:

            enum
            {
                MinX               = 0,
                MinY               = 1,
                MinZ               = 2,
                MaxX               = 3,
                MaxY               = 4,
                MaxZ               = 5,
                NumberOfComponents = 6,
            };

        private:

            X m_V[NumberOfComponents];

        private:

            inline explicit CAABB3(XConstPtr _pV);

        private:

            inline bool IsValid() const;
            inline bool IsValid(const CCorner& _rMin, const CCorner& _rMax) const;
    };
}

namespace Core
{
    template <typename T>
    inline CAABB3<T>::CAABB3() 
    {
        (*this)[Min] = CCorner();
        (*this)[Max] = CCorner();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB3<T>::CAABB3(const CThis& _rAABB) 
    {
        (*this)[Min] = _rAABB[Min];
        (*this)[Max] = _rAABB[Max];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB3<T>::CAABB3(EUninitialized) 
    {
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB3<T>::CAABB3(const CCorner& _rMin, const CCorner& _rMax) 
    {
        (*this)[Min] = _rMin;
        (*this)[Max] = _rMax;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline CAABB3<T>::CAABB3(XConstPtr _pV) 
    {
        m_V[MinX] = _pV[MinX];
        m_V[MinY] = _pV[MinY];
        m_V[MinZ] = _pV[MinZ];
        m_V[MaxX] = _pV[MaxX];
        m_V[MaxY] = _pV[MaxY];
        m_V[MaxZ] = _pV[MaxZ];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB3<T>::CThis& CAABB3<T>::operator = (const CThis& _rAABB)
    {
        (*this)[Min] = _rAABB[Min];
        (*this)[Max] = _rAABB[Max];

        return *this;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB3<T>::CCorner& CAABB3<T>::operator [] (int _Index)
    {
        return const_cast<CCorner&>(static_cast<const CThis&>(*this)[_Index]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CAABB3<T>::CCorner& CAABB3<T>::operator [] (int _Index) const
    {
        assert(_Index < NumberOfCorners);

        return *reinterpret_cast<const CCorner*>(&m_V[_Index * CCorner::s_NumberOfComponents]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CAABB3<T>::operator == (const CThis& _rAABB) const
    {
        return ((*this)[Min] == _rAABB[Min]) && ((*this)[Max] == _rAABB[Max]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CAABB3<T>::operator != (const CThis& _rAABB) const
    {
        return ((*this)[Min] != _rAABB[Min]) || ((*this)[Max] != _rAABB[Max]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline void CAABB3<T>::SetMin(const CCorner& _rMin)
    {
        (*this)[Min] = _rMin;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB3<T>::CCorner& CAABB3<T>::GetMin()
    {
        return (*this)[Min];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CAABB3<T>::CCorner& CAABB3<T>::GetMin() const
    {
        return (*this)[Min];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline void CAABB3<T>::SetMax(const CCorner& _rMax)
    {
        (*this)[Max] = _rMax;
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline typename CAABB3<T>::CCorner& CAABB3<T>::GetMax()
    {
        return (*this)[Max];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline const typename CAABB3<T>::CCorner& CAABB3<T>::GetMax() const
    {
        return (*this)[Max];
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    bool CAABB3<T>::Intersects(const CThis& _rAABB) const
    {
        assert(IsValid() && _rAABB.IsValid());

        return !((m_V[MaxX] < _rAABB.m_V[MinX]) ||
                 (m_V[MaxY] < _rAABB.m_V[MinY]) ||
                 (m_V[MaxZ] < _rAABB.m_V[MinZ]) ||
                 (m_V[MinX] > _rAABB.m_V[MaxX]) ||
                 (m_V[MinY] > _rAABB.m_V[MaxY]) ||
                 (m_V[MinZ] > _rAABB.m_V[MaxZ]));
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    bool CAABB3<T>::Contains(const CThis& _rAABB) const
    {
        assert(IsValid() && _rAABB.IsValid());

        return (m_V[MinX] <= _rAABB.m_V[MinX]) && 
               (m_V[MinY] <= _rAABB.m_V[MinY]) &&
               (m_V[MinZ] <= _rAABB.m_V[MinZ]) &&
               (m_V[MaxX] >= _rAABB.m_V[MaxX]) &&
               (m_V[MaxY] >= _rAABB.m_V[MaxY]) &&
               (m_V[MaxZ] >= _rAABB.m_V[MaxZ]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    bool CAABB3<T>::Contains(const CCorner& _rVector) const
    {
        assert(IsValid());

        return (_rVector[0] >= m_V[MinX]) &&
               (_rVector[1] >= m_V[MinY]) && 
               (_rVector[2] >= m_V[MinZ]) && 
               (_rVector[0] <= m_V[MaxX]) && 
               (_rVector[1] <= m_V[MaxY]) &&
               (_rVector[2] <= m_V[MaxZ]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename CAABB3<T>::CThis CAABB3<T>::Union(const CThis& _rAABB) const
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

        if (m_V[MinZ] < _rAABB.m_V[MinZ])
        {
            V[MinZ] = m_V[MinZ];
        }
        else
        {
            V[MinZ] = _rAABB.m_V[MinZ];
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

        if (m_V[MaxZ] > _rAABB.m_V[MaxZ])
        {
            V[MaxZ] = m_V[MaxZ];
        }
        else
        {
            V[MaxZ] = _rAABB.m_V[MaxZ];
        }

        return CThis(V);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename CAABB3<T>::CThis CAABB3<T>::Intersection(const CThis& _rAABB) const
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

        if (m_V[MinZ] > _rAABB.m_V[MinZ])
        {
            V[MinZ] = m_V[MinZ];
        }
        else
        {
            V[MinZ] = _rAABB.m_V[MinZ];
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

        if (m_V[MaxZ] < _rAABB.m_V[MaxZ])
        {
            V[MaxZ] = m_V[MaxZ];
        }
        else
        {
            V[MaxZ] = _rAABB.m_V[MaxZ];
        }

        return CThis(V);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename CAABB3<T>::CCorner CAABB3<T>::GetCentre() const
    {
        assert(IsValid());

        return CCorner((m_V[MinX] + m_V[MaxX]) / X(2), (m_V[MinY] + m_V[MaxY]) / X(2), (m_V[MinZ] + m_V[MaxZ]) / X(2));
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline float CAABB3<T>::GetDistance(const CCorner& _rPosition) const
    {
        if (Contains(_rPosition))
        { 
            return 0.0f; 
        }
        
        CCorner ClosestCorner(0.0f);

        ClosestCorner[0] = m_V[MinX] > _rPosition[0] ? m_V[MinX] : m_V[MaxX] < _rPosition[0] ? m_V[MaxX] : _rPosition[0];
        ClosestCorner[1] = m_V[MinY] > _rPosition[1] ? m_V[MinY] : m_V[MaxY] < _rPosition[1] ? m_V[MaxY] : _rPosition[1];
        ClosestCorner[2] = m_V[MinZ] > _rPosition[2] ? m_V[MinZ] : m_V[MaxZ] < _rPosition[2] ? m_V[MaxZ] : _rPosition[2];

        return (ClosestCorner - _rPosition).GetLength();
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    typename bool CAABB3<T>::IsValid() const
    {
        return (m_V[MaxX] >= m_V[MinX]) && (m_V[MaxY] >= m_V[MinY]) && (m_V[MaxZ] >= m_V[MinZ]);
    }

    // -----------------------------------------------------------------------------

    template <typename T>
    inline bool CAABB3<T>::IsValid(const CCorner& _rMin, const CCorner& _rMax) const
    {
        return (_rMax[0] >= _rMin[0]) && (_rMax[1] >= _rMin[1]) && (_rMax[2] >= _rMin[2]);
    }
} // namespace Core
