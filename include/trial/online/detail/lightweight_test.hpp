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

} // namespace detail
} // namespace online
} // namespace trial

#define TRIAL_ONLINE_TEST BOOST_TEST
#define TRIAL_ONLINE_TEST_EQUAL BOOST_TEST_EQ

#define TRIAL_ONLINE_TEST_CLOSE(LHS, RHS, TOLERANCE) ::trial::online::detail::test_close_impl(#LHS, #RHS, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, LHS, RHS, TOLERANCE)

#endif // TRIAL_ONLINE_DETAIL_LIGHTWEIGHT_TEST_HPP
