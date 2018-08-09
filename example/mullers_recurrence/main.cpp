#include <cnl/all.h>

#include <iostream>
#include <string>
#include <type_traits>

using namespace cnl::literals;

template<typename Scalar>
auto divide(Scalar const& n, Scalar const& d)
-> typename std::enable_if<std::is_floating_point<Scalar>::value, decltype(n / d)>::type {
    return n / d;
}

template<typename NumeratorRep, int NumeratorExponent, typename DenominatorRep, int DenominatorExponent>
auto divide(
        cnl::fixed_point<NumeratorRep, NumeratorExponent> const& n,
        cnl::fixed_point<DenominatorRep, DenominatorExponent> const& d) {
    return cnl::quotient(n, d);
}

// from: https://medium.com/@bellmar/is-cobol-holding-you-hostage-with-math-5498c0eb428b
template<typename Scalar>
auto iterate(Scalar const& y, Scalar const& z)
{
    return Scalar{108.} - Scalar{divide(Scalar{815.} - Scalar{divide(Scalar{1500.}, z)}, y)};
}

template<typename Scalar>
void test(char const* const title)
{
    using std::cout;
    cout << title << '\n';
    auto print_row = [&](int iteration, Scalar const& value) {
        cout << iteration << '\t' << cnl::to_string(value) << '\n';
    };

    Scalar previous = 4.;
    print_row(0, previous);

    Scalar current = 4.25;
    print_row(1, current);

    auto divergence_iteration = 0;
    for (auto n = 2; n<100; ++n) {
        Scalar const next = iterate(current, previous);
        if (next==current) {
            break;
        }
        previous = current;
        current = next;

        if (!divergence_iteration && cnl::abs(current-5.) > cnl::abs(previous-5.)) {
            divergence_iteration = n;
        }

        print_row(n, current);
    }

    cout << "converged until " << divergence_iteration << "\n\n";
}

int main()
{
    test<float>("single precision floaint point");
    test<double>("double precision floaint point");
    test<long double>("extended precision floaint point");
    test<cnl::fixed_point<cnl::int64, -52>>("Q25.38");
    test<cnl::fixed_point<cnl::elastic_integer<49>, -38>>("Q11.38");
    test<cnl::static_number<42, -30>>("cnl::static_number<42, -30>");
//    test<cnl::fractional<cnl::static_number<42, -30>>("cnl::static_number<42, -30>");
}
