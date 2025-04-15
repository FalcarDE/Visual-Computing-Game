
#pragma once

#include "core_uncopyable.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace Core
{
    class CIDManager : private CUncopyable
    {
        public:

            using BID = unsigned int;

        public:

            static constexpr BID s_InvalidID = BID(-1);

        public:

            CIDManager();
           ~CIDManager();

        public:

            BID Register(const std::string& _rString);

            bool ContainsName(const std::string& _rString) const;

            const std::string& GetName(BID _ID) const;

            size_t GetNumberOfNames() const;

        public:

            void Clear();

        private:

            using CIDsByName         = std::unordered_map<std::string, BID>;
            using SIDsByNameItem     = std::pair<std::string, BID>;
            using CIDsByNameIterator = CIDsByName::iterator;
            using CIDsByNameResult   = std::pair<CIDsByNameIterator, bool>;
            using CNamesByID         = std::vector<CIDsByNameIterator>;

        private:

            CIDsByName m_IDsByName;
            CNamesByID m_NamesByID;
    };
} // namespace Core
