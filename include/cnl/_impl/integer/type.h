
//          Copyright John McFarlane 2015 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_IMPL_WIDE_INTEGER_OPERATORS_H)
#define CNL_IMPL_WIDE_INTEGER_OPERATORS_H

#include "../number_base.h"

/// compositional numeric library
namespace cnl {
    namespace _impl {
        // just an integer; useful when you just want to use a fundamental integer but for some reason, a class is
        // required, e.g.: `class X : public int`
        template<typename Rep=int>
        class integer : public number_base<integer<Rep>, Rep> {
        };
    }
}

#endif  // CNL_IMPL_WIDE_INTEGER_OPERATORS_H
