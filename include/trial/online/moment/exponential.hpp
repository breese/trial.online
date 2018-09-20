#ifndef TRIAL_ONLINE_MOMENT_EXPONENTIAL_HPP
#define TRIAL_ONLINE_MOMENT_EXPONENTIAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/moment/decay.hpp>

namespace trial
{
namespace online
{
namespace moment
{

template <typename T, typename MeanRatio>
using exponential = basic_decay<T, with_mean, MeanRatio>;

} // namespace moment
} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_MOMENT_EXPONENTIAL_HPP
