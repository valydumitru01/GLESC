# ==========================================================
# ===================== CMakeLists.txt =====================
# ==========================================================
# This is the main CMakeLists.txt file for the project.
# Here all the modules work together to create the project.
# All the modules are found in the cmake folder.

# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.10)
# Main project name
project(game)
# The c++ version used
set(CMAKE_CXX_STANDARD 17)
# Ensure that the compiler supports the c++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enables CMake code to be forward compatible with newer
# versions of CMake.
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0135 NEW)

# ----------------------------------------------------------
# Function: include_cmake_once
# Description:
#   This function is used to include cmake files only once.
#   It is very important that this function stays at the top
#   of the CMakeLists.txt file. This is because the modules
#   that are included by this function may use this for
#   including other cmake files.
# Parameters:
#   cmake_file: The cmake file to include
# ----------------------------------------------------------
function(include_cmake_once cmake_file)
  string(TOUPPER ${cmake_file} cmake_file_upper)
  string(REPLACE "." "_" cmake_file_upper ${cmake_file_upper})
  if (NOT DEFINED CMAKE_INCLUDED_${cmake_file_upper})
    include(${cmake_file})
    set(CMAKE_INCLUDED_${cmake_file_upper} TRUE PARENT_SCOPE)
  endif ()
endfunction()

include_cmake_once(cmake/FindPackages.cmake)
include_cmake_once(cmake/LinkedLibraries.cmake)
include_cmake_once(cmake/PlatformDetection.cmake)
include_cmake_once(cmake/CompilerDefinitions.cmake)
include_cmake_once(cmake/Testing.cmake)
# ----------------------------------------------------------
# Function: include_cmake_once
# Description:
#   Simple wrapper to add an executable target
# Parameters:
#   name: The name of the executable target
# ----------------------------------------------------------
function(create_executable name)
  message(STATUS "Adding executable target ${name}")
  add_executable(${name})
endfunction()

# Defining all the targets of the project
set(targets
    # The main target
    game
    # The test target
    game_test
)

# ----------------------------------------------------------
# Finding packages

# This finds all the packages that are common to all targets
find_common_packages()

if (TARGET game_test)
  find_extra_package(GTest)
  find_extra_package(GTestMain)
  find_extra_package(GMock)
  find_extra_package(GMockMain)
endif ()

# ----------------------------------------------------------


# ----------------------------------------------------------
# Creating the targets
foreach (target ${targets})
  create_executable(${target})
endforeach ()
# ----------------------------------------------------------


# ----------------------------------------------------------
# Setting the source files
foreach (target ${targets})
  set_common_sources(${target})
endforeach ()

if (TARGET game_test)
  add_extra_sources(game_test ${TEST_FILES})
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
  set_common_static_lib_dirs(${target})
endforeach ()

foreach (target ${targets})
  link_common_libs(${target})
endforeach ()
if (TARGET game_test)
  link_extra_libs(game_test gtest gtest_main)
endif ()
# ----------------------------------------------------------
# Setting the compiler flags

# Here we set the compiler flags that are applied to all
# files and can be specific to the target
foreach (target ${targets})
  set_common_compiler_flags_to_build_type(${target})
endforeach ()
# And here we apply the compiler flags to the files
# which are common to all targets (and cannot be specific
# to a target)
set_compile_flags_to_common_files()
# Here we apply those flags to extra files
if (TARGET game_test)
  set_compile_flags_to_extra_files(${TEST_FILES})
endif ()

# ----------------------------------------------------------

if (BUILD_TESTING)
  message(STATUS "Building tests")



endif ()

