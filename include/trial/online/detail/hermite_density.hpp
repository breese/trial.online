#ifndef TRIAL_ONLINE_DETAIL_HERMITE_DENSITY_HPP
#define TRIAL_ONLINE_DETAIL_HERMITE_DENSITY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// Stephanou, Varughese, and Macdonald, "Sequential quantiles via Hermite
//   series density estimation", Electronic Journal of Statistics, 11(1),
//   p. 570-607, 2017

#include <cstddef>
#include <limits>
#include <type_traits>
#include <trial/online/with.hpp>

namespace trial
{
namespace online
{
namespace detail
{

template <typename, std::size_t Precision, online::with, typename Moment>
class hermite_density;

template <typename T, std::size_t Precision, typename Moment>
class hermite_density<T, Precision, with::density, Moment>
{
    static_assert(Precision > 0, "Precision must be larger than zero");
    static_assert(std::is_floating_point<T>::value, "T must be an floating-point type");
    static_assert(std::is_same<T, typename Moment::value_type>::value, "Use same value_type");

public:
    using value_type = T;
    using size_type = std::size_t;

    hermite_density() noexcept;
    hermite_density(const hermite_density&) noexcept = default;
    hermite_density(hermite_density&&) noexcept = default;
    hermite_density& operator= (const hermite_density&) noexcept = default;
    hermite_density& operator= (hermite_density&&) noexcept = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    value_type at(value_type position) const noexcept;
    value_type lower() const noexcept;
    value_type upper() const noexcept;

protected:
    value_type weighted(value_type) const noexcept;

protected:
    struct
    {
        value_type factorial;
        value_type alpha;
    } constant[Precision + 1];

    struct
    {
        Moment coefficients[Precision + 1];
        value_type lower;
        value_type upper;
    } member;
};

template <typename T, std::size_t Precision, typename Moment>
class hermite_density<T, Precision, with::cumulation, Moment>
    : protected hermite_density<T, Precision, with::density, Moment>
{
    using super = hermite_density<T, Precision, with::density, Moment>;

public:
    using typename super::value_type;
    using typename super::size_type;

    hermite_density() noexcept;
    hermite_density(const hermite_density&) noexcept = default;
    hermite_density(hermite_density&&) noexcept = default;
    hermite_density& operator= (const hermite_density&) noexcept = default;
    hermite_density& operator= (hermite_density&&) noexcept = default;

    using super::clear;
    using super::push;
    using super::at;
    value_type until(value_type position) const noexcept;
    using super::lower;
    using super::upper;

protected:
    struct
    {
        value_type positive[Precision / 2 + 1];
        value_type negative[Precision / 2 + 1];
        value_type denominator[Precision / 2 + 1];
    } constant[Precision + 1];
};

} // namespace detail
} // namespace online
} // namespace trial

#include <trial/online/detail/hermite_density.ipp>

#endif // TRIAL_ONLINE_DETAIL_HERMITE_DENSITY_HPP
