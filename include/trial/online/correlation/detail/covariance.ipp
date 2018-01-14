///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
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
namespace correlation
{

template <typename T, template <typename, bool> class Avg>
auto basic_covariance<T, Avg>::size() const -> size_type
{
    return average_x.size();
}

template <typename T, template <typename, bool> class Avg>
void basic_covariance<T, Avg>::clear()
{
    average_x.clear();
    average_y.clear();
    cov = value_type(0);
}

template <typename T, template <typename, bool> class Avg>
void basic_covariance<T, Avg>::push(value_type x, value_type y)
{
    average_x.push(x);
    const auto previous_average_y = average_y.value();
    average_y.push(y);
    cov += (x - average_x.value()) * (y - previous_average_y);
}

template <typename T, template <typename, bool> class Avg>
auto basic_covariance<T, Avg>::value() const -> value_type
{
    if (size() > 1)
        return cov / (size() - 1);
    return value_type(0);
}

template <typename T, template <typename, bool> class Avg>
auto basic_covariance<T, Avg>::normalized_value() const -> value_type
{
    if (size() > 0)
        return cov / size();
    return value_type(0);
}

} // namespace correlation
} // namespace online
} // namespace trial
