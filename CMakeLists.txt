cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
# ------------ FOLDER LOCATIONS ------------
set(SRC_DIR src)
set(LIB_INCLUDE_DIR lib/include)
set(LIB_SRC_DIR ${LIB_INCLUDE_DIR}) # Src and include are the same for the library
set(INCLUDE_DIR include)
set(LIB_STATIC_DIR lib/lib)
set(TEST_DIR tests)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)


# ------------ SOURCE FILES ------------
file(GLOB_RECURSE SOURCE_FILES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE LIB_SOURCE_FILES "${LIB_SRC_DIR}/*.cpp")
file(GLOB_RECURSE TEST_FILES "${TEST_DIR}/*.cpp")
file(GLOB_RECURSE VERT_SHADER "${SRC_DIR}/*.vert")
file(GLOB_RECURSE FRAG_SHADER "${SRC_DIR}/*.frag")

# ------------ MACRO DEFINITIONS ------------
add_definitions(-DPROJECT_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\")
set(PROJECT_BINARY_DIR_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug")
add_definitions(-DPROJECT_NAME=\"${PROJECT_NAME}\")

add_definitions(-DFRAG_SHADER=\"${FRAG_SHADER}\")
add_definitions(-DVERT_SHADER=\"${VERT_SHADER}\")

# Get the binary directory for the current build type
set(PROJECT_BINARY_DIR_RELEASE "${CMAKE_SOURCE_DIR}/bin/release")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DPROJECT_BINARY_DIR=\"${PROJECT_BINARY_DIR_DEBUG}\")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DPROJECT_BINARY_DIR=\"${PROJECT_BINARY_DIR_RELEASE}\")
endif ()


if (WIN32)
    add_definitions(-D__WINDOWS__ -DGLEW_STATIC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-D__LINUX__)
elseif (APPLE)
    add_definitions(-D__MAC__)
endif ()

# ------------ EXECUTABLE ------------
add_executable(game ${SOURCE_FILES} ${LIB_SOURCE_FILES}
        include/engine/core/debugger/Debugger.h
        include/engine/subsystems/input/debugger/InputDebugger.h
        include/engine/core/math/debugger/MathDebugger.h)


# ------------ INCLUDE DIRECTORIES ------------
# Must be added before linking libraries
target_include_directories(game PRIVATE ${INCLUDE_DIR} ${LIB_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

# ------------ LINKER FLAGS AND LIBRARIES ------------

if (WIN32)
    target_link_libraries(game DbgHelp)
    target_link_directories(game PRIVATE ${LIB_STATIC_DIR})
    target_link_libraries(game mingw32 SDL2main SDL2 SDL2_net
            SDL2_mixer SDL2_image glew32s opengl32 glu32 imm32 version setupapi winmm)
elseif (UNIX AND NOT APPLE)
    # Modify the library paths and names according to your system configuration
    target_link_libraries(game mingw32 SDL2main SDL2 SDL2_net
            SDL2_mixer SDL2_image glew32s opengl32 glu32 imm32 version setupapi winmm)
elseif (APPLE)
    # Modify the library paths and names according to your system configuration
    target_link_libraries(game mingw32 SDL2main SDL2 SDL2_net
            SDL2_mixer SDL2_image glew32s opengl32 glu32 imm32 version setupapi winmm)
endif ()

# ------------ COMPILER FLAGS ------------
if (WIN32)
    target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic)
elseif (UNIX AND NOT APPLE)
    target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic)
elseif (APPLE)
    target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic)
endif ()
# ------------ BUILD TYPES ------------
# ............ DEBUG ............
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0") # Optimization flag, no optimization
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG") #Define DEBUG macro
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g") #Produce debugging information
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb") #Produce debugging information for gdb
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG") #Define _DEBUG macro
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG") #Define DEBUG macro
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_LOGGING") #Define DEBUG_LOGGING macro

add_custom_target(preprocess ALL)

# ............ RELEASE ............
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" "-O3") # Optimization flag, -O3 is not always faster than -O2
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" "-DRELEASE") #Define RELEASE macro
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" "-DNDEBUG") #Define NDEBUG macro
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" "-DDEBUG_LOGGING") #Define DEBUG_LOGGING macro
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" "-flto") #Link time optimization
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" "-s") #Strip symbols from binary

###################################
# ------------ TESTING -----------
# --------------------------------

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