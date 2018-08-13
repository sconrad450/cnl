
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef CNL_IMPL_TYPE_TRAITS_IS_NARROWING
#define CNL_IMPL_TYPE_TRAITS_IS_NARROWING

#include <type_traits>

/// compositional numeric library
namespace cnl {
    namespace _impl {
        // https://groups.google.com/a/isocpp.org/d/msg/std-proposals/FwasK14dTNI/DkGMOM3-BgAJ
        template<typename Src, typename Dest>
        constexpr bool narrowing(...)
        {
            return true;
        }

        template<typename Src, typename Dest>
        constexpr auto narrowing(int) -> decltype(Dest{std::declval<Src>()}, false)
        {
            return false;
        }

        // https://www.kdab.com/~peppe/cpp_proposals/is_non_narrowing_convertible/
        template<typename From, typename To, class Enable = void>
        struct is_narrowing : std::integral_constant<bool, _impl::narrowing<From, To>(0)> {
        };

#if defined(__cpp_variable_templates)
        template<typename From, typename To>
        constexpr int is_narrowing_v = is_narrowing<From, To>::value;
#endif
    }
}

#endif  // CNL_IMPL_TYPE_TRAITS_IS_NARROWING
