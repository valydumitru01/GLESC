cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add find_package for Boost
find_package(Boost REQUIRED)
# ------------ FOLDER LOCATIONS ------------
set(SRC_DIR src)
set(LIB_SRC_DIR lib/src)
set(INCLUDE_DIR include)
set(LIB_STATIC_DIR lib/lib)
set(LIB_INCLUDE_DIR lib/include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)


# ------------ SOURCE FILES ------------
file(GLOB_RECURSE SOURCE_FILES "${SRC_DIR}/**/*.cpp")
file(GLOB_RECURSE LIB_SOURCE_FILES "${LIB_SRC_DIR}/*.cpp")

# ------------ MACRO DEFINITIONS ------------
add_definitions(-DPROJECT_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\")
set(PROJECT_BINARY_DIR_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug")
add_definitions(-DPROJECT_NAME=\"${PROJECT_NAME}\")

# Get the binary directory for the current build type
set(PROJECT_BINARY_DIR_RELEASE "${CMAKE_SOURCE_DIR}/bin/release")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DPROJECT_BINARY_DIR=\"${PROJECT_BINARY_DIR_DEBUG}\")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DPROJECT_BINARY_DIR=\"${PROJECT_BINARY_DIR_RELEASE}\")
endif()


if (WIN32)
    add_definitions(-D__WINDOWS__ -DGLEW_STATIC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-D__LINUX__)
elseif (APPLE)
    add_definitions(-D__MAC__)
endif ()

# ------------ EXECUTABLE ------------
add_executable(game ${SOURCE_FILES} ${LIB_SOURCE_FILES})

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

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DDEBUG -g -ggdb -D_DEBUG -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DRELEASE -DNDEBUG -s -fno-rtti -fno-exceptions")