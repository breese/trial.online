#ifndef TRIAL_ONLINE_CUMULATIVE_CORRELATION_HPP
#define TRIAL_ONLINE_CUMULATIVE_CORRELATION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// https://en.wikipedia.org/wiki/Pearson_correlation_coefficient

#include <trial/online/cumulative/comoment.hpp>

namespace trial
{
namespace online
{
namespace cumulative
{

template <typename T>
class correlation
{
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear() noexcept;
    void push(value_type, value_type) noexcept;

    size_type size() const noexcept;
    value_type value() const noexcept;

private:
    basic_comoment<value_type, with::variance> co_moment;
    basic_moment<value_type, with::variance> x_moment;
    basic_moment<value_type, with::variance> y_moment;
};

} // namespace cumulative
} // namespace online
} // namespace trial

#include <trial/online/cumulative/detail/correlation.ipp>

#endif // TRIAL_ONLINE_CUMULATIVE_CORRELATION_HPP
