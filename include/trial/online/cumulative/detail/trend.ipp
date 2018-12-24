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
namespace cumulative
{

template <typename T>
void basic_trend<T, with::mean>::clear() noexcept
{
    center.clear();
    grand.clear();
}

template <typename T>
void basic_trend<T, with::mean>::push(value_type input) noexcept
{
    center.push(input);
    grand.push(center.mean());
}

template <typename T>
auto basic_trend<T, with::mean>::size() const noexcept -> size_type
{
    return center.size();
}

template <typename T>
auto basic_trend<T, with::mean>::value() const noexcept -> value_type
{
    // The mean and grand mean are stable compared to the input data.
    // The mean lags behind the trending data by half, and grand mean lags
    // behind mean by half, which gives us the points (mean, N/2) and
    // (grand mean, N/4) to extrapolate the point (prediction, N) from.

    return center.mean() + value_type(2) * (center.mean() - grand.mean());
}

} // namespace cumulative
} // namespace online
} // namespace trial
