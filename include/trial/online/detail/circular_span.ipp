///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>

namespace trial
{
namespace online
{

//-----------------------------------------------------------------------------
// circular_span<T>
//-----------------------------------------------------------------------------

template <typename T>
template <typename ContiguousIterator>
circular_span<T>::circular_span(ContiguousIterator begin,
                                ContiguousIterator end) noexcept
    : member{std::addressof(*begin), size_type(std::distance(begin, end)), 0, 0}
{
}

template <typename T>
template <typename ContiguousIterator>
circular_span<T>::circular_span(ContiguousIterator begin,
                                ContiguousIterator end,
                                ContiguousIterator first,
                                size_type length) noexcept
    : member{std::addressof(*begin), size_type(std::distance(begin, end)), length, size_type(std::distance(begin, first))}
{
}

template <typename T>
template <std::size_t N>
circular_span<T>::circular_span(value_type (&array)[N]) noexcept
    : circular_span(array, array + N)
{
}

template <typename T>
auto circular_span<T>::operator= (std::initializer_list<value_type> input) noexcept(std::is_nothrow_copy_assignable<T>::value) -> circular_span&
{
    assign(std::move(input));
    return *this;
}

template <typename T>
bool circular_span<T>::empty() const noexcept
{
    return size() == 0;
}

template <typename T>
bool circular_span<T>::full() const noexcept
{
    return size() == capacity();
}

template <typename T>
auto circular_span<T>::capacity() const noexcept -> size_type
{
    return member.capacity;
}

template <typename T>
auto circular_span<T>::size() const noexcept -> size_type
{
    return member.size;
}

template <typename T>
auto circular_span<T>::front() const noexcept -> const_reference
{
    assert(!empty());

    return at(member.next - member.size);
}

template <typename T>
auto circular_span<T>::back() const noexcept -> const_reference
{
    assert(!empty());

    return at(member.next - 1);
}

template <typename T>
void circular_span<T>::clear() noexcept
{
    member.size = 0;
    member.next = 0;
}

template <typename T>
template <typename InputIterator>
void circular_span<T>::assign(InputIterator first, InputIterator last) noexcept(std::is_nothrow_copy_assignable<T>::value)
{
    clear();
    while (first != last)
    {
        push_back(*first);
        ++first;
    }
}

template <typename T>
void circular_span<T>::assign(std::initializer_list<value_type> input) noexcept(std::is_nothrow_move_assignable<T>::value)
{
    clear();
    for (const auto& value : input)
    {
        push_back(std::move(value));
    }
}

template <typename T>
void circular_span<T>::push_front(value_type input) noexcept(std::is_nothrow_move_assignable<T>::value)
{
    if (full())
    {
        member.next = member.capacity + index(member.next) - 1;
    }
    else
    {
        ++member.size;
    }
    at(index(member.next) - member.size) = std::move(input);
}

template <typename T>
void circular_span<T>::push_back(value_type input) noexcept(std::is_nothrow_move_assignable<T>::value)
{
    at(member.next) = std::move(input);
    member.next = member.capacity + index(member.next) + 1;
    if (!full())
    {
        ++member.size;
    }
}

template <typename T>
void circular_span<T>::pop_front() noexcept
{
    assert(!empty());

    --member.size;
}

template <typename T>
void circular_span<T>::pop_back() noexcept
{
    assert(!empty());

    member.next = member.capacity + index(member.next - 1);
    --member.size;
}

template <typename T>
auto circular_span<T>::begin() -> iterator
{
    return iterator(this, vindex(member.next - member.size));
}

template <typename T>
auto circular_span<T>::begin() const -> const_iterator
{
    return const_iterator(this, vindex(member.next - member.size));
}

template <typename T>
auto circular_span<T>::cbegin() const -> const_iterator
{
    return const_iterator(this, vindex(member.next - member.size));
}

template <typename T>
auto circular_span<T>::end() -> iterator
{
    return iterator(this, vindex(member.next));
}

template <typename T>
auto circular_span<T>::end() const -> const_iterator
{
    return const_iterator(this, vindex(member.next));
}

template <typename T>
auto circular_span<T>::cend() const -> const_iterator
{
    return const_iterator(this, vindex(member.next));
}

//-----------------------------------------------------------------------------

template <typename T>
auto circular_span<T>::index(size_type position) const noexcept -> size_type
{
    return position % member.capacity;
}

template <typename T>
auto circular_span<T>::vindex(size_type position) const noexcept -> size_type
{
    return position % (2 * member.capacity);
}

template <typename T>
auto circular_span<T>::at(size_type position) noexcept -> reference
{
    return member.data[index(position)];
}

template <typename T>
auto circular_span<T>::at(size_type position) const noexcept -> const_reference
{
    return member.data[index(position)];
}

//-----------------------------------------------------------------------------
// circular_span<T>::basic_iterator
//-----------------------------------------------------------------------------

template <typename T>
template <typename U>
circular_span<T>::basic_iterator<U>::basic_iterator(const circular_span<T> *parent,
                                                    size_type position)
    : parent(parent),
      current(position)
{
}

template <typename T>
template <typename U>
auto circular_span<T>::basic_iterator<U>::operator++ () noexcept -> iterator_type&
{
    assert(parent);

    current = parent->vindex(current + 1);
    return *this;
}

template <typename T>
template <typename U>
auto circular_span<T>::basic_iterator<U>::operator* () const noexcept -> const_reference
{
    assert(parent);

    return parent->at(current);
}

template <typename T>
template <typename U>
bool circular_span<T>::basic_iterator<U>::operator== (const iterator_type& other) const noexcept
{
    assert(parent);
    assert(parent == other.parent);

    return current == other.current;
}

template <typename T>
template <typename U>
bool circular_span<T>::basic_iterator<U>::operator!= (const iterator_type& other) const noexcept
{
    return !operator==(other);
}

} // namespace online
} // namespace trial
