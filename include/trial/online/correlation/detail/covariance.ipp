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

template <typename T, template <typename, moment::type> class Avg>
auto basic_covariance<T, Avg>::size() const -> size_type
{
    return x_moment.size();
}

template <typename T, template <typename, moment::type> class Avg>
void basic_covariance<T, Avg>::clear()
{
    x_moment.clear();
    y_moment.clear();
    co_moment = value_type(0);
}

template <typename T, template <typename, moment::type> class Avg>
void basic_covariance<T, Avg>::push(value_type x, value_type y)
{
    x_moment.push(x);
    // Using new x moment and old y moment
    co_moment += (x - x_moment.value()) * (y - y_moment.value());
    y_moment.push(y);
}

template <typename T, template <typename, moment::type> class Avg>
auto basic_covariance<T, Avg>::value() const -> value_type
{
    if (size() > 0)
        return co_moment / size();
    return value_type(0);
}

template <typename T, template <typename, moment::type> class Avg>
auto basic_covariance<T, Avg>::unbiased_value() const -> value_type
{
    // With Bessel's correction
    if (size() > 1)
        return co_moment / (size() - 1);
    return value_type(0);
}

} // namespace correlation
} // namespace online
} // namespace trial
