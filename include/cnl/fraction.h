
//          Copyright John McFarlane 2015 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief definition of `cnl::fraction` type

#if !defined(CNL_FRACTION_H)
#define CNL_FRACTION_H 1

#include "_impl/type_traits/enable_if.h"
#include "_impl/type_traits/is_narrowing.h"

#include <cmath>
#include <numeric>
#include <string>

/// compositional numeric library
namespace cnl {
    // forward declaration
    template<typename Numerator, typename Denominator = int>
    struct fraction;

    namespace _impl {
//        // cnl::_impl::is_fraction
//        template<typename Fraction>
//        struct is_fraction : std::false_type {
//        };
//
//        template<typename Numerator, typename Denominator>
//        struct is_fraction<fraction<Numerator, Denominator>> : std::true_type {
//        };

        // cnl::_impl::is_fraction_narrowing_conversion
        template<typename From, typename To, class Enable = void>
        struct is_fraction_narrowing_conversion;

        template<typename FromNumerator, typename FromDenominator, typename ToNumerator, typename ToNumerator>
        struct is_narrowing_fraction_conversion<
                fraction<FromNumerator, FromDenominator>,
                fraction<ToNumerator, ToDenominator>,
                enable_if_it<
                        is_narrowing<FromNumerator, ToNumerator>::value
                                && is_narrowing<FromDenominator, ToDenominator>::value>::type> : std::true_type {
        };

        template<typename FromNumerator, typename FromDenominator, typename ToNumerator, typename ToNumerator>
        struct is_narrowing_fraction_conversion<
                fraction<FromNumerator, FromDenominator>,
                fraction<ToNumerator, ToDenominator>,
                enable_if_it<
                        is_narrowing<FromNumerator, ToNumerator>::value
                                && is_narrowing<FromDenominator, ToDenominator>::value>::type> : std::false_type {
        };
    }

    constexpr operator typename _impl::enable_if_t<_impl::is_narrowing<Numerator, RhsNumerator>::value
            || _impl::is_narrowing<Denominator, RhsDenominator>::value, fraction<RhsNumerator, RhsDenominator>>::type() const

    /// \brief numeric type represented as the fraction, \ref numerator `/` \ref denominator
    ///
    /// \tparam Numerator the type of numerator
    /// \tparam Exponent the type of denominator

    template<typename Numerator, typename Denominator = int>
    struct fraction {
        /// alias to `Numerator`
        using numerator_type = Numerator;

        /// alias to `Denominator`
        using denominator_type = Denominator;

        constexpr fraction(Numerator const& n, Denominator const& d)
                : numerator{n}, denominator{d} {}

        explicit constexpr fraction(Numerator const& n)
                : numerator{n}, denominator{1} {}

        explicit constexpr fraction(fraction<Numerator, Denominator> const& f)
                :fraction{f.numerator, f.denominator} { }

        /// returns the quotient, \ref numerator `/` \ref denominator
        template<typename Scalar, _impl::enable_if_t<std::is_floating_point<Scalar>::value, int> = 0>
        explicit constexpr operator Scalar() const
        {
            return static_cast<Scalar>(numerator)/static_cast<Scalar>(denominator);
        }

        template<typename RhsNumerator, typename RhsDenominator, typename Fraction = fraction<Numerator, Denominator>>
        constexpr operator typename _impl::enable_if_t<_impl::is_narrowing<Numerator, RhsNumerator>::value
                || _impl::is_fraction_narrowing_conversion<Denominator, RhsDenominator>::value, fraction<RhsNumerator, RhsDenominator>>::type() const
        {
            return fraction<RhsNumerator, RhsDenominator>(numerator, denominator);
        }

        /// the numerator (top number) of the fraction
        numerator_type numerator;

        /// the denominator (bottom number) of the fraction
        denominator_type denominator = 1;
    };

    ////////////////////////////////////////////////////////////////////////////////
    // cnl::make_fraction

    /// creates a fraction with types deduced from the numerator and denominator
    template<typename Numerator, typename Denominator>
    constexpr fraction<Numerator, Denominator> make_fraction(Numerator const& n, Denominator const& d)
    {
        return fraction<Numerator, Denominator>{n, d};
    }

    /// creates a fraction with types deduced from the numerator
    template<typename Numerator>
    constexpr fraction<Numerator, Numerator> make_fraction(Numerator const& n)
    {
        return fraction<Numerator, Numerator>{n, 1};
    }

    ////////////////////////////////////////////////////////////////////////////////
    // cnl::gcd

#if defined(__cpp_lib_gcd)
    template<typename Numerator, typename Denominator>
    constexpr auto gcd(fraction<Numerator, Denominator> const& f) {
        return std::gcd(f.numerator, f.denominator);
    }

    ////////////////////////////////////////////////////////////////////////////////
    // cnl::reduce

    template<typename Numerator, typename Denominator>
    constexpr auto reduce(fraction<Numerator, Denominator> const& f) {
        return make_fraction(f.numerator / gcd(f), f.denominator / gcd(f));
    }
#endif

    ////////////////////////////////////////////////////////////////////////////////
    // cnl::fraction operators

    // cnl::fraction arithmetic
    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator+(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(make_fraction(
            lhs.numerator*rhs.denominator+rhs.numerator*lhs.denominator, lhs.denominator*rhs.denominator))
    {
        return make_fraction(
                lhs.numerator*rhs.denominator+rhs.numerator*lhs.denominator, lhs.denominator*rhs.denominator);
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator-(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(make_fraction(
            lhs.numerator*rhs.denominator-rhs.numerator*lhs.denominator, lhs.denominator*rhs.denominator))
    {
        return make_fraction(
                lhs.numerator*rhs.denominator-rhs.numerator*lhs.denominator, lhs.denominator*rhs.denominator);
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator*(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(make_fraction(lhs.numerator*rhs.numerator, lhs.denominator*rhs.denominator))
    {
        return make_fraction(lhs.numerator*rhs.numerator, lhs.denominator*rhs.denominator);
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator/(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(make_fraction(lhs.numerator*rhs.denominator, lhs.denominator*rhs.numerator))
    {
        return make_fraction(lhs.numerator*rhs.denominator, lhs.denominator*rhs.numerator);
    }

    // cnl::fraction comparison
    namespace _impl {
        template<typename Numerator, typename Denominator>
        constexpr auto one(fraction<Numerator, Denominator> const& f)
        -> decltype(f.numerator==f.denominator)
        {
            return f.numerator==f.denominator;
        }
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator==(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(_impl::one(lhs/rhs))
    {
        return _impl::one(lhs/rhs);
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator!=(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(!(lhs==rhs))
    {
        return !(lhs==rhs);
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator<(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(_impl::one(lhs/rhs))
    {
        return lhs.numerator*rhs.denominator<rhs.numerator*lhs.denominator;
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator>(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(_impl::one(lhs/rhs))
    {
        return lhs.numerator*rhs.denominator>rhs.numerator*lhs.denominator;
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator<=(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(_impl::one(lhs/rhs))
    {
        return lhs.numerator*rhs.denominator<=rhs.numerator*lhs.denominator;
    }

    template<typename LhsNumerator, typename LhsDenominator, typename RhsNumerator, typename RhsDenominator>
    constexpr auto operator>=(
            fraction<LhsNumerator, LhsDenominator> const& lhs,
            fraction<RhsNumerator, RhsDenominator> const& rhs)
    -> decltype(_impl::one(lhs/rhs))
    {
        return lhs.numerator*rhs.denominator>=rhs.numerator*lhs.denominator;
    }

    // cnl::fraction free functions
    using std::to_string;

    template<typename N, typename D>
    std::string to_string(fraction<N, D> const& f)
    {
        return to_string(static_cast<long double>(f));
//        auto const numerator_string = to_string(f.numerator);
//        auto const denominator_string = to_string(f.denominator);
//
//        auto const total_length = numerator_string.length() + 1 + denominator_string.length();
//        auto fraction_string {std::string{}};
//        fraction_string.reserve(total_length);
//
//        fraction_string = numerator_string;
//        fraction_string += '/';
//        fraction_string += denominator_string;
//        return fraction_string;
    }

    template<typename N, typename D>
    fraction<N, D> abs(fraction<N, D> const& f)
    {
        return fraction<N, D>{abs(f.numerator), abs(f.denominator)};
    }
}

#endif  // CNL_FRACTION_H
