#ifndef TRIAL_ONLINE_MOMENT_DECAY_HPP
#define TRIAL_ONLINE_MOMENT_DECAY_HPP

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
class basic_decay;

//! @brief Exponential smoothing with compensation for bias towards the initial value.
//!
//! See http://breese.github.io/2015/10/26/on-average.html

template <typename T, typename MeanRatio>
class basic_decay<T, with_mean, MeanRatio>
{
protected:
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");
    static_assert(detail::is_ratio<MeanRatio>::value, "MeanRatio must be a ratio");

public:
    using value_type = T;

    void clear();
    void push(value_type);

    value_type value() const;

protected:
    static constexpr value_type mean_factor = { MeanRatio::num / value_type(MeanRatio::den) };
    value_type mean = value_type(0);
    value_type normalization = value_type(0);
};

// With variance

template <typename T, typename MeanRatio, typename VarRatio>
class basic_decay<T, with_variance, MeanRatio, VarRatio>
    : public basic_decay<T, with_mean, MeanRatio>
{
protected:
    using super = basic_decay<T, with_mean, MeanRatio>;

public:
    using typename super::value_type;

    void clear();
    void push(value_type);

    using super::value;
    value_type variance() const;

protected:
    static constexpr value_type var_factor = { VarRatio::num / value_type(VarRatio::den) };
    struct
    {
        value_type variance = value_type(0);
    } sum;
    value_type normalization = value_type(0);
};

// With skew

template <typename T, typename MeanRatio, typename VarRatio, typename SkewRatio>
class basic_decay<T, with_skew, MeanRatio, VarRatio, SkewRatio>
    : public basic_decay<T, with_variance, MeanRatio, VarRatio>
{
protected:
    using super = basic_decay<T, with_variance, MeanRatio, VarRatio>;

public:
    using typename super::value_type;

    void clear();
    void push(value_type);

    using super::value;
    using super::variance;
    value_type skew() const;

protected:
    static constexpr value_type skew_factor = { SkewRatio::num / value_type(SkewRatio::den) };
    struct
    {
        value_type skew = value_type(0);
    } sum;
    value_type normalization = value_type(0);
};

// Convenience

template <typename T, typename MeanRatio>
using decay = basic_decay<T, with_mean, MeanRatio>;

template <typename T, typename MeanRatio, typename VarRatio = MeanRatio>
using decay_variance = basic_decay<T, with_variance, MeanRatio, VarRatio>;

template <typename T, typename MeanRatio, typename VarRatio = MeanRatio, typename SkewRatio = VarRatio>
using decay_skew = basic_decay<T, with_skew, MeanRatio, VarRatio, SkewRatio>;

} // namespace moment
} // namespace online
} // namespace trial

#include <trial/online/moment/detail/decay.ipp>

#endif // TRIAL_ONLINE_MOMENT_DECAY_HPP
