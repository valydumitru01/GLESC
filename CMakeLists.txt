# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.10)
# Main project name
project(game)
# The c++ version used
set(CMAKE_CXX_STANDARD 20)
# Ensure that the compiler supports the c++ version
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enables CMake code to be forward compatible with newer versions of CMake.
cmake_policy(SET CMP0074 NEW)

find_package(Boost REQUIRED)


# ------------ FOLDER LOCATIONS ------------

# ............ Project Files ............
# Set the source directory, this is where the source files are located
set(SRC_DIR src)
# Set the include directory, this is where the header files are located
set(INCLUDE_DIR include)
# .........................................

# ............ Library Files ............
# Set the include directory for the library, this is where the library header files are located
set(LIB_INCLUDE_DIR lib/include)
# Set the source directory for the library, this is where the library source files are located
set(LIB_SRC_DIR ${LIB_INCLUDE_DIR}) # Src and include are the same for the library
# Set the static library directory, this is where the static library files (.a extension) are located
set(LIB_STATIC_DIR lib/lib)
# Set the test directory, this is where the test files are located
# .........................................


# ............ Test Files ............
set(TEST_DIR tests)
# .........................................


# ............ Binaries ............
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)
# .........................................


# ------------ FILES ------------
# We're using GLOB_RECURSE to obtain all the files in the directories
# It will be necessary to re-run cmake if you add new files to the project

# Obtain all the source files in the source directory
file(GLOB_RECURSE SOURCE_FILES "${SRC_DIR}/*.cpp")
# Obtain all the source files in the library source directory
file(GLOB_RECURSE LIB_SOURCE_FILES "${LIB_SRC_DIR}/*.cpp")

# Obtain all the test files in the test directory
file(GLOB_RECURSE TEST_FILES "${TEST_DIR}/*.cpp")

# Obtain the vertex shader files in the source directory
file(GLOB_RECURSE VERT_SHADER "${SRC_DIR}/*.vert")
# Obtain the fragment shader files in the source directory
file(GLOB_RECURSE FRAG_SHADER "${SRC_DIR}/*.frag")

# ------------ COMPILER FLAGS ------------
# We're setting the compiler flags only for the files in the source directory, not the library files
# That is why we're using set_source_files_properties instead of target_compile_options
# Also we're using list instead of string because it allows us to add comments to the flags

# Initialize an empty list to store compile flags
set(compile_flags "")

# Append flags one by one (with comments)
list(APPEND compile_flags "-Wall")           # Enable all warnings
list(APPEND compile_flags "-Wextra")          # Enable extra warnings
list(APPEND compile_flags "-Wpedantic")       # Enable pedantic warnings
list(APPEND compile_flags "-Wshadow")         # Warn if a variable declaration shadows one from a parent context
list(APPEND compile_flags "-Wconversion")     # Warn for implicit conversions that may alter a value
list(APPEND compile_flags "-Wuninitialized")  # Warn if an automatic variable is used without first being initialized
list(APPEND compile_flags "-Wold-style-cast") # Warn for c-style casts
list(APPEND compile_flags "-Wfloat-equal")    # Warn if floating point values are used in equality comparisons
list(APPEND compile_flags "-Wcast-qual")      # Warn if a pointer is cast so as to remove a type qualifier
list(APPEND compile_flags "-Wcast-align")     # Warn for potential performance problem casts

# Convert the list to a single string separated by spaces
string(JOIN " " final_compile_flags ${compile_flags})

# Apply the flags to your source files
set_source_files_properties(
        ${SOURCE_FILES} ${INCLUDE_FILES} ${TEST_FILES}
        PROPERTIES
        COMPILE_FLAGS ${final_compile_flags}
)
# ------------ EXECUTABLE ------------
# Add an executable target called game to be built from the source files
add_executable(game ${SOURCE_FILES} ${LIB_SOURCE_FILES})

# ------------ PLATFORM DETECTION ------------
# Defining custom variables to detect the platform
if (WIN32)
    set(WINDOWS TRUE)
elseif (UNIX AND NOT APPLE)
    set(LINUX TRUE)
elseif (APPLE)
    set(APPLE TRUE)
endif ()

# This allows the project to be built on different platforms
if (WINDOWS)
    target_compile_definitions(game PRIVATE __WINDOWS__)
elseif (LINUX)
    target_compile_definitions(game PRIVATE __LINUX__)
elseif (APPLE)
    target_compile_definitions(game PRIVATE __APPLE__)
endif ()

# ------------ MACRO DEFINITIONS ------------

# This is needed to allow the shaders to be loaded
target_compile_definitions(game PRIVATE FRAG_SHADER="${FRAG_SHADER}")
target_compile_definitions(game PRIVATE VERT_SHADER="${VERT_SHADER}")

# This is needed to allow stacktraces to be printed
target_compile_definitions(game PRIVATE PROJECT_NAME="${PROJECT_NAME}")

# This is also needed to allow stacktraces to be printed
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(game PRIVATE PROJECT_BINARY_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(game PRIVATE PROJECT_BINARY_DIR="${PROJECT_BINARY_DIR_RELEASE_RELEASE}")
endif ()



# This is needed to allow the glew library (glew32s.lib) to be linked statically
target_compile_definitions(game PRIVATE GLEW_STATIC)

# ------------ INCLUDE DIRECTORIES ------------
# Must be added before linking libraries
target_include_directories(game
        PRIVATE
        ${INCLUDE_DIR} # This is where the header files for the project are located
)
target_include_directories(game
        SYSTEM # This is needed to suppress warnings, we don't want to see warnings from the libraries
        PRIVATE
        ${LIB_INCLUDE_DIR} # This is where the library header files are located
        ${Boost_INCLUDE_DIRS} # This is where the boost header files are located
)

# ------------ LINKING LIBRARIES ------------
# Instruct the linker to link your program statically with the libraries it depends on
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
# This specifies the location of the static libraries to link
target_link_directories(game PRIVATE ${LIB_STATIC_DIR})


target_link_libraries(game
        mingw32 # This is needed to allow the project to be built on different platforms
        SDL2 # This is the SDL library, Simple DirectMedia Layer, used for window creation and input handling
        SDL2main # This is the main component of the SDL library
        SDL2_net # This is the networking component of the SDL library
        SDL2_mixer # This is the audio component of the SDL library
        SDL2_image # This is the image component of the SDL library
        glew32s # This is the glew library, OpenGL Extension Wrangler, used to load OpenGL functions
)
if (WINDOWS)
    target_link_libraries(game
            opengl32 # This is the OpenGL library, used for rendering, specific for Windows
            imm32 # library is a component of Microsoft Windows that provides Input Method Editor (IME) capabilities,
                  # This is necessary for the SDL library, it allows more characters than the standard keyboard
            DbgHelp # Debug Help Library, It allows stacktraces to be printed in Windows
            version # This is a dependency of the SDL library,
                    # is used on Windows to obtain version information about operating system
                    # components, files, and other resources
            setupapi # This is a dependency of the SDL library,
                     # handles installation, enumeration, and management of hardware devices
            winmm # This is a dependency of the SDL library,
                  # Windows-specific library that provides a range of multimedia functionalities,
                  # such as playing sound files, providing timers, and accessing joysticks
    )
elseif (LINUX)
    # TODO: Add libraries for Linux
elseif (APPLE)
    # TODO: Add libraries for Mac
endif ()


# ------------ BUILD TYPES ------------
# ............ DEBUG ............
set(DEBUG_FLAGS
        "-O0" # Optimization flag, no optimization
        "-g"  # Produce debugging information
        "-ggdb" # Produce debugging information for gdb
)
string(JOIN " " CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})

# ............ RELEASE ............
set(RELEASE_FLAGS
        "-O3" # Optimization flag, -O3 is not always faster than -O2 TODO: Test which one is faster
        "-DRELEASE" # Enable miscellaneous release features
        "-DNDEBUG" # This disables the assert statements, avoiding the overhead of checking the condition
        "-DNLOGGING" # This disables the logging statements, avoiding the overhead of writing to the log file
        "-DDEBUG_GAPI" # This disables debugging for graphics API, avoiding the overhead
        "-flto" # Link time optimization, optimizes code at link time but increases compilation time
        "-s" # Strip symbols from binary, reduces the size of the binary but makes debugging harder
)
string(JOIN " " CMAKE_CXX_FLAGS_RELEASE ${RELEASE_FLAGS})

###################################
# ------------ TESTING -----------
# --------------------------------
# Here we're using the googletest library to test our code

# Download and unpack googletest at configure time
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(game_test ${TEST_FILES} ${LIB_SOURCE_FILES})
target_include_directories(game_test PRIVATE ${INCLUDE_DIR} ${LIB_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(game_test gtest_main)
enable_testing()
add_test(NAME MyGameTest COMMAND game_test)