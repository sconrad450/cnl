
//          Copyright John McFarlane 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cnl/overflow.h>
#include <cnl/wide_integer.h>

#include <cnl/cmath.h>
#include <cnl/_impl/type_traits/identical.h>

#include <gtest/gtest.h>

namespace {
    using cnl::_impl::identical;
    static_assert(
            cnl::_impl::has_most_negative_number<cnl::wide_integer<100>>::value,
            "");

    namespace test_ctor {
        TEST(static_number, ctor_fraction)
        {
            auto expected = cnl::wide_integer<200>{std::pow(2., 196.)/3.};
            auto actual = (cnl::_impl::wide_integer<200>(1) << 196)/cnl::_impl::wide_integer<200>(3);
            ASSERT_LT(cnl::abs(expected-actual), cnl::_impl::wide_integer<200>{.0001});
        }
    }
}
