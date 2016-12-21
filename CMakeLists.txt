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

set(TRIAL_ONLINE_BUILD_DIR ${CMAKE_BINARY_DIR})
set(TRIAL_ONLINE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${TRIAL_ONLINE_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${TRIAL_ONLINE_BUILD_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

###############################################################################
# Brigand package
###############################################################################

include_directories(external/brigand)

###############################################################################
# Trial.Online package
###############################################################################

include_directories(include)

function(trial_online_add_test name)
  add_executable(${name} ${ARGN})
  #target_link_libraries(${name} ${TRIAL_ONLINE_DEPENDENT_LIBRARIES})
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
  target_compile_options(${name} PRIVATE -Wall -Wextra)
endfunction()

enable_testing()

add_subdirectory(test)
