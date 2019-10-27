///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace online
{
namespace interim
{
namespace detail
{

//-----------------------------------------------------------------------------
// With mean
//-----------------------------------------------------------------------------

template <typename T, std::size_t Window, online::with UseMoment>
class basic_moment<T, Window, with::mean, UseMoment>
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert((!std::is_same<T, bool>::value), "T cannot be bool");
    static_assert(Window > 0, "Window must be larger than zero");
    static_assert(Window % 2 == 0, "Window must be event");

public:
    using value_type = T;
    using size_type = std::size_t;

    void clear() noexcept;

    void push(value_type) noexcept;

    size_type capacity() const noexcept;
    size_type size() const noexcept;
    bool empty() const noexcept;
    bool full() const noexcept;

    value_type mean() const noexcept;

protected:
    cumulative::basic_moment<value_type, UseMoment> active;
    cumulative::basic_moment<value_type, UseMoment> passive;
};

template <typename T, std::size_t W, online::with UseMoment>
void basic_moment<T, W, with::mean, UseMoment>::clear() noexcept
{
    active.clear();
    passive.clear();
}

template <typename T, std::size_t W, online::with UseMoment>
void basic_moment<T, W, with::mean, UseMoment>::push(value_type input) noexcept
{
    const bool is_active_full = active.size() >= W;
    if (is_active_full)
    {
        std::swap(active, passive);
        active.clear();
    }
    active.push(input);
}

template <typename T, std::size_t W, online::with UseMoment>
auto basic_moment<T, W, with::mean, UseMoment>::capacity() const noexcept -> size_type
{
    return W;
}

template <typename T, std::size_t W, online::with UseMoment>
auto basic_moment<T, W, with::mean, UseMoment>::size() const noexcept -> size_type
{
    return passive.empty() ? active.size() : W;
}

template <typename T, std::size_t W, online::with UseMoment>
bool basic_moment<T, W, with::mean, UseMoment>::empty() const noexcept
{
    return size() == 0;
}

template <typename T, std::size_t W, online::with UseMoment>
bool basic_moment<T, W, with::mean, UseMoment>::full() const noexcept
{
    return (active.size() == W) || !passive.empty();
}

template <typename T, std::size_t W, online::with UseMoment>
auto basic_moment<T, W, with::mean, UseMoment>::mean() const noexcept -> value_type
{
    if (passive.empty())
        return active.mean();

    // Weighted combined mean
    const auto sz = active.size();
    return (passive.mean() * (W - sz) + active.mean() * (2 * sz))
        / value_type(W + sz);
}

//-----------------------------------------------------------------------------
// With variance
//-----------------------------------------------------------------------------

template <typename T, std::size_t N, online::with UseMoment>
class basic_moment<T, N, with::variance, UseMoment>
    : protected basic_moment<T, N, with::mean, UseMoment>
{
    using super = basic_moment<T, N, with::mean, UseMoment>;

    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using typename super::value_type;
    using typename super::size_type;

    using super::clear;
    using super::push;
    using super::capacity;
    using super::empty;
    using super::full;
    using super::mean;
    using super::size;
    value_type variance() const noexcept;
};

template <typename T, std::size_t W, online::with UseMoment>
auto basic_moment<T, W, with::variance, UseMoment>::variance() const noexcept -> value_type
{
    if (super::passive.empty())
        return super::active.variance();
    if (super::active.size() <= 1) // Insufficient data points to calculate variance
        return super::passive.variance();

    // Squared weighted combined variance
    const auto sz = super::active.size() - 1;
    const auto passive_weight = (W - sz) * (W - sz);
    const auto active_weight = 2 * sz;
    return (passive_weight * super::passive.variance() + active_weight * super::active.variance())
        / (passive_weight + active_weight);
}

//-----------------------------------------------------------------------------
// With skewness
//-----------------------------------------------------------------------------

template <typename T, std::size_t N, online::with UseMoment>
class basic_moment<T, N, with::skewness, UseMoment>
    : protected basic_moment<T, N, with::variance, UseMoment>
{
    using super = basic_moment<T, N, with::variance, UseMoment>;

    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using typename super::value_type;
    using typename super::size_type;

    using super::clear;
    using super::push;
    using super::capacity;
    using super::empty;
    using super::full;
    using super::mean;
    using super::variance;
    using super::size;
    value_type skewness() const noexcept;
};

template <typename T, std::size_t W, online::with UseMoment>
auto basic_moment<T, W, with::skewness, UseMoment>::skewness() const noexcept -> value_type
{
    if (super::passive.empty())
        return super::active.skewness();
    if (super::active.size() <= 1) // Insufficient data points to calculate skewness
        return super::passive.skewness();

    // Weighted combined skewness
    const auto sz = super::active.size() - 1;
    const auto passive_weight = (W - sz);
    const auto active_weight = 2 * sz;
    return (passive_weight * super::passive.skewness() + active_weight * super::active.skewness())
        / (passive_weight + active_weight);
}

//-----------------------------------------------------------------------------
// With kurtosis
//-----------------------------------------------------------------------------

template <typename T, std::size_t N, online::with UseMoment>
class basic_moment<T, N, with::kurtosis, UseMoment>
    : protected basic_moment<T, N, with::skewness, UseMoment>
{
    using super = basic_moment<T, N, with::skewness, UseMoment>;

    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using typename super::value_type;
    using typename super::size_type;

    using super::clear;
    using super::push;
    using super::capacity;
    using super::empty;
    using super::full;
    using super::mean;
    using super::variance;
    using super::skewness;
    using super::size;
    value_type kurtosis() const noexcept;
};

template <typename T, std::size_t W, online::with UseMoment>
auto basic_moment<T, W, with::kurtosis, UseMoment>::kurtosis() const noexcept -> value_type
{
    if (super::passive.empty())
        return super::active.kurtosis();
    if (super::active.size() <= 1) // Insufficient data points to calculate kurtosis
        return super::passive.kurtosis();

    // Weighted combined kurtosis
    const auto sz = super::active.size() - 1;
    const auto passive_weight = (W - sz);
    const auto active_weight = 2 * sz;
    return (passive_weight * super::passive.kurtosis() + active_weight * super::active.kurtosis())
        / (passive_weight + active_weight);
}

} // namespace detail
} // namespace interim
} // namespace online
} // namespace trial
