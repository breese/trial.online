#ifndef TRIAL_ONLINE_DETAIL_TYPE_TRAITS_HPP
#define TRIAL_ONLINE_DETAIL_TYPE_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace trial
{
namespace online
{
namespace detail
{

template <typename T, typename = int>
struct is_ratio : public std::false_type {};

template <typename T>
struct is_ratio<T, decltype((void)T::num, (void)T::den, 0)> : public std::true_type {};

} // namespace detail
} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_DETAIL_TYPE_TRAITS_HPP
