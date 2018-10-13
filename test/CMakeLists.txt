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

# cumulative
trial_online_add_test(cumulative_moment_suite cumulative/moment_suite.cpp)
trial_online_add_test(cumulative_covariance_suite cumulative/covariance_suite.cpp)
trial_online_add_test(cumulative_correlation_suite cumulative/correlation_suite.cpp)
trial_online_add_test(cumulative_regression_suite cumulative/regression_suite.cpp)

# decay
trial_online_add_test(decay_moment_suite decay/moment_suite.cpp)

# window
trial_online_add_test(window_moment_suite window/moment_suite.cpp)
trial_online_add_test(window_covariance_suite window/covariance_suite.cpp)

# quantile
trial_online_add_test(psquare_suite quantile/psquare_suite.cpp)

# impulse
trial_online_add_test(finite_suite impulse/finite_suite.cpp)
trial_online_add_test(infinite_suite impulse/infinite_suite.cpp)

# sampling
trial_online_add_test(reservoir_suite sampling/reservoir_suite.cpp)
