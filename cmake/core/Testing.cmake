# ==========================================================
# ==================== TESTING MODULE ======================
# ==========================================================
# Module description:
#   This module is responsible for setting up the testings
#   environment. It will download the googletest library
#   and set up the testing command.

# ··························································
# ··················Module Dependencies·····················

include_once(FetchContent)

# ··························································

function(prepare_tests target)
  FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
  )
  FetchContent_GetProperties(googletest)
  important_info("Downloading googletest library...")
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  success("Googletest library downloaded successfully!")

  # Force Google Test to use shared runtime libraries
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  # Enable CMake's testing capabilities
  enable_testing()
  # Add a new test named MyGameTest that will run the command 'game_test'
  add_test(NAME MyGameTest COMMAND game_test)
endfunction()
