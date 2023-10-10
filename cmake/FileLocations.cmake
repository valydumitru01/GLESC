# ------------ FILE LOCATIONS ------------

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

file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE LIB_SOURCE_FILES ${LIB_SRC_DIR}/*.cpp)
file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp)

message("Source files: ${SOURCE_FILES}")
message("Library source files: ${LIB_SOURCE_FILES}")
message("Test files: ${TEST_FILES}")

# Obtain the vertex shader files in the source directory
file(GLOB_RECURSE VERT_SHADER "${SRC_DIR}/*.vert")
# Obtain the fragment shader files in the source directory
file(GLOB_RECURSE FRAG_SHADER "${SRC_DIR}/*.frag")