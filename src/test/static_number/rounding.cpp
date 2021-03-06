
//          Copyright John McFarlane 2015 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cnl/static_number.h>
#include <cnl/_impl/type_traits/assert_same.h>

namespace {
    using cnl::_impl::identical;
    using cnl::_impl::assert_same;

    namespace test_rounding_t {
        static_assert(
                assert_same<
                        cnl::_impl::nearest_rounding_tag,
                        cnl::_impl::rounding_t<cnl::static_number<1>>
                >::value,
                "cnl::_impl::rounding_t<cnl::static_number<>> test failed");
    }

    namespace test_set_rounding_t {
        static_assert(
                assert_same<
                        cnl::static_number<1, 0, cnl::native_rounding_tag>,
                        cnl::_impl::set_rounding_t<
                                cnl::static_number<1>,
                                cnl::native_rounding_tag>
                >::value,
                "cnl::_impl::set_rounding_t<cnl::static_number<>> test failed");
    }
}
