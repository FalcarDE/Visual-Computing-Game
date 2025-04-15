
#pragma once

namespace Core
{
    template <typename TTargetPtr, typename TSourcePtr>
    TTargetPtr AddToPtr(TSourcePtr* _pPtr, size_t _NumberOfBytes)
    {
        return reinterpret_cast<TTargetPtr>(reinterpret_cast<size_t>(_pPtr) + _NumberOfBytes);
    }

    // -----------------------------------------------------------------------------

    template <typename TTargetPtr, typename TSourcePtr>
    TTargetPtr SubFromPtr(TSourcePtr* _pPtr, size_t _NumberOfBytes)
    {
        return reinterpret_cast<TTargetPtr>(reinterpret_cast<size_t>(_pPtr) - _NumberOfBytes);
    }

    // -----------------------------------------------------------------------------

    template <typename TUnit, typename TStartPtr, typename TEndPtr>
    size_t DistanceOfPtr(TEndPtr* _pEndPtr, TStartPtr* _pStartPtr)
    {
        assert(reinterpret_cast<size_t>(_pEndPtr) >= reinterpret_cast<size_t>(_pStartPtr));

        return (reinterpret_cast<size_t>(_pEndPtr) - reinterpret_cast<size_t>(_pStartPtr)) / sizeof(TUnit);
    }

    // -----------------------------------------------------------------------------

    template <class TOwner, class TMember>
    size_t GetMemberOffset(const TMember TOwner::* _Mtr)
    {
        return DistanceOfPtr<unsigned char>(&(static_cast<const TOwner* const>(0)->*_Mtr), static_cast<const void*>(0));
    }

    //------------------------------------------------------------------------------

    template <class TOwner, class TMember>
    TOwner& GetOwnerOfMember(TMember& _rMember, const TMember TOwner::* _Mtr)
    {
        return *SubFromPtr<TOwner*>(&_rMember, GetMemberOffset(_Mtr));
    }

    //------------------------------------------------------------------------------

    template <class TOwner, class TMember>
    const TOwner& GetOwnerOfMember(const TMember& _rMember, const TMember TOwner::* _Mtr)
    {
        return *SubFromPtr<const TOwner*>(&_rMember, GetMemberOffset(_Mtr));
    }
} // namespace Core
