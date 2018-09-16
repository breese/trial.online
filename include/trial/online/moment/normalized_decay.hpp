#ifndef TRIAL_ONLINE_MOMENT_NORMALIZED_DECAY_HPP
#define TRIAL_ONLINE_MOMENT_NORMALIZED_DECAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
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

template <typename T, moment::type Moment, typename...>
class basic_normalized_decay;

//! @brief Exponential smoothing with compensation for bias towards the initial value.
//!
//! See http://breese.github.io/2015/10/26/on-average.html

template <typename T, typename MeanRatio>
class basic_normalized_decay<T, with_mean, MeanRatio>
    : basic_decay<T, with_mean, MeanRatio>
{
    using super = basic_decay<T, with_mean, MeanRatio>;

public:
    using typename super::value_type;

    void clear();
    value_type value() const;
    void push(value_type);

protected:
    value_type normalization = value_type(0);
};

template <typename T, typename MeanRatio>
using normalized_decay = basic_normalized_decay<T, with_mean, MeanRatio>;

} // namespace moment
} // namespace online
} // namespace trial

#include <trial/online/moment/detail/normalized_decay.ipp>

#endif // TRIAL_ONLINE_MOMENT_NORMALIZED_DECAY_HPP
