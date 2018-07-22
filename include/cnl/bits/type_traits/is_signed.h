
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef CNL_BITS_TYPE_TRAITS_IS_SIGNED
#define CNL_BITS_TYPE_TRAITS_IS_SIGNED

#include <cnl/bits/config.h>
#include <cnl/bits/num_traits/is_composite.h>
#include <cnl/bits/num_traits/to_rep.h>
#include <cnl/bits/type_traits.h>

namespace cnl {
    template<typename T, class Enable = void>
    struct is_signed : std::is_signed<T> {
    };

#if defined(CNL_INT128_ENABLED)
    template<>
    struct is_signed<int128> : std::true_type {
    };
    
    template<>
    struct is_signed<uint128> : std::false_type {
    };
#endif

    // template<class Number>
    // struct is_signed<Number, _impl::enable_if_t<is_composite<Number>::value>> 
    //         : is_signed<_impl::to_rep_t<Number>> {
    // };
}

#endif  // CNL_BITS_TYPE_TRAITS_IS_SIGNED
