#ifndef TRIAL_ONLINE_WITH_HPP
#define TRIAL_ONLINE_WITH_HPP

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

enum struct with
{
    mean = 1,
    variance = 2,
    skew = 3
};

} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_WITH_HPP
