cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Set up include directories
include_directories(include)
include_directories(lib/include)

# Set up library directories
link_directories(lib/lib)

# Set up source files
set(SOURCES
        src/core/main.cpp
        )

# Add libraries
set(LIBRARIES
        SDL2
        SDL2_image
        SDL2_net
        SDL2_mixer
        GLEW
        )

# Add executable
add_executable(MyProject ${SOURCES})

# Link libraries to executable
target_link_libraries(MyProject ${LIBRARIES})


