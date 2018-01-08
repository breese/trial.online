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
trial_online_add_test(cumulative_suite average/cumulative_suite.cpp)
trial_online_add_test(cumulative_variance_suite average/cumulative_variance_suite.cpp)

# correlation
trial_online_add_test(covariance_suite correlation/covariance_suite.cpp)
trial_online_add_test(pearson_suite correlation/pearson_suite.cpp)

# quantile
trial_online_add_test(psquare_suite quantile/psquare_suite.cpp)

# impulse
trial_online_add_test(finite_suite impulse/finite_suite.cpp)
trial_online_add_test(infinite_suite impulse/infinite_suite.cpp)

# sampling
trial_online_add_test(reservoir_suite sampling/reservoir_suite.cpp)
