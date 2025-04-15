
#pragma once

namespace Core
{
    class CUncopyable
    {
        protected:

            CUncopyable() = default;
           ~CUncopyable() = default;

        private:

            CUncopyable(const CUncopyable&) = delete;

            CUncopyable& operator = (const CUncopyable&) = delete;
    };
} // namespace Core
