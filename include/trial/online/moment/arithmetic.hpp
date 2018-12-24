#ifndef TRIAL_ONLINE_MOMENT_ARITHMETIC_HPP
#define TRIAL_ONLINE_MOMENT_ARITHMETIC_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/window/moment.hpp>

namespace trial
{
namespace online
{
namespace moment
{

// Deprecated.
//
// Use window::moment instead.

template <typename T, std::size_t N>
using arithmetic = window::basic_moment<T, N, with::mean>;

template <typename T, std::size_t N>
using arithmetic_variance = window::basic_moment<T, N, with::variance>;

} // namespace moment
} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_MOMENT_ARITHMETIC_HPP
