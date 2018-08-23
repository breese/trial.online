###############################################################################
#
# Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.0)
project(trial.online)

set(TRIAL_ONLINE_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(TRIAL_ONLINE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${TRIAL_ONLINE_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${TRIAL_ONLINE_BUILD_DIR}/bin)

get_filename_component(TRIAL_ONLINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../" ABSOLUTE)

if (${CMAKE_VERSION} VERSION_LESS 3.8)
  set(TRIAL_ONLINE_FEATURES cxx_auto_type)
else()
  set(TRIAL_ONLINE_FEATURES cxx_std_11)
endif()

if (MSVC)
  set(TRIAL_ONLINE_WARNING_FLAGS /W3)
else()
  set(TRIAL_ONLINE_WARNING_FLAGS -Wall -Wextra -pedantic -Werror=return-type)
endif()

###############################################################################
# Boost package
###############################################################################

# Boost.Circular Buffer
find_package(Boost 1.55.0 QUIET)
if (NOT ${Boost_FOUND})
  message(FATAL_ERROR "${Boost_ERROR_REASON}")
endif()

###############################################################################
# Trial.Online
###############################################################################

add_library(trial-online INTERFACE)

###############################################################################
# External packages
###############################################################################

set_target_properties(trial-online PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIRS}"
  INTERFACE_INCLUDE_DIRECTORIES "${TRIAL_ONLINE_ROOT_DIR}/include")

# Use own copy if Boost.Mp11 is unavailable
if (${Boost_VERSION} LESS 106600)
  set_property(TARGET trial-online APPEND PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES "${TRIAL_ONLINE_ROOT_DIR}/external/mp11/include")
endif()
