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
include(cmake/modules/Printing.cmake)
include(cmake/modules/ErrorChecking.cmake)
include(cmake/modules/Including.cmake)
include(cmake/modules/PlatformDetection.cmake)
important_info("CMake Version: ${CMAKE_VERSION}")

# Main project name
project(game)
# The c++ version used
set(CMAKE_CXX_STANDARD 17)
important_info("C++ Version: ${CMAKE_CXX_STANDARD}")

include_cmake_once(core/FindPackages.cmake)
include_cmake_once(core/FileLocations.cmake)
include_cmake_once(core/LinkLibraries.cmake)
include_cmake_once(core/CompilerDefinitions.cmake)
include_cmake_once(core/CompilerFlags.cmake)
include_cmake_once(core/Testing.cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Defining all the targets of the project
    set(targets
            # The main target
            game
            # The test target
            game_test
    )
else ()
    set(targets
            # The main target
            game
    )
endif ()



# ----------------------------------------------------------
# Function: include_cmake_once
# Description:
#   Simple wrapper to add an executable target
# Parameters:
#   name: The name of the executable target
# ----------------------------------------------------------
function(create_executable name)
    important_info("Adding executable target ${name}")
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_executable(${name} WIN32)
    else ()
        add_executable(${name})
    endif ()
    success("Added executable target ${name}")
endfunction()


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


# ----------------------------------------------------------

# ----------------------------------------------------------
# Setting include directories
foreach (target ${targets})
    set_common_include_dirs(${target})
endforeach ()
if (TARGET game_test)
    add_extra_include_dirs(game_test "${TEST_DIR}")
    add_extra_include_dirs(game_test "${GTEST_INCLUDE_DIRS}")
endif ()
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

set(DIRECTORY_TO_EMPTY ${CMAKE_BINARY_DIR}${ASSETS_BIN_DIR})
important_info("Copying assets from ${ASSETS_DEV_DIR} to ${DIRECTORY_TO_EMPTY}")
file(COPY ${ASSETS_DEV_DIR} DESTINATION ${CMAKE_BINARY_DIR}${ASSETS_BIN_LOCATION} )
success("Copied assets from ${ASSETS_DEV_DIR} to ${CMAKE_BINARY_DIR}${ASSETS_BIN_LOCATION}")


# TODO: Fix all this mess
# Get the directory part of the path
get_filename_component(DIR ${CMAKE_BINARY_DIR} DIRECTORY)

# Get the directory part of the path
get_filename_component(FILE ${CMAKE_BINARY_DIR} NAME)
set_new_dir(RELEASE_RELEASE_DIR ${DIR}/release-${FILE})
important_info("Copying bins from ${BIN_DEV_DIR} to ${CMAKE_BINARY_DIR}${BIN_BIN_LOCATION}")
file(GLOB_RECURSE BINS_TO_COPY ${BIN_DEV_DIR}/*)
important_info("Copying files:")
foreach (file ${BINS_TO_COPY})
    file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}${BIN_BIN_LOCATION})
    success("Copied ${file} to ${CMAKE_BINARY_DIR}/${BIN_BIN_LOCATION}")

    success("Copied ${file} to ${RELEASE_RELEASE_DIR}")
    file(COPY ${file} DESTINATION ${RELEASE_RELEASE_DIR})
endforeach ()
success("Copied bins from ${BIN_DEV_DIR} to ${CMAKE_BINARY_DIR}${BIN_BIN_LOCATION}")

# Copy the executable and the assets to the release folders
file(COPY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe DESTINATION ${RELEASE_RELEASE_DIR})
success("Copied ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe to ${RELEASE_RELEASE_DIR}")
file(COPY ${CMAKE_BINARY_DIR}/assets DESTINATION ${RELEASE_RELEASE_DIR})
success("Copied ${CMAKE_BINARY_DIR}/assets to ${RELEASE_RELEASE_DIR}")