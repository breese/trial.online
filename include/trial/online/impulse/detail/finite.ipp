///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <iterator>

namespace trial
{
namespace online
{
namespace impulse
{

template <typename T>
template <std::size_t P>
finite<T>::finite(const value_type (&coefficients)[P])
    : input{P},
      output(),
      coefficients{std::begin(coefficients), std::end(coefficients)}
{
}

template <typename T>
template <std::size_t P>
finite<T>::finite(value_type (&&coefficients)[P])
    : input{P},
      output(),
      coefficients{std::make_move_iterator(std::begin(coefficients)), std::make_move_iterator(std::end(coefficients))}
{
}

template <typename T>
auto finite<T>::capacity() const -> size_type
{
    return input.capacity();
}

template <typename T>
void finite<T>::clear()
{
    input.clear();
}

template <typename T>
bool finite<T>::empty() const
{
    return input.empty();
}

template <typename T>
bool finite<T>::full() const
{
    return input.full();
}

template <typename T>
auto finite<T>::value() const -> value_type
{
    return output;
}

template <typename T>
void finite<T>::push(value_type in)
{
    input.push_front(in);
    output = std::inner_product(input.begin(), input.end(), coefficients.begin(), value_type());
}

template <typename T>
auto finite<T>::size() const -> size_type
{
    return input.size();
}

} // namespace impulse
} // namespace online
} // namespace trial
