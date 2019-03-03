///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace online
{

namespace math
{

// Upper incomplete gamma function:
//   Gamma(s + 1, x) = s Gamma(s, x) + x^s exp(-x)
//
// https://en.wikipedia.org/wiki/Incomplete_gamma_function#Properties

template <typename T>
T upper_gamma_next(T s, T Gn, T xs, T exp_minus_x) noexcept
{
    return s * Gn + xs * exp_minus_x;
}

// Lower incomplete gamma function:
//   gamma(s + 1, x) = s gamma(s, x) - x^s exp(-x)
//
// https://en.wikipedia.org/wiki/Incomplete_gamma_function#Properties

template <typename T>
T lower_gamma_next(T s, T gn, T xs, T exp_minus_x) noexcept
{
    return s * gn - xs * exp_minus_x;
}

// Hermite polynomial:
//   H[n+1](x) = 2 x H[n](x) - 2 n H[n-1](x)
//
// https://en.wikipedia.org/wiki/Hermite_polynomials#Recursion_relation

template <typename T>
T hermite_next(std::size_t n, T x, T Hn, T Hnm1)
{
    return T(2) * (x * Hn - T(n) * Hnm1);
}

} // namespace math
} // namespace online
} // namespace trial
