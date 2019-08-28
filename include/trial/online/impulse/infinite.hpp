#ifndef TRIAL_ONLINE_IMPULSE_INFINITE_HPP
#define TRIAL_ONLINE_IMPULSE_INFINITE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <vector>
#include <type_traits>
#include <trial/circular/vector.hpp>

namespace trial
{
namespace online
{
namespace impulse
{

// Infinite Impulse Response filter

template <typename T>
class infinite
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

    template <std::size_t P, std::size_t Q>
    infinite(const value_type (&input_coefficients)[P],
             const value_type (&output_coefficients)[Q],
             value_type output_scale = value_type(1));
    template <std::size_t P, std::size_t Q>
    infinite(value_type (&&input_coefficients)[P],
             value_type (&&output_coefficients)[Q],
             value_type output_scale = value_type(1));

    void clear();
    bool empty() const;
    value_type value() const;
    void push(value_type);

private:
    using window_type = trial::circular::vector<value_type>;
    struct
    {
        window_type window;
        std::vector<value_type> coefficients;
    } input;
    struct
    {
        window_type window;
        value_type scale;
        std::vector<value_type> coefficients;
    } output;
};

} // namespace impulse
} // namespace online
} // namespace trial

#include <trial/online/impulse/detail/infinite.ipp>

#endif // TRIAL_ONLINE_IMPULSE_INFINITE_HPP
