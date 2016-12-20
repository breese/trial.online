#ifndef TRIAL_ONLINE_AVERAGE_EXPONENTIAL_HPP
#define TRIAL_ONLINE_AVERAGE_EXPONENTIAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace trial
{
namespace online
{
namespace average
{

template <typename T>
class exponential
{
public:
    using value_type = T;

    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

    exponential(value_type smoothing_factor);

    void clear();
    value_type mean() const;
    void push(value_type value);

private:
    static constexpr value_type zero = value_type(0);
    static constexpr value_type one = value_type(1);
    const value_type smoothing_factor;
    value_type average;
    value_type normalization;
};

} // namespace average
} // namespace online
} // namespace trial

#include <trial/online/average/detail/exponential.ipp>

#endif // TRIAL_ONLINE_AVERAGE_EXPONENTIAL_HPP
