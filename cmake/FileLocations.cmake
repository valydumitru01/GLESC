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


function(set_common_include_dirs target)
    message(STATUS "Adding include directories of the project to ${target}")
    target_include_directories(${target} PRIVATE ${INCLUDE_DIR})
    message(STATUS "Adding include directories of the libraries to ${target}")
    target_include_directories(${target} SYSTEM PRIVATE ${LIB_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
    message(VERBOSE "Added include directories to ${target}:
        ${INCLUDE_DIR}
        ${LIB_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}"
    )
endfunction()

function(add_extra_include_dirs target dirs)
    message(STATUS "Adding extra include directories to ${target}")
    target_include_directories(${target} PRIVATE ${dirs})
    message(VERBOSE "Added include directories to ${target}: ${dirs}")
endfunction()

function(set_common_static_lib_dirs target)
    message(STATUS "Adding static library directories of the project to ${target}")
    target_link_directories(${target} PRIVATE ${LIB_STATIC_DIR})
    message(VERBOSE "Added static library directories to ${target}: ${LIB_STATIC_DIR}")
endfunction()

function(add_extra_static_lib_dirs target dirs)
    message(STATUS "Adding extra static library directories to ${target}")
    target_link_directories(${target} PRIVATE ${dirs})
    message(VERBOSE "Added static library directories to ${target}: ${dirs}")
endfunction()

# function that adds all the common sources to the given target
function(set_common_sources target)
    message(STATUS "Adding common sources to ${target}")
    target_sources(${target} PRIVATE
            ${SOURCE_FILES} # These are the source files for the project
            ${LIB_SOURCE_FILES}# These are the source files for the libraries
    )
    message(VERBOSE "Added sources: ${SOURCE_FILES} ${LIB_SOURCE_FILES} to ${target}")
endfunction()
# function to add extra sources to the given target
function(add_extra_sources target srcs)
    message(STATUS "Adding extra sources to ${target}")
    target_sources(${target} PRIVATE ${srcs})
    message(VERBOSE "Added sources: ${srcs} to ${target}")
endfunction()