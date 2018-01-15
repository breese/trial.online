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
#include <trial/online/detail/type_traits.hpp>

namespace trial
{
namespace online
{
namespace moment
{

template <typename T, typename Smoothing>
class exponential
{
public:
    using value_type = T;

    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");
    static_assert(detail::is_ratio<Smoothing>::value, "Smoothing factor must be a ratio");

    exponential();

    void clear();
    value_type value() const;
    void push(value_type value);

private:
    static constexpr value_type smoothing_factor = { Smoothing::num / value_type(Smoothing::den) };
    value_type average;
    value_type normalization;
};

} // namespace moment
} // namespace online
} // namespace trial

#include <trial/online/moment/detail/exponential.ipp>

#endif // TRIAL_ONLINE_MOMENT_EXPONENTIAL_HPP
