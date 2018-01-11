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
namespace average
{

//-----------------------------------------------------------------------------
// Average without variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_cumulative<T, false>::clear()
{
    mean = value_type(0);
    count = size_type(0);
}

template <typename T>
auto basic_cumulative<T, false>::size() const -> size_type
{
    return count;
}

template <typename T>
auto basic_cumulative<T, false>::value() const -> value_type
{
    return mean;
}

template <typename T>
void basic_cumulative<T, false>::push(value_type input)
{
    ++count;
    mean += (input - mean) / T(count);
}

//-----------------------------------------------------------------------------
// Average with variance
//-----------------------------------------------------------------------------

template <typename T>
void basic_cumulative<T, true>::clear()
{
    mean = value_type(0);
    numerator = value_type(0);
    count = size_type(0);
}

template <typename T>
auto basic_cumulative<T, true>::size() const -> size_type
{
    return count;
}

template <typename T>
auto basic_cumulative<T, true>::value() const -> value_type
{
    return mean;
}

template <typename T>
auto basic_cumulative<T, true>::variance() const -> value_type
{
    if (count > 0)
        return numerator / count;
    return value_type(0);
}

template <typename T>
void basic_cumulative<T, true>::push(value_type input)
{
    ++count;
    if (count > 1)
    {
        const auto diff = input - mean;
        mean += diff / count;
        numerator += diff * (input - mean);
    }
    else
    {
        mean = input;
        numerator = value_type(0);
    }
}

} // namespace average
} // namespace online
} // namespace trial
