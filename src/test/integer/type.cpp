
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief tests for <cnl/wide_integer.h>

#include <cnl/_impl/integer.h>

#include <cnl/_impl/type_traits/assert_same.h>
#include <cnl/_impl/type_traits/identical.h>

using cnl::_impl::assert_same;
using cnl::_impl::identical;

namespace {
    namespace test_parameters {
        static_assert(
                assert_same<cnl::_impl::integer<int>, cnl::_impl::integer<>>::value,
                "default parameters of cnl::integer");
    }

    namespace test_is_composite {
        static_assert(identical(true, cnl::is_composite<cnl::_impl::integer<>>::value), "is_composite<integer>");
    }

//    namespace test_ctor {
//        static_assert(
//                identical(cnl::wide_integer<int, 2>{}, cnl::wide_integer<int, 2>{0}),
//                "constructor taking integer");
//    }
//
//    namespace test_big_number {
//        auto max = cnl::numeric_limits<int>::max();
//        static_assert(
//                identical(
//                        cnl::wide_integer<int, 2>{max/3},
//                        (cnl::wide_integer<int, 2>{max}*300)/100),
//                "constructor taking integer");
//    }
}
