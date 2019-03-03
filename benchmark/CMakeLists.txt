###############################################################################
#
# Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

include(GoogleBenchmark.cmake)

add_custom_target(benchmark)

function(trial_online_add_benchmark name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} trial-online Google::benchmark)
  target_compile_options(${name} PRIVATE ${TRIAL_ONLINE_WARNING_FLAGS} -DNDEBUG=1)
  target_compile_features(${name} PRIVATE ${TRIAL_ONLINE_FEATURES})
  add_dependencies(benchmark ${name})
endfunction()

# online
trial_online_add_benchmark(circular_span_benchmark circular_span_benchmark.cpp)

# cumulative
trial_online_add_benchmark(cumulative_moment_benchmark cumulative/moment_benchmark.cpp)
trial_online_add_benchmark(cumulative_regression_benchmark cumulative/regression_benchmark.cpp)

# decay
trial_online_add_benchmark(decay_moment_benchmark decay/moment_benchmark.cpp)

# window
trial_online_add_benchmark(window_moment_benchmark window/moment_benchmark.cpp)
trial_online_add_benchmark(window_regression_benchmark window/regression_benchmark.cpp)

# interim
trial_online_add_benchmark(interim_moment_benchmark interim/moment_benchmark.cpp)
trial_online_add_benchmark(interim_regression_benchmark interim/regression_benchmark.cpp)
trial_online_add_benchmark(interim_psquare_quantile_benchmark interim/psquare_quantile_benchmark.cpp)
