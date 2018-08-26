
//          Copyright John McFarlane 2015 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_IMPL_WIDE_INTEGER_OPERATORS_H)
#define CNL_IMPL_WIDE_INTEGER_OPERATORS_H

#include "cnl/_impl/wide_integer/type.h"

/// compositional numeric library
namespace cnl {
    namespace _impl {
        template<class Operator, typename Rep>
        struct binary_operator<Operator, integer<Rep>, integer<Rep>, typename Operator::is_comparison> {
            constexpr auto operator()(integer<Rep> const& lhs, integer<Rep> const& rhs) const
            -> decltype(Operator()(_impl::to_rep(lhs), _impl::to_rep(rhs)))
            {
                return Operator()(_impl::to_rep(lhs), _impl::to_rep(rhs));
            }
        };
    }
}

#endif  // CNL_IMPL_WIDE_INTEGER_OPERATORS_H
