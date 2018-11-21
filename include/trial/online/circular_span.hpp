#ifndef TRIAL_ONLINE_CIRCULAR_SPAN_HPP
#define TRIAL_ONLINE_CIRCULAR_SPAN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <type_traits>
#include <iterator>

namespace trial
{
namespace online
{

// FIXME: Partly inspired by http://wg21.link/p0059

template <typename T>
class circular_span
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = typename std::add_pointer<value_type>::type;
    using reference = typename std::add_lvalue_reference<value_type>::type;
    using const_reference = typename std::add_const<reference>::type;

    circular_span(const circular_span&) noexcept = default;
    circular_span(circular_span&&) noexcept = default;
    circular_span& operator= (const circular_span&) noexcept = default;
    circular_span& operator= (circular_span&&) noexcept = default;

    template <typename ContiguousIterator>
    circular_span(ContiguousIterator begin, ContiguousIterator end) noexcept;

    //! @brief Check if span is empty.
    bool empty() const noexcept;

    //! @brief Check if span is full.
    bool full() const noexcept;

    //! @brief Returns the maximum possible number of elements in span.
    size_type capacity() const noexcept;

    //! @brief Returns the number of elements in span.
    size_type size() const noexcept;

    //! @brief Returns reference to first element in span.
    const_reference front() const noexcept;

    //! @brief Returns reference to last element in span.
    const_reference back() const noexcept;

    //! @brief Clears the span.
    //!
    //! The content of the underlying storage is not modified.
    void clear() noexcept;

    //! @brief Inserts element at the end of the span.
    void push_back(const value_type& input) noexcept(std::is_nothrow_copy_assignable<T>::value);

private:
    template <typename U>
    struct basic_iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using value_type = U;
        using difference_type = std::ptrdiff_t;
        using pointer = typename std::add_pointer<value_type>::type;
        using reference = typename std::add_lvalue_reference<value_type>::type;
        using const_reference = typename std::add_const<reference>::type;
        using iterator_type = basic_iterator<value_type>;

        iterator_type& operator++ () noexcept;
        iterator_type operator++ (int) noexcept;

        pointer operator-> () noexcept;
        const_reference operator* () const noexcept;

        bool operator== (const iterator_type&) const noexcept;
        bool operator!= (const iterator_type&) const noexcept;

    private:
        friend class circular_span<T>;

        basic_iterator(const circular_span<T>& parent, const size_type index);

    private:
        const circular_span<T>& parent;
        size_type current;
    };

public:
    using iterator = basic_iterator<value_type>;
    using const_iterator = basic_iterator<const value_type>;

    //! @brief Returns iterator to the beginning of the span.
    iterator begin();
    const_iterator begin() const;

    //! @brief Returns iterator to the ending of the span.
    iterator end();
    const_iterator end() const;

private:
    size_type index(size_type) const noexcept;
    size_type vindex(size_type) const noexcept;
    reference at(size_type) noexcept;
    const_reference at(size_type) const noexcept;

private:
    struct
    {
        const pointer data;
        const size_type capacity;
        size_type size;
        size_type next;
    } member;
};

template <typename T, std::size_t N>
class circular_span<T[N]>
    : protected circular_span<T>
{
    using super = circular_span<T>;

public:
    using super::value_type;
    using super::size_type;
    using super::pointer;
    using super::reference;
    using super::const_reference;

    circular_span(T (&array)[N]) noexcept;

    using super::empty;
    using super::full;
    using super::size;
    using super::capacity;
    using super::front;
    using super::back;

    using super::clear;
    using super::push_back;

    using super::iterator;
    using super::const_iterator;
    using super::begin;
    using super::end;
};

} // namespace online
} // namespace trial

#include <trial/online/detail/circular_span.ipp>

#endif // TRIAL_ONLINE_CIRCULAR_SPAN_HPP
