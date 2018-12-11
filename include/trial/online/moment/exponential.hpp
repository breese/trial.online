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

#include <ratio>
#include <trial/online/decay/moment.hpp>

namespace trial
{
namespace online
{
namespace moment
{

template <typename T, typename MeanRatio>
class exponential
    : public decay::basic_moment<T, with::mean>
{
    using super = decay::basic_moment<T, with::mean>;

public:
    using typename super::value_type;

    exponential()
        : super(MeanRatio::num / value_type(MeanRatio::den))
    {}

    using super::clear;
    using super::push;
    using super::value;
};

} // namespace moment
} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_MOMENT_EXPONENTIAL_HPP
