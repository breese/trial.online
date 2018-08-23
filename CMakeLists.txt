###############################################################################
#
# Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.0)
project(trial.online)

function(trial_online_add_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} trial-online)
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
  target_compile_options(${name} PRIVATE -Wall -Wextra)
endfunction()

enable_testing()

add_subdirectory(cmake)
add_subdirectory(test)
