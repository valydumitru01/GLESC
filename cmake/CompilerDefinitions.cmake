# ·················· MODULE DEPENDENCIES ···················
include_cmake_once(FileLocations.cmake)
include_cmake_once(PlatformDetection.cmake)
# ··························································




# ==========================================================
# =================== DEFINITIONS MODULE ===================
# ==========================================================
# Module description:
#   This module is in charge to provide functions to add
#   definitions to targets.
#   For example, the platform the project will be added as a
#   definition -DPLATFORM="Linux" to the target.




# ----------------------------------------------------------
# Function: set_common_definitions
# Description:
#   This function adds common definitions to a target.
#   Common definitions are those that are needed for the
#   project to work properly.
#   Added definitions:
#       - PLATFORM
#           Linux, Windows, etc.
#       - GLEW_STATIC
#           This is needed for glew to work statically
#       - FRAG_SHADER
#           This is the fragment shader file
#       - VERT_SHADER
#           This is the vertex shader file
#       - PROJECT_NAME
#           This is the name of the executable
#       - PROJECT_BINARY_DIR
#           This is the binary directory of the project
# Parameters:
#   target: The target to add the definitions to.
# ----------------------------------------------------------
function(set_common_definitions target)
  message(STATUS "Adding common definitions to ${target}")

  # Set project binary directory based on build type
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PROJECT_BINARY_DIR
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(PROJECT_BINARY_DIR
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")
  endif ()

  # Store all definitions in a list
  set(defs
      # This is the platform the project is being
      # built on
      ${PLATFORM}
      # This is needed for glew to work statically
      GLEW_STATIC
      # This is the fragment shader file location
      FRAG_SHADER="${FRAG_SHADER}"
      # This is the vertex shader file location
      VERT_SHADER="${VERT_SHADER}"
      # This is the name of the executable
      PROJECT_NAME="${PROJECT_NAME}"
      # This is the binary directory of the project,
      # it is needed for stack traces to work
      PROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}"
  )

  # Apply definitions to the target
  target_compile_definitions(${target} PRIVATE ${defs})

  # Verbose log of all definitions
  message(VERBOSE "Added definitions to ${target}:")
  foreach (def IN LISTS defs)
    message(VERBOSE "  ${def}")
  endforeach ()
endfunction()




# ----------------------------------------------------------
# Function: add_extra_definitions
# Description:
#   This function adds extra definitions to a target.
#   Extra definitions are those that are needed for a
#   specific target to work properly.
# Parameters:
#   target: The target to add the definitions to.
#   defs: The definitions to add.
# ----------------------------------------------------------
function(add_extra_definitions target defs)
  message(STATUS "Adding extra definitions to ${target}")
  target_compile_definitions(${target} PRIVATE ${defs})
  message(VERBOSE
      "Added definitions to ${target}: ${defs}")
endfunction()