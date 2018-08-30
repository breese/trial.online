///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <limits>

namespace trial
{
namespace online
{
namespace regression
{

template <typename T, template <typename, moment::type> class Avg>
void basic_linear<T, Avg>::clear()
{
    covariance.clear();
    x_moment.clear();
    y_moment.clear();
}

template <typename T, template <typename, moment::type> class Avg>
auto basic_linear<T, Avg>::size() const -> size_type
{
    assert(x_moment.size() == y_moment.size());

    return x_moment.size();
}

template <typename T, template <typename, moment::type> class Avg>
void basic_linear<T, Avg>::push(value_type x,
                                value_type y)
{
    covariance.push(x, y);
    x_moment.push(x);
    y_moment.push(y);
}

template <typename T, template <typename, moment::type> class Avg>
auto basic_linear<T, Avg>::slope() const -> value_type
{
    const auto divisor = x_moment.variance();
    return (divisor == 0)
        ? value_type(0)
        : covariance.normalized_value() / divisor;
}

template <typename T, template <typename, moment::type> class Avg>
auto basic_linear<T, Avg>::intercept() const -> value_type
{
    return y_moment.value() - slope() * x_moment.value();
}

template <typename T, template <typename, moment::type> class Avg>
auto basic_linear<T, Avg>::correlation() const -> value_type
{
    // Pearson's correlation coefficient
    const value_type variance_product = x_moment.variance() * y_moment.variance();
    return (variance_product < std::numeric_limits<value_type>::epsilon())
        ? value_type(1)
        : covariance.normalized_value() / std::sqrt(variance_product);
}

} // namespace regression
} // namespace online
} // namespace trial
