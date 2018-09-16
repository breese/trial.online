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
void basic_normalized_decay<T, with_mean, MR>::clear()
{
    super::clear();
    normalization = value_type(0);
}

template <typename T, typename MR>
auto basic_normalized_decay<T, with_mean, MR>::value() const -> value_type
{
    return (normalization > value_type(0))
        ? super::value() / normalization
        : value_type(0);
}

template <typename T, typename MR>
void basic_normalized_decay<T, with_mean, MR>::push(value_type input)
{
    super::push(input);
    const value_type one(1);
    normalization = super::mean_factor + (one - super::mean_factor) * normalization;
}

} // namespace moment
} // namespace online
} // namespace trial
