#ifndef TRIAL_ONLINE_DETAIL_LIGHTWEIGHT_TEST_HPP
#define TRIAL_ONLINE_DETAIL_LIGHTWEIGHT_TEST_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <algorithm>
#include <sstream>
#include <boost/detail/lightweight_test.hpp>

namespace trial
{
namespace online
{
namespace detail
{

template<class T, class U>
inline void test_close_impl(char const * expr1,
                            char const * expr2,
                            char const * file, int line, char const * function,
                            const T& lhs, const U& rhs, double tolerance)
{
    if (std::fabs(lhs - rhs) <= tolerance)
    {
        boost::detail::report_errors_remind();
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test '" << expr1 << " == " << expr2
            << "' failed in function '" << function << "': "
            << "'" << lhs << "' != '" << rhs << "'" << std::endl;
        ++boost::detail::test_errors();
    }
}

template<class InputIt1, class InputIt2, class Predicate>
inline void test_mismatch_impl(char const * file, int line, char const * function,
                               InputIt1 first_begin, InputIt1 first_end,
                               InputIt2 second_begin, InputIt2 second_end,
                               Predicate predicate)
{
    if (std::distance(first_begin, first_end) != std::distance(second_begin, second_end))
    {
        ::boost::detail::error_impl("Container sizes are different", __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);
    }
    else
    {
        std::pair<InputIt1, InputIt2> result = std::mismatch(first_begin, first_end, second_begin, predicate);
        if (result.first == first_end)
        {
            boost::detail::report_errors_remind();
        }
        else
        {
            std::ostringstream indices;
            while (result.first != first_end)
            {
                indices << ' ' << std::distance(first_begin, result.first);
                result = std::mismatch(++result.first, first_end, ++result.second);
            }
            BOOST_LIGHTWEIGHT_TEST_OSTREAM
                << file << "(" << line << "): Container contents differ in function '" << function << "': mismatching indices"
                << indices.str() << std::endl;
            ++boost::detail::test_errors();
        }
    }
}

} // namespace detail
} // namespace online
} // namespace trial

#define TRIAL_ONLINE_TEST BOOST_TEST
#define TRIAL_ONLINE_TEST_EQUAL BOOST_TEST_EQ

#define TRIAL_ONLINE_TEST_CLOSE(LHS, RHS, TOLERANCE) ::trial::online::detail::test_close_impl(#LHS, #RHS, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, LHS, RHS, TOLERANCE)

#define TRIAL_ONLINE_TEST_ALL_WITH(FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE) ::trial::online::detail::test_mismatch_impl(__FILE__, __LINE__, BOOST_CURRENT_FUNCTION, FIRST_BEGIN, FIRST_END, SECOND_BEGIN, SECOND_END, PREDICATE)

#endif // TRIAL_ONLINE_DETAIL_LIGHTWEIGHT_TEST_HPP
