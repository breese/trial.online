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
#include <initializer_list>
#include <iterator>

namespace trial
{
namespace online
{

// FIXME: Partly inspired by boost::circular_buffer and http://wg21.link/p0059

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
    //! @brief Clears span and inserts elements at end of span.
    circular_span& operator= (std::initializer_list<value_type>) noexcept(std::is_nothrow_copy_assignable<T>::value);

    //! @brief Creates circular span.
    //!
    //! The span covers the range from begin to end.
    template <typename ContiguousIterator>
    circular_span(ContiguousIterator begin,
                  ContiguousIterator end) noexcept;

    //! @brief Creates circular span.
    //!
    //! The span covers the range from @c begin to @c end.
    //!
    //! The span is initialized as if the pre-existing @c length values from
    //! @c first had already been pushed onto the span.
    template <typename ContiguousIterator>
    circular_span(ContiguousIterator begin,
                  ContiguousIterator end,
                  ContiguousIterator first,
                  size_type length) noexcept;

    //! @brief Checks if span is empty.
    bool empty() const noexcept;

    //! @brief Checks if span is full.
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

    //! @brief Clears span and inserts elements at end of span.
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) noexcept(std::is_nothrow_copy_assignable<T>::value);

    //! @brief Clears span and inserts elements at end of span.
    void assign(std::initializer_list<value_type> input) noexcept(std::is_nothrow_move_assignable<T>::value);

    //! @brief Inserts element at beginning of span.
    void push_front(value_type input) noexcept(std::is_nothrow_move_assignable<T>::value);

    //! @brief Inserts element at end of span.
    void push_back(value_type input) noexcept(std::is_nothrow_move_assignable<T>::value);

    //! @brief Erases element from beginning of span
    void pop_front() noexcept;

    //! @brief Erases element from end of span
    void pop_back() noexcept;

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

        basic_iterator() = default;
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        basic_iterator& operator= (const basic_iterator&) = default;
        basic_iterator& operator= (basic_iterator&&) = default;

        iterator_type& operator++ () noexcept;
        iterator_type operator++ (int) noexcept;

        pointer operator-> () noexcept;
        const_reference operator* () const noexcept;

        bool operator== (const iterator_type&) const noexcept;
        bool operator!= (const iterator_type&) const noexcept;

    private:
        friend class circular_span<T>;

        basic_iterator(const circular_span<T> *parent, const size_type index);

    private:
        const circular_span<T> *parent;
        size_type current;
    };

public:
    using iterator = basic_iterator<value_type>;
    using const_iterator = basic_iterator<const value_type>;

    //! @brief Returns iterator to the beginning of the span.
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    //! @brief Returns iterator to the ending of the span.
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

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
    using typename super::value_type;
    using typename super::size_type;
    using typename super::pointer;
    using typename super::reference;
    using typename super::const_reference;

    circular_span(T (&array)[N]) noexcept;

    using super::operator=;

    using super::empty;
    using super::full;
    using super::size;
    using super::capacity;
    using super::front;
    using super::back;

    using super::clear;
    using super::assign;
    using super::push_front;
    using super::push_back;
    using super::pop_front;
    using super::pop_back;

    using typename super::iterator;
    using typename super::const_iterator;
    using super::begin;
    using super::cbegin;
    using super::end;
    using super::cend;
};

} // namespace online
} // namespace trial

#include <trial/online/detail/circular_span.ipp>

#endif // TRIAL_ONLINE_CIRCULAR_SPAN_HPP
