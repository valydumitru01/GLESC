# Main CMakeLists.txt file for the project

# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.10)
# Main project name
project(game)
# Option for building tests
option(BUILD_TESTING "Build tests" ON)
# The c++ version used
set(CMAKE_CXX_STANDARD 17)
# Ensure that the compiler supports the c++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enables CMake code to be forward compatible with newer versions of CMake.
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0135 NEW)

include(cmake/CompilerFlags.cmake)
include(cmake/FileLocations.cmake)
include(cmake/FindPackages.cmake)
include(cmake/LinkedLibraries.cmake)
include(cmake/PlatformDetection.cmake)

include(cmake/Testing.cmake)

# ------------ TARGETS ------------
# function to create the executables of given name
function(create_executable name)
    message(STATUS "Adding executable target ${name}")
    add_executable(${name})
endfunction()


# ------------ DEFINITIONS ------------
# Function to set common definitions to the given target
function(set_common_definitions target)
    message(STATUS "Adding common definitions to ${target}")

    # Set project binary directory based on build type
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(PROJECT_BINARY_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(PROJECT_BINARY_DIR "${PROJECT_BINARY_DIR_RELEASE_RELEASE}")
    endif ()

    # Store all definitions in a list
    set(defs
            ${PLATFORM} # This is the platform the project is being built on
            GLEW_STATIC # This is needed for glew to work statically
            FRAG_SHADER="${FRAG_SHADER}" # This is the fragment shader file
            VERT_SHADER="${VERT_SHADER}" # This is the vertex shader file
            PROJECT_NAME="${PROJECT_NAME}" # This is the name of the executable
            # This is needed for stack traces to work
            PROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}" # This is the binary directory of the project
            # This is also needed for stack traces to work
    )

    # Apply definitions to the target
    target_compile_definitions(${target} PRIVATE ${defs})

    # Verbose log of all definitions
    message(VERBOSE "Added definitions:")
    foreach (def IN LISTS defs)
        message(VERBOSE "  ${def}")
    endforeach ()

endfunction()
function(add_extra_definitions target defs)
    message(STATUS "Adding extra definitions to ${target}")
    target_compile_definitions(${target} PRIVATE ${defs})
    message(VERBOSE "Added definitions: ${defs} to ${target}")
endfunction()



# ------------ COMPILE FLAGS ------------
# Function to set common compile flags
function(set_compile_flags_to_common_files)
    message(STATUS "Adding compile flags to common files")
    set_source_files_properties(
            ${SOURCE_FILES} ${INCLUDE_FILES} ${TEST_FILES}
            PROPERTIES
            COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    )
    message(VERBOSE "Added compile flags: ${MY_COMPILE_FLAGS}")
    message(VERBOSE "These compile flags are only applied to the project sources.
        No compile flags are applied to the library sources.
        The following sources are affected:
        ${SOURCE_FILES} ${INCLUDE_FILES} ${TEST_FILES}\n")
endfunction()
function(set_compile_flags_to_extra_files files)
    message(STATUS "Adding compile flags to extra files")
    set_source_files_properties(
            files
            PROPERTIES
            COMPILE_FLAGS ${flags}
    )
    message(VERBOSE "Added compile flags: ${flags} to ${target}")
    message(VERBOSE "he following sources are affected:\n
        ${files}")
endfunction()

# ------------ INCLUDE DIRECTORIES ------------
# Must be added before linking libraries





# ------------ LINKING LIBRARIES ------------

target_link_directories(game PRIVATE
        ${LIB_STATIC_DIR} # This is where the static libraries are located
        # This is defined in FileLocations.cmake
)
target_link_libraries(game
        ${MAIN_LIBS} # These are the libraries that the project depends on
        # Defined in LinkedLibraries.cmake
)
foreach(target game game_test)
    create_executable(${target})
    set_common_sources(${target})
    set_common_definitions(${target})
    set_common_include_dirs(${target})

    set_common_static_lib_dirs(${target})
    link_common_static_libs(${target})

    set_common_build_type_flags(${target})
endforeach()
set_compile_flags_to_common_files()

if(BUILD_TESTING)
    message(STATUS "Building tests")
    set_compile_flags_to_extra_files(${TEST_FILES})
    add_extra_sources(game_test ${TEST_FILES})
    add_extra_definitions(game_test GTEST_HAS_DEATH_TEST=1)
    add_extra_include_dirs(game_test ${TEST_INCLUDE_DIR})
    link_extra_static_libs(game_test gtest gtest_main)

endif()

# ------------ BUILD TYPES ------------
