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

template <typename T, typename MR>
void basic_decay<T, with_mean, MR>::clear()
{
    mean = value_type(0);
}

template <typename T, typename MR>
auto basic_decay<T, with_mean, MR>::value() const -> value_type
{
    return mean;
}

template <typename T, typename MR>
void basic_decay<T, with_mean, MR>::push(value_type input)
{
    const value_type one(1);
    mean = mean_factor * input + (one - mean_factor) * mean;
}

} // namespace moment
} // namespace online
} // namespace trial
