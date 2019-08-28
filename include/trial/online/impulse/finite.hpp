#ifndef TRIAL_ONLINE_IMPULSE_FINITE_HPP
#define TRIAL_ONLINE_IMPULSE_FINITE_HPP

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

// Finite Impulse Response filter

template <typename T>
class finite
{
public:
    using value_type = T;
    using size_type = std::size_t;

    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

    template <std::size_t P>
    finite(const value_type (&input_coefficients)[P]);
    template <std::size_t P>
    finite(value_type (&&input_coefficients)[P]);

    size_type capacity() const;
    void clear();
    bool empty() const;
    bool full() const;
    value_type value() const;
    void push(value_type);
    size_type size() const;

private:
    using window_type = trial::circular::vector<value_type>;
    window_type input;
    value_type output;
    std::vector<value_type> coefficients;
};

} // namespace impulse
} // namespace online
} // namespace trial

#include <trial/online/impulse/detail/finite.ipp>

#endif // TRIAL_ONLINE_IMPULSE_FINITE_HPP
