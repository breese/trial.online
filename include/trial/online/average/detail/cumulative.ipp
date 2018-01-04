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
void cumulative<T>::clear()
{
    mean = value_type(0);
    count = size_type(0);
}

template <typename T>
auto cumulative<T>::size() const -> size_type
{
    return count;
}

template <typename T>
auto cumulative<T>::value() const -> value_type
{
    return mean;
}

template <typename T>
void cumulative<T>::push(value_type input)
{
    ++count;
    mean += (input - mean) / T(count);
}

} // namespace average
} // namespace online
} // namespace trial
