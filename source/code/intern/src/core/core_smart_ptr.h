
#pragma once

#include <assert.h>

namespace Core
{
    template <class T>
    class CSmartPtr
    {
        public:

            using CThis     = CSmartPtr<T>;
            using X         = T;
            using XPtr      = T*;
            using XConstPtr = const T*;
            using XRef      = T&;
            using XConstRef = const T&;

        public:

            CSmartPtr()
                : m_pObject(nullptr)
            {
            }

            explicit CSmartPtr(XPtr _pObject)
                : m_pObject(_pObject)
            {
                AddRef(_pObject);
            }

            CSmartPtr(const CThis& _rPtr)
                : m_pObject(_rPtr.m_pObject)
            {
                AddRef(m_pObject);
            }

           ~CSmartPtr()
            {
                Release(m_pObject);
            }

        public:

            CThis& operator = (const CThis& _rPtr)
            {
                XPtr pObject;
                
                pObject = m_pObject; m_pObject = _rPtr.m_pObject;

                AddRef(m_pObject); Release(pObject);

                return *this;
            }

            CThis& operator = (XPtr _pObject)
            {
                XPtr pObject;
                
                pObject = m_pObject; m_pObject = _pObject;

                AddRef(m_pObject); Release(pObject);

                return *this;
            }

        public:

            bool operator < (XConstPtr _pObject) const 
            { 
                return m_pObject < _pObject;
            }

            bool operator <= (XConstPtr _pObject) const 
            { 
                return m_pObject <= _pObject;
            }

            bool operator > (XConstPtr _pObject) const 
            { 
                return m_pObject > _pObject;
            }

            bool operator >= (XConstPtr _pObject) const 
            { 
                return m_pObject >= _pObject;
            }

            bool operator == (XConstPtr _pObject) const 
            { 
                return m_pObject == _pObject;
            }

            bool operator != (XConstPtr _pObject) const 
            { 
                return m_pObject != _pObject;
            }

        public:

            bool operator < (const CThis& _rPtr) const 
            { 
                return m_pObject < _rPtr.m_pObject;
            }

            bool operator <= (const CThis& _rPtr) const 
            { 
                return m_pObject <= _rPtr.m_pObject;
            }

            bool operator > (const CThis& _rPtr) const 
            { 
                return m_pObject > _rPtr.m_pObject;
            }

            bool operator >= (const CThis& _rPtr) const 
            { 
                return m_pObject >= _rPtr.m_pObject;
            }

            bool operator == (const CThis& _rPtr) const 
            { 
                return m_pObject == _rPtr.m_pObject;
            }

            bool operator != (const CThis& _rPtr) const 
            { 
                return m_pObject != _rPtr.m_pObject;
            }

        public:

            XRef operator * ()
            { 
                assert(IsValid());

                return *m_pObject;
            }

            XConstRef operator * () const
            { 
                assert(IsValid());

                return *m_pObject;
            }

            XPtr operator -> ()
            { 
                return m_pObject;
            }

            XConstPtr operator -> () const 
            { 
                return m_pObject;
            }

        public:

            bool IsValid() const 
            { 
                return m_pObject != nullptr;
            }

        public:

            XPtr GetPtr()
            { 
                return m_pObject;
            }

            XConstPtr GetPtr() const
            { 
                return m_pObject;
            }

        public:

            int AddRef()
            { 
                return AddRef(m_pObject);
            }

            int Release() 
            { 
                return Release(m_pObject);
            }

        private:

            XPtr m_pObject;

        private:

            static int AddRef(XPtr _pObject)
            {
                return (_pObject != nullptr) ? _pObject->AddRef() : 0;
            }

            static int Release(XPtr _pObject)
            {
                return (_pObject != nullptr) ? _pObject->Release() : 0;
            }
    };
} // namespace Core