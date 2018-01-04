#ifndef TRIAL_ONLINE_AVERAGE_CUMULATIVE_VARIANCE_HPP
#define TRIAL_ONLINE_AVERAGE_CUMULATIVE_VARIANCE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <type_traits>

namespace trial
{
namespace online
{
namespace average
{

template <typename T>
class cumulative_variance
{
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear();
    size_type size() const;
    void push(value_type);
    value_type value() const;
    value_type variance() const;

private:
    value_type mean = value_type(0);
    value_type numerator = value_type(0);
    size_type count = size_type(0);
};

} // namespace average
} // namespace online
} // namespace trial

#include <trial/online/average/detail/cumulative_variance.ipp>

#endif // TRIAL_ONLINE_AVERAGE_CUMULATIVE_VARIANCE_HPP
