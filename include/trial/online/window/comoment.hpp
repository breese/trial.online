#ifndef TRIAL_ONLINE_WINDOW_COMOMENT_HPP
#define TRIAL_ONLINE_WINDOW_COMOMENT_HPP

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
#include <trial/online/with.hpp>

namespace trial
{
namespace online
{
namespace window
{

template <typename T, std::size_t Window, online::with Moment>
class basic_comoment;

template <typename T, std::size_t Window>
class basic_comoment<T, Window, with::variance>
{
public:
    using value_type = T;
    using size_type = std::size_t;
    
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");

    basic_comoment() noexcept;

    void clear() noexcept;
    void push(value_type first, value_type second) noexcept;

    size_type size() const noexcept;
    value_type variance() const noexcept;
    value_type unbiased_variance() const noexcept;

private:
    value_type cosum() const noexcept;

private:
    std::pair<value_type, value_type> storage[Window];
    circular_span<decltype(storage)> window;
    struct
    {
        value_type x = value_type(0);
        value_type y = value_type(0);
        value_type xy = value_type(0);
    } sum;
};

// Convenience

template <typename T, std::size_t Window>
using covariance = basic_comoment<T, Window, with::variance>;

} // namespace window
} // namespace online
} // namespace trial

#include <trial/online/window/detail/comoment.ipp>

#endif // TRIAL_ONLINE_WINDOW_COMOMENT_HPP
