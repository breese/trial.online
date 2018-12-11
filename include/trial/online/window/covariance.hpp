#ifndef TRIAL_ONLINE_WINDOW_COVARIANCE_HPP
#define TRIAL_ONLINE_WINDOW_COVARIANCE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/circular_span.hpp>
#include <trial/online/window/moment.hpp>

namespace trial
{
namespace online
{
namespace window
{

template <typename T, std::size_t Window>
class covariance
{
public:
    using value_type = T;
    using size_type = std::size_t;
    
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

    covariance();

    void clear();
    void push(value_type first, value_type second);

    size_type size() const;
    // O(W)
    value_type value() const;
    value_type unbiased_value() const;

private:
    value_type sum() const;

private:
    basic_moment<value_type, Window, with::mean> x_moment;
    basic_moment<value_type, Window, with::mean> y_moment;
    std::pair<value_type, value_type> storage[Window];
    circular_span<decltype(storage)> window;
};

} // namespace window
} // namespace online
} // namespace trial

#include <trial/online/window/detail/covariance.ipp>

#endif // TRIAL_ONLINE_WINDOW_COVARIANCE_HPP
