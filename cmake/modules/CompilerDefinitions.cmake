# ==========================================================
# =================== DEFINITIONS MODULE ===================
# ==========================================================
# Module description:
#   This module is in charge to provide functions to add
#   definitions to targets.
#   For example, the platform the project will be added as a
#   definition -DPLATFORM="Linux" to the target.

# ··························································
# ··················Module Dependencies·····················

include_cmake_once(modules/FileLocations.cmake)

# ··························································

# **********************************************************
# ~~~~~~~~~~~~~~~~~~ Module initialization ~~~~~~~~~~~~~~~~~
# **********************************************************

# Set project binary directory based on build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(MY_PROJECT_BINARY_DIR
      "${BIN_DIR_DEBUG}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(MY_PROJECT_BINARY_DIR
      "${BIN_DIR_RELEASE}")
endif ()


# Store all definitions in a list
set(MY_DEFINITIONS
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
    PROJECT_BINARY_DIR="${MY_PROJECT_BINARY_DIR}"
    CACHE INTERNAL "Common definitions" FORCE
)

# **********************************************************
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# **********************************************************


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
  assert_not_empty(${target})
  assert_not_empty(${MY_DEFINITIONS})

  important_info("Adding common definitions to target ${target}")
  # Apply definitions to the target
  target_compile_definitions(${target} PRIVATE ${MY_DEFINITIONS})

  # Verbose log of all definitions
  set(defs_string "Added definitions to ${target}:\n\t\t")
  foreach (def IN LISTS MY_DEFINITIONS)
    set(defs_string "${defs_string}${def}\n\t\t")
  endforeach ()
  string(STRIP "${defs_string}" defs_string)
  success("${defs_string}")
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
  important_info( "Adding extra definitions to ${target}")
  target_compile_definitions(${target} PRIVATE ${defs})
  success( "Added definitions to ${target}: ${defs}")
endfunction()