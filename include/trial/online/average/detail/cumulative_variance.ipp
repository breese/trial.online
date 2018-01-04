///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
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

template <typename T>
void cumulative_variance<T>::clear()
{
    mean = value_type(0);
    numerator = value_type(0);
    count = size_type(0);
}

template <typename T>
auto cumulative_variance<T>::size() const -> size_type
{
    return count;
}

template <typename T>
void cumulative_variance<T>::push(value_type input)
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

template <typename T>
auto cumulative_variance<T>::value() const -> value_type
{
    return mean;
}

template <typename T>
auto cumulative_variance<T>::variance() const -> value_type
{
    if (count > 0)
        return numerator / count;
    return value_type(0);
}

} // namespace average
} // namespace online
} // namespace trial
