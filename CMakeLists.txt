# ==========================================================
# ===================== CMakeLists.txt =====================
# ==========================================================
# This is the main CMakeLists.txt file for the project.
# Here all the modules work together to create the project.
# All the modules are found in the cmake folder.

# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.20)
# Enables CMake code to be forward compatible with newer
# versions of CMake.
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0135 NEW)

# Enforces that the specified C++ standard is required.
# If the compiler can't support it, CMake config will fail.
# Prevents fallback to older standards, ensuring consistent
# behavior across different compilers and systems.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

# Core functionality, needed to build the project
# Using the regular include, because the custom
# include_once might depend on these
include(cmake/core/Printing.cmake)
include(cmake/core/ErrorChecking.cmake)
include(cmake/core/Including.cmake)
include(cmake/core/PlatformDetection.cmake)
important_info("CMake Version: ${CMAKE_VERSION}")

# Main project name
project(game)
# The c++ version used
set(CMAKE_CXX_STANDARD 17)
important_info("C++ Version: ${CMAKE_CXX_STANDARD}")

include_cmake_once(modules/FindPackages.cmake)
include_cmake_once(modules/FileLocations.cmake)
include_cmake_once(modules/LinkLibraries.cmake)
include_cmake_once(modules/CompilerDefinitions.cmake)
include_cmake_once(modules/CompilerFlags.cmake)
include_cmake_once(modules/Testing.cmake)
# ----------------------------------------------------------
# Function: include_cmake_once
# Description:
#   Simple wrapper to add an executable target
# Parameters:
#   name: The name of the executable target
# ----------------------------------------------------------
function(create_executable name)
  important_info("Adding executable target ${name}")
  add_executable(${name})
  success("Added executable target ${name}")
endfunction()

# Defining all the targets of the project
set(targets
    # The main target
    game
    # The test target
    game_test
)

# And here we apply the compiler flags to the files
# which are common to all targets (and cannot be specific
# to a target)
set_compile_flags_to_common_files()

# Here we apply those flags to extra files
if (TARGET game_test)
  # Cache variables need to be passed as strings
  set_compile_flags_to_extra_files("${TEST_SOURCE_FILES}")
endif ()

# ----------------------------------------------------------
# Creating the targets
foreach (target ${targets})
  create_executable(${target})
endforeach ()
# ----------------------------------------------------------

# ----------------------------------------------------------
# This finds all the packages that are common to all targets
find_common_packages()

# ----------------------------------------------------------

# ----------------------------------------------------------
# Setting testing
if (TARGET game_test)
  prepare_tests(game_test)
endif ()
# ----------------------------------------------------------


# ----------------------------------------------------------
# Setting the compiler flags

# Here we set the compiler flags that are applied to all
# files and can be specific to the target
foreach (target ${targets})
  set_common_compiler_flags_to_build_type(${target})
endforeach ()

# ----------------------------------------------------------

# ----------------------------------------------------------
# Setting the source files
foreach (target ${targets})
  set_common_sources(${target})
endforeach ()

if (TARGET game_test)
  add_extra_sources(game_test "${TEST_SOURCE_FILES}")
endif ()


# ----------------------------------------------------------

# ----------------------------------------------------------
# Setting compiler definitions
foreach (target ${targets})
  set_common_definitions(${target})
endforeach ()

if (TARGET game_test)
  add_extra_definitions(game_test GTEST_HAS_DEATH_TEST=1)
endif ()

# ----------------------------------------------------------

# ----------------------------------------------------------
# Setting include directories
foreach (target ${targets})
  set_common_include_dirs(${target})
endforeach ()
# ----------------------------------------------------------

# ----------------------------------------------------------
# Setting the static libraries directories before linking
# and then linking the static libraries
foreach (target ${targets})
  set_common_link_lib_dirs(${target})
endforeach ()

foreach (target ${targets})
  set_common_link_libs(${target})
endforeach ()
if (TARGET game_test)
  add_extra_link_libs(game_test gtest gtest_main)
endif ()
# ----------------------------------------------------------



