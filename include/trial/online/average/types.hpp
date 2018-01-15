#ifndef TRIAL_ONLINE_AVERAGE_TYPES_HPP
#define TRIAL_ONLINE_AVERAGE_TYPES_HPP

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

enum moment_type
{
    with_mean = 1,
    with_variance = 2
};

} // namespace average
} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_AVERAGE_TYPES_HPP
