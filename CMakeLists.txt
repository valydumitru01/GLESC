# ==========================================================
# ===================== CMakeLists.txt =====================
# ==========================================================
# This is the main CMakeLists.txt file for the project.
# Here all the modules work together to create the project.
# All the modules are found in the cmake folder.
# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.10)
include(cmake/Printing.cmake)
important_info("CMake Version: ${CMAKE_VERSION}")

# Main project name
project(game)
# The c++ version used
set(CMAKE_CXX_STANDARD 17)
important_info("C++ Version: ${CMAKE_CXX_STANDARD}")

# Ensure that the compiler supports the c++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enables CMake code to be forward compatible with newer
# versions of CMake.
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0135 NEW)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)
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
  string(REGEX REPLACE "[^a-zA-Z0-9]" "_" cmake_file_upper ${cmake_file})
  set(CURRENT_FILE ${CMAKE_CURRENT_LIST_FILE})
  string(REPLACE "${CMAKE_SOURCE_DIR}/" "" STRIPPED_PATH ${CURRENT_FILE})
  debug("Including cmake file ${cmake_file} to file ${STRIPPED_PATH}")
  if (NOT DEFINED CMAKE_INCLUDED_${cmake_file_upper})
    include(cmake/${cmake_file})
    set(CMAKE_INCLUDED_${cmake_file_upper} TRUE PARENT_SCOPE)
  else ()
    debug("CMake file ${cmake_file} already included, not necessary to include it again for file ${STRIPPED_PATH}")
  endif ()
endfunction()

include_cmake_once(FindPackages.cmake)
include_cmake_once(FileLocations.cmake)
include_cmake_once(LinkedLibraries.cmake)
include_cmake_once(PlatformDetection.cmake)
include_cmake_once(CompilerDefinitions.cmake)
include_cmake_once(CompilerFlags.cmake)
include_cmake_once(Testing.cmake)
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
endfunction()

# Defining all the targets of the project
set(targets
    # The main target
    game
    # The test target
    game_test
)
# Here we define the directories and files of the cmake
# and store them in variables for later use
define_directories_and_files()
# Here we're detecting the platform where the project is
# being built
detect_platform()
# ----------------------------------------------------------
# Finding packages

# This finds all the packages that are common to all targets
find_common_packages()

if (TARGET game_test)
  find_extra_packages(GTest)
  find_extra_packages(GTestMain)
  find_extra_packages(GMock)
  find_extra_packages(GMockMain)
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


