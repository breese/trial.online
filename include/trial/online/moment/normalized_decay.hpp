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

#include <ratio>
#include <trial/online/detail/type_traits.hpp>
#include <trial/online/moment/types.hpp>

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
{
protected:
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");
    static_assert(detail::is_ratio<MeanRatio>::value, "MeanRatio must be a ratio");

public:
    using value_type = T;

    void clear();
    value_type value() const;
    void push(value_type);

protected:
    static constexpr value_type mean_factor = { MeanRatio::num / value_type(MeanRatio::den) };
    value_type mean = value_type(0);
    value_type normalization = value_type(0);
};

template <typename T, typename MeanRatio, typename VarRatio>
class basic_normalized_decay<T, with_variance, MeanRatio, VarRatio>
    : public basic_normalized_decay<T, with_mean, MeanRatio>
{
protected:
    using super = basic_normalized_decay<T, with_mean, MeanRatio>;

public:
    using typename super::value_type;

    void clear();
    using super::value;
    value_type variance() const;
    void push(value_type);

protected:
    static constexpr value_type var_factor = { VarRatio::num / value_type(VarRatio::den) };
    struct
    {
        value_type variance = value_type(0);
    } sum;
    value_type normalization = value_type(0);
};

// Convenience

template <typename T, typename MeanRatio>
using normalized_decay = basic_normalized_decay<T, with_mean, MeanRatio>;

template <typename T, typename MeanRatio, typename VarRatio>
using normalized_decay_variance = basic_normalized_decay<T, with_variance, MeanRatio, VarRatio>;

} // namespace moment
} // namespace online
} // namespace trial

#include <trial/online/moment/detail/normalized_decay.ipp>

#endif // TRIAL_ONLINE_MOMENT_NORMALIZED_DECAY_HPP
