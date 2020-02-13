///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <trial/online/detail/math.hpp>
#ifndef NDEBUG
#include <boost/math/special_functions/gamma.hpp>
#include <trial/online/detail/functional.hpp>
#endif

namespace trial
{
namespace online
{
namespace detail
{

//-----------------------------------------------------------------------------
// With density
//-----------------------------------------------------------------------------

template <typename T, std::size_t P, typename M>
hermite_density<T, P, with::density, M>::hermite_density() noexcept
    : member{{}, std::numeric_limits<value_type>::max(), std::numeric_limits<value_type>::min()}
{
    const value_type root_pi = boost::math::constants::root_pi<value_type>();
    // Calculate constants used in equations
    for (size_type k = 0; k <= P; ++k)
    {
        constant[k].factorial = boost::math::factorial<value_type>(k);

        // Alpha constants listed after equation 7 on page 575:
        //   alpha[k] = sqrt(pi) / (2^{k-1} k!)
        constant[k].alpha = root_pi
            / (std::pow(value_type(2), k - value_type(1)) * constant[k].factorial);
    }
}

template <typename T, std::size_t P, typename M>
void hermite_density<T, P, with::density, M>::push(value_type input) noexcept
{
    if (input < member.lower)
        member.lower = input;
    if (input > member.upper)
        member.upper = input;

    // Equation 10 page 576
    const value_type weighted_input = weighted(input);

    value_type h0 = value_type(1);
    member.coefficients[0].push(constant[0].alpha * weighted_input * h0);

    value_type h1 = value_type(2) * input;
    member.coefficients[1].push(constant[1].alpha * weighted_input * h1);

    for (size_type k = 2; k <= P; ++k)
    {
        const value_type h = math::hermite_next(k - 1, input, h1, h0);
        member.coefficients[k].push(constant[k].alpha * weighted_input * h);
        h0 = h1;
        h1 = h;
    }
}

template <typename T, std::size_t P, typename M>
auto hermite_density<T, P, with::density, M>::at(value_type position) const noexcept -> value_type
{
    // Equation 11 page 576
    const value_type weighted_position = weighted(position);

    value_type h0 = value_type(1);
    value_type result = member.coefficients[0].mean() * weighted_position * h0;

    value_type h1 = value_type(2) * position;
    result += member.coefficients[1].mean() * weighted_position * h1;

    for (size_type k = 2; k <= P; ++k)
    {
        const value_type h = math::hermite_next(k - 1, position, h1, h0);
        result += member.coefficients[k].mean() * weighted_position * h;
        h0 = h1;
        h1 = h;
    }
    return result;
}

template <typename T, std::size_t P, typename M>
auto hermite_density<T, P, with::density, M>::lower() const noexcept -> value_type
{
    return member.upper >= member.lower ? member.lower : value_type(0);
}

template <typename T, std::size_t P, typename M>
auto hermite_density<T, P, with::density, M>::upper() const noexcept -> value_type
{
    return member.upper >= member.lower ? member.upper : value_type(0);
}

template <typename T, std::size_t P, typename M>
auto hermite_density<T, P, with::density, M>::weighted(value_type input) const noexcept -> value_type
{
    const value_type half_input_squared = boost::math::constants::half<value_type>() * input * input;

    return std::exp(-half_input_squared)
        / boost::math::constants::root_two_pi<value_type>();
}

//-----------------------------------------------------------------------------
// With cumulation
//-----------------------------------------------------------------------------

template <typename T, std::size_t P, typename M>
hermite_density<T, P, with::cumulation, M>::hermite_density() noexcept
{
    const value_type root_pi = boost::math::constants::root_pi<value_type>();
    // Calculate more constants used in equations
    for (size_type k = 0; k <= P; ++k)
    {
        size_type m = 0;
        for (; m <= k / 2; ++m)
        {
            // numerator = 2^{3k/2 - 3m - 1}
            const value_type numerator = std::pow(value_type(2), value_type(1.5) * k - value_type(3 * m) - value_type(1));

            // -1^m numerator
            constant[k].positive[m] = (m % 2 == 0) ? numerator : -numerator;

            // -1^{k-m} numerator
            constant[k].negative[m] = ((k - m) % 2 == 0) ? numerator : -numerator;

            // m! (k - 2m)! sqrt(pi)
            constant[k].denominator[m] = super::constant[m].factorial * super::constant[k - 2 * m].factorial * root_pi;
        }
    }
}

template <typename T, std::size_t P, typename M>
auto hermite_density<T, P, with::cumulation, M>::until(value_type position) const noexcept -> value_type
{
    const value_type root_pi = boost::math::constants::root_pi<value_type>();

    // Equation 13 page 579
    //
    // Pre-calculate (non-normalized) gamma values using recurrence relation:
    //
    //   Gamma(s+1, z) = s Gamma(s, z) + z^s exp(-z)
    //
    // where s = (k + 1) / 2 for k = {0, 1, ..., Precision}, and z = 1/2 x^2
    //
    // As boost::math::tgamma is slow, use these relations to calculate first Gamma values:
    //
    //   Gamma(1/2, z) = sqrt(pi) (1 - erf(sqrt(z))
    //   Gamma(2/2, z) = exp(-z)

    const value_type half_position_squared = boost::math::constants::half<value_type>() * position * position;
    const value_type exp_constant = std::exp(-half_position_squared);
    const value_type initial_x1 = std::sqrt(half_position_squared);
    value_type x1 = 1;
    const value_type initial_x2 = half_position_squared;
    value_type x2 = initial_x2;

    value_type upper_gamma_cache[2 * P];
    upper_gamma_cache[0] = root_pi * (value_type(1) - std::erf(initial_x1));
    upper_gamma_cache[1] = exp_constant;

    for (size_type k = 1; k < P; ++k)
    {
        const size_type s1 = 2 * k - 1;
        const size_type s2 = 2 * k;

        upper_gamma_cache[s1 + 1] = math::upper_gamma_next(boost::math::constants::half<value_type>() * s1,
                                                           upper_gamma_cache[s1 - 1],
                                                           x1 * initial_x1,
                                                           exp_constant);
        upper_gamma_cache[s2 + 1] = math::upper_gamma_next(boost::math::constants::half<value_type>() * s2,
                                                           upper_gamma_cache[s2 - 1],
                                                           x2,
                                                           exp_constant);

        x1 = x2; // z^s
        x2 *= initial_x2; // z^{s+1}
    }
#ifndef NDEBUG // Verification
    for (size_type k = 0; k < 2 * P; ++k)
    {
        const value_type upper = boost::math::tgamma<value_type>(value_type(k + 1) / 2,
                                                                 half_position_squared);
        assert(detail::close_to<double>(1e-6, 1e-6)(upper_gamma_cache[k], upper));
    }
#endif

    value_type outer_sum(0);
    if (position >= 0)
    {
        for (size_type k = 0; k <= P; ++k)
        {
            value_type inner_sum(0);
            for (size_type m = 0; m <= k / 2; ++m)
            {
                inner_sum += constant[k].positive[m] * upper_gamma_cache[k - 2 * m] / constant[k].denominator[m];
            }
            outer_sum += super::member.coefficients[k].mean() * super::constant[k].factorial * inner_sum;
        }
        return value_type(1) - outer_sum;
    }
    else
    {
        for (size_type k = 0; k <= P; ++k)
        {
            value_type inner_sum(0);
            for (size_type m = 0; m <= k / 2; ++m)
            {
                inner_sum += constant[k].negative[m] * upper_gamma_cache[k - 2 * m] / constant[k].denominator[m];
            }
            outer_sum += super::member.coefficients[k].mean() * super::constant[k].factorial * inner_sum;
        }
        return outer_sum;
    }
}

} // namespace detail
} // namespace online
} // namespace trial
