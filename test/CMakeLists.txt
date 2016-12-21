###############################################################################
#
# Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

# detail
trial_online_add_test(type_traits_suite detail/type_traits_suite.cpp)

# average
trial_online_add_test(arithmetic_suite average/arithmetic_suite.cpp)
trial_online_add_test(arithmetic_variance_suite average/arithmetic_variance_suite.cpp)
trial_online_add_test(exponential_suite average/exponential_suite.cpp)

# quantile
trial_online_add_test(psquare_suite quantile/psquare_suite.cpp)
