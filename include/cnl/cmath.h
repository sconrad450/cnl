
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief file containing definitions that might go in \verbatim<cmath>\endverbatim if they were standard

#ifndef CNL_CMATH_H
#define CNL_CMATH_H

#include <cmath>

/// compositional numeric library
namespace cnl {
    template<typename T>
    constexpr T sqrt(T arg) {
        return std::sqrt(arg);
    }

    using std::abs;

#if defined(CNL_INT128_ENABLED) && defined(__clang__)
    int128 abs(int128 const& n) {
        return (n<0)?-n:n;
    }
    uint128 abs(uint128 const& n) {
        return n;
    }
#endif
}

#endif //CNL_CMATH_H
