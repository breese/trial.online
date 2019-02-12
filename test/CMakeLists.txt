###############################################################################
#
# Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

function(trial_online_add_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} trial-online)
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
  target_compile_options(${name} PRIVATE ${TRIAL_ONLINE_WARNING_FLAGS})
  target_compile_features(${name} PRIVATE ${TRIAL_ONLINE_FEATURES})
endfunction()

# online
trial_online_add_test(circular_span_suite circular_span_suite.cpp)

# detail
trial_online_add_test(type_traits_suite detail/type_traits_suite.cpp)

# cumulative
trial_online_add_test(cumulative_moment_suite cumulative/moment_suite.cpp)
trial_online_add_test(cumulative_comoment_suite cumulative/comoment_suite.cpp)
trial_online_add_test(cumulative_correlation_suite cumulative/correlation_suite.cpp)
trial_online_add_test(cumulative_regression_suite cumulative/regression_suite.cpp)
trial_online_add_test(cumulative_trend_suite cumulative/trend_suite.cpp)

# decay
trial_online_add_test(decay_moment_suite decay/moment_suite.cpp)

# window
trial_online_add_test(window_moment_suite window/moment_suite.cpp)
trial_online_add_test(window_comoment_suite window/comoment_suite.cpp)
trial_online_add_test(window_regression_suite window/regression_suite.cpp)

# quantile
trial_online_add_test(quantile_psquare_suite quantile/psquare_suite.cpp)
trial_online_add_test(quantile_interim_psquare_suite quantile/interim_psquare_suite.cpp)

# impulse
trial_online_add_test(finite_suite impulse/finite_suite.cpp)
trial_online_add_test(infinite_suite impulse/infinite_suite.cpp)

# sampling
trial_online_add_test(reservoir_suite sampling/reservoir_suite.cpp)
