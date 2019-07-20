#ifndef TRIAL_ONLINE_ITERATOR_HPP
#define TRIAL_ONLINE_ITERATOR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <iterator>

namespace trial
{
namespace online
{

template <typename Container>
class push_iterator
{
public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    constexpr push_iterator()
        : container(nullptr)
    {
    }

    constexpr explicit push_iterator(Container& c)
        : container(&c)
    {
    }

    push_iterator& operator=(const typename container_type::value_type& value)
    {
        container->push(value);
        return *this;
    }

    push_iterator& operator*()
    {
        return *this;
    }

    push_iterator& operator++()
    {
        return *this;
    }

    push_iterator& operator++(int)
    {
        return *this;
    }

private:
    Container *container;
};

template <typename Container>
push_iterator<Container> push_inserter(Container& c)
{
    return push_iterator<Container>(c);
}

} // namespace online
} // namespace trial

#endif // TRIAL_ONLINE_ITERATOR_HPP
