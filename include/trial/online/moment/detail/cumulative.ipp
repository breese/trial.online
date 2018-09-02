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
namespace moment
{

//-----------------------------------------------------------------------------
// Average without variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_cumulative<T, with_mean>::clear()
{
    mean = value_type(0);
    count = size_type(0);
}

template <typename T>
auto basic_cumulative<T, with_mean>::size() const -> size_type
{
    return count;
}

template <typename T>
auto basic_cumulative<T, with_mean>::value() const -> value_type
{
    return mean;
}

template <typename T>
void basic_cumulative<T, with_mean>::push(value_type input)
{
    ++count;
    mean += (input - mean) / value_type(count);
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_cumulative<T, with_variance>::clear()
{
    mean.clear();
    numerator = value_type(0);
}

template <typename T>
auto basic_cumulative<T, with_variance>::size() const -> size_type
{
    return mean.size();
}

template <typename T>
auto basic_cumulative<T, with_variance>::value() const -> value_type
{
    return mean.value();
}

template <typename T>
auto basic_cumulative<T, with_variance>::variance() const -> value_type
{
    const auto count = size();
    return (count > 0)
        ? numerator / value_type(count)
        : value_type(0);
}

template <typename T>
auto basic_cumulative<T, with_variance>::unbiased_variance() const -> value_type
{
    const auto count = size();
    return (count > 1)
        ? numerator / value_type(count - 1)
        : value_type(0);
}

template <typename T>
void basic_cumulative<T, with_variance>::push(value_type input)
{
    if (size() > 0)
    {
        const auto diff = input - mean.value();
        mean.push(input);
        numerator += diff * (input - mean.value());
    }
    else
    {
        mean.push(input);
    }
}

} // namespace moment
} // namespace online
} // namespace trial
