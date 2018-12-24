#ifndef TRIAL_ONLINE_CUMULATIVE_TREND_HPP
#define TRIAL_ONLINE_CUMULATIVE_TREND_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/cumulative/moment.hpp>

namespace trial
{
namespace online
{
namespace cumulative
{

template <typename T, online::with Moment>
class basic_trend;

template <typename T>
class basic_trend<T, with::mean>
{
public:
    using value_type = T;
    using size_type = std::size_t;

    void clear() noexcept;
    void push(value_type value) noexcept;

    size_type size() const noexcept;
    value_type value() const noexcept;

private:
    cumulative::basic_moment<value_type, with::mean> center;
    cumulative::basic_moment<value_type, with::mean> grand;
};

template <typename T>
using trend = basic_trend<T, with::mean>;

} // namespace cumulative
} // namespace online
} // namespace trial

#include <trial/online/cumulative/detail/trend.ipp>

#endif // TRIAL_ONLINE_CUMULATIVE_TREND_HPP
