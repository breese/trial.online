#ifndef TRIAL_ONLINE_AVERAGE_ARITHMETIC_VARIANCE_HPP
#define TRIAL_ONLINE_AVERAGE_ARITHMETIC_VARIANCE_HPP

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
#include <boost/circular_buffer.hpp>

namespace trial
{
namespace online
{
namespace average
{

template <typename T, std::size_t N>
class arithmetic_variance
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(N > 0, "N must be larger than zero");
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

    arithmetic_variance();

    size_type capacity() const;
    void clear();
    bool empty() const;
    bool full() const;
    value_type mean() const;
    void push(value_type value);
    size_type size() const;
    value_type variance() const;

private:
    value_type delta(value_type, value_type);

private:
    using window_type = boost::circular_buffer<value_type>;
    window_type window;
    value_type sum;
    value_type numerator;
};

} // namespace average
} // namespace online
} // namespace trial

#include <trial/online/average/detail/arithmetic_variance.ipp>

#endif // TRIAL_ONLINE_AVERAGE_ARITHMETIC_VARIANCE_HPP
