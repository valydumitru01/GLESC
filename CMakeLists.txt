cmake_minimum_required(VERSION 3.10)
project(TFG___OpenGL_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------ FOLDER LOCATIONS ------------
set(SRC_DIR src)
set(LIB_SRC_DIR lib/src)
set(INCLUDE_DIR include)
set(LIB_STATIC_DIR lib/lib)
set(LIB_INCLUDE_DIR lib/include)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# ------------ SOURCE FILES ------------
file(GLOB_RECURSE SOURCE_FILES "${SRC_DIR}/**/*.cpp")
file(GLOB_RECURSE LIB_SOURCE_FILES "${LIB_SRC_DIR}/*.cpp")

# ------------ MACRO DEFINITIONS ------------
add_definitions(-DPROJECT_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\")
if (WIN32)
    add_definitions(-D__WINDOWS__ -DGLEW_STATIC)
elseif (UNIX AND NOT APPLE)
    add_definitions(-D__LINUX__)
elseif (APPLE)
    add_definitions(-D__MAC__)
endif ()

# ------------ EXECUTABLE ------------
add_executable(TFG___OpenGL_Engine ${SOURCE_FILES} ${LIB_SOURCE_FILES})

target_include_directories(TFG___OpenGL_Engine PRIVATE ${INCLUDE_DIR} ${LIB_INCLUDE_DIR})

# ------------ LINKER FLAGS AND LIBRARIES ------------
if (WIN32)
    target_link_directories(TFG___OpenGL_Engine PRIVATE ${LIB_STATIC_DIR})
    target_link_libraries(TFG___OpenGL_Engine mingw32 SDL2main SDL2 SDL2_net
            SDL2_mixer SDL2_image glew32s opengl32 glu32 imm32 version setupapi winmm )
elseif (UNIX AND NOT APPLE)
    # Modify the library paths and names according to your system configuration
    target_link_libraries(TFG___OpenGL_Engine mingw32 SDL2main SDL2 SDL2_net
            SDL2_mixer SDL2_image glew32s opengl32 glu32 imm32 version setupapi winmm )
elseif (APPLE)
    # Modify the library paths and names according to your system configuration
    target_link_libraries(TFG___OpenGL_Engine mingw32 SDL2main SDL2 SDL2_net
            SDL2_mixer SDL2_image glew32s opengl32 glu32 imm32 version setupapi winmm )
endif ()

# ------------ COMPILER FLAGS ------------
if (WIN32)
    target_compile_options(TFG___OpenGL_Engine PRIVATE -Wall -Wextra -Wpedantic)
elseif (UNIX AND NOT APPLE)
    target_compile_options(TFG___OpenGL_Engine PRIVATE -Wall -Wextra -Wpedantic)
elseif (APPLE)
    target_compile_options(TFG___OpenGL_Engine PRIVATE -Wall -Wextra -Wpedantic)
endif ()
# ------------ BUILD TYPES ------------
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DRELEASE")