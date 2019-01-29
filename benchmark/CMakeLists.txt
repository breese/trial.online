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
  target_compile_options(${name} PRIVATE ${TRIAL_ONLINE_WARNING_FLAGS})
  target_compile_features(${name} PRIVATE ${TRIAL_ONLINE_FEATURES})
  add_dependencies(benchmark ${name})
endfunction()

# online
trial_online_add_benchmark(circular_span_benchmark circular_span_benchmark.cpp)

# cumulative
trial_online_add_benchmark(cumulative_moment_benchmark cumulative/moment_benchmark.cpp)
