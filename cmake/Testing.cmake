#------------ TESTING -----------
# Here we're using the googletest library to test our code
find_package(GTest)
include(FetchContent)

message(STATUS "Fetching Google Test")
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
message(STATUS "Google Test fetched")

# Force Google Test to use shared runtime libraries
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Enable CMake's testing capabilities
enable_testing()
# Add a new test named MyGameTest that will run the command 'game_test'
add_test(NAME MyGameTest COMMAND game_test)