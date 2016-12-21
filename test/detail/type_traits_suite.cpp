///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/core/lightweight_test_trait.hpp>
#include <trial/online/detail/lightweight_test.hpp>

#include <ratio>
#include <trial/online/detail/type_traits.hpp>

//-----------------------------------------------------------------------------

namespace is_ratio_suite
{

struct valid_ratio
{
    static constexpr std::intmax_t num = 1;
    static constexpr std::intmax_t den = 2;
};

struct invalid_ratio_missing_den
{
    static constexpr std::intmax_t num = 1;
};

struct invalid_ratio_missing_num
{
    static constexpr std::intmax_t den = 1;
};

struct invalid_ratio_empty
{
};

void test()
{
    BOOST_TEST_TRAIT_TRUE((trial::online::detail::is_ratio<std::ratio<1,2>>));
    BOOST_TEST_TRAIT_TRUE((trial::online::detail::is_ratio<valid_ratio>));
    BOOST_TEST_TRAIT_FALSE((trial::online::detail::is_ratio<invalid_ratio_missing_den>));
    BOOST_TEST_TRAIT_FALSE((trial::online::detail::is_ratio<invalid_ratio_missing_num>));
    BOOST_TEST_TRAIT_FALSE((trial::online::detail::is_ratio<invalid_ratio_empty>));
}

} // namespace is_ratio_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    is_ratio_suite::test();

    return boost::report_errors();
}
