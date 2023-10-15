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
if (BUILD_TESTING)
    message(STATUS "Building tests")
    include(cmake/Testing.cmake)
endif ()

# ------------ TARGETS ------------
# Add an executable target called game to be built from the source files
message(STATUS "Adding executable target game")
add_executable(game
        ${SOURCE_FILES} # These are the source files for the project
        ${LIB_SOURCE_FILES}# These are the source files for the libraries
)
message(STATUS "Adding executable target game_test")
add_executable(game_test
        ${TEST_FILES} # These are the test source files for the project
        ${LIB_SOURCE_FILES} # These are the source files for the libraries (the same as for the main project)
)
# ------------ MACRO DEFINITIONS ------------
# Macro definitions for the project

message(STATUS "Adding macro definitions")
target_compile_definitions(game PRIVATE
        # This is the platform definition for the project
        # Defined in PlatformDetection.cmake
        ${PLATFORM}
)
message("Platform definition: ${PLATFORM}")


# This is needed to allow the shaders to be loaded
target_compile_definitions(game PRIVATE
        # This stores the path to the fragment shader
        FRAG_SHADER="${FRAG_SHADER}"
)
message("Fragment shader: ${FRAG_SHADER}")
target_compile_definitions(game PRIVATE
        # This stores the path to the vertex shader
        VERT_SHADER="${VERT_SHADER}"
)
message("Vertex shader: ${VERT_SHADER}")

# This is needed to allow stacktrace to be printed with the correct project name
target_compile_definitions(game PRIVATE
        PROJECT_NAME="${PROJECT_NAME}"
)
message("Project name: ${PROJECT_NAME}")

# This is also needed to allow stacktrace to be printed
# This stores the path to the executable
# This is different for each build type with cmake
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game PRIVATE PROJECT_BINARY_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game PRIVATE PROJECT_BINARY_DIR="${PROJECT_BINARY_DIR_RELEASE_RELEASE}")
endif ()
message("Project binary dir: ${PROJECT_BINARY_DIR}")


# This is needed to allow the glew library (glew32s.lib) to be linked statically
target_compile_definitions(game PRIVATE GLEW_STATIC)

# ------------ COMPILE FLAGS ------------
message(STATUS "Adding compile flags")
# Apply the flags to your source files
set_source_files_properties(
        ${SOURCE_FILES} ${INCLUDE_FILES} ${TEST_FILES}
        PROPERTIES
        COMPILE_FLAGS
        ${MY_COMPILE_FLAGS} # These are the compile flags for the project
        # Defined in CompilerFlags.cmake
)
message("Compile flags: ${MY_COMPILE_FLAGS}")

# ------------ INCLUDE DIRECTORIES ------------
message(STATUS "Adding include directories")
message(STATUS "Adding include directories of the project")
# Must be added before linking libraries
target_include_directories(game
        PRIVATE
        ${INCLUDE_DIR} # This is where the header files for the project are located
)
message(STATUS "Adding include directories of the libraries")
target_include_directories(game
        SYSTEM # This is needed to suppress warnings, we don't want to see warnings from the libraries
        PRIVATE
        ${LIB_INCLUDE_DIR} # This is where the library header files are located
        ${Boost_INCLUDE_DIRS} # This is where the boost header files are located
)
message(STATUS "Include directories added: ${INCLUDE_DIR} ${LIB_INCLUDE_DIR} ${Boost_INCLUDE_DIRS}")

# ------------ LINKING LIBRARIES ------------
message(STATUS "Adding linking libraries")

# Instruct the linker to link your program statically with the libraries it depends on
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

message(STATUS "Adding linking libraries of the project")

target_link_directories(game PRIVATE
        ${LIB_STATIC_DIR} # This is where the static libraries are located
        # This is defined in FileLocations.cmake
)
target_link_libraries(game
        ${MAIN_LIBS} # These are the libraries that the project depends on
        # Defined in LinkedLibraries.cmake
)


if (BUILD_TESTING)
    target_include_directories(game_test PRIVATE
            # Libraries that are needed for the tests
            ${INCLUDE_DIR} # This is where the header files for the project are located
            ${LIB_INCLUDE_DIR} # This is where the library header files are located
            ${Boost_INCLUDE_DIRS} # This is where the boost header files are located
            # Defined in FileLocations.cmake
    )
    # Link libraries for the test executable
    target_link_libraries(game_test
            gtest_main # This is the google test library, needed for the tests
            ${MAIN_LIBS} # These are the libraries that the project depends on
            # Defined in LinkedLibraries.cmake
    )
endif ()


# ------------ BUILD TYPES ------------
# This applies to all targets created
message("Applying flags on the build type")
# ............ DEBUG ............
set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS}")
# ............ RELEASE ............
set(CMAKE_CXX_FLAGS_RELEASE "${RELEASE_FLAGS}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Build type: Debug")
    message("Applied flags: ${CMAKE_CXX_FLAGS_DEBUG}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Build type: Release")
    message("Applied flags: ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()