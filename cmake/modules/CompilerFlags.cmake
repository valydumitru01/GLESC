# ==========================================================
# ================ COMPILER FLAGS MODULE ===================
# ==========================================================
# Module description:
#   This module is in charge of defining all the compiler
#   flags that will be used in the project.
#   Also it defines functions to apply the flags to the
#   different targets and files.


# **********************************************************
# ~~~~~~~~~~~~~~~~~~ Module initialization ~~~~~~~~~~~~~~~~~
# **********************************************************

verbose_info("Defining compiler flags")
# Defining general compile flags
set(MY_COMPILE_FLAGS
    # Enable all warnings
    "-Wall"
    # Enable extra warnings
    "-Wextra"
    # Enable pedantic warnings
    "-Wpedantic"
    # Warn if a variable declaration shadows one from a
    # parent context
    "-Wshadow"
    # Warn for implicit conversions that may alter a value
    "-Wconversion"
    # Warn if an automatic variable is used without first
    # being initialized
    "-Wuninitialized"
    # Warn for c-style casts
    "-Wold-style-cast"
    # Warn if floating point values are used in equality
    # comparisons
    "-Wfloat-equal"
    # Warn if a pointer is cast so as to remove a type
    # qualifier
    "-Wcast-qual"
    # Warn for potential performance problem casts
    "-Wcast-align"
    # Link statically
    "-static"
    CACHE STRING "Flags used by the compiler during all build types."
)

# Defining debug build flags
set(DEBUG_FLAGS
    # Optimization flag, no optimization
    "-O0"
    # Produce debugging information
    "-g"
    # Produce debugging information for gdb
    "-ggdb"
    # Verbose output, enabled only for specific problems
    #"-v"
    CACHE STRING "Flags used by the compiler during debug builds."
)

# Defining release build flags
set(RELEASE_FLAGS
    # Optimization flag, -O3 is not always faster than -O2
    # TODO: Test which one is faster
    "-O3"
    # Enable miscellaneous release features
    "-DRELEASE"
    # This disables the assert statements, avoiding the
    # overhead of checking the condition
    "-DNDEBUG"
    # This disables the logging statements, avoiding the
    # overhead of writing to the log file
    "-DNLOGGING"
    # This disables debugging for graphics API, avoiding
    # the overhead
    "-DDEBUG_GAPI"
    # Link time optimization, optimizes code at link time
    # but increases compilation time
    "-flto"
    # Strip symbols from binary, reduces the size of the
    # binary but makes debugging harder
    "-s"
    CACHE STRING "Flags used by the compiler during release builds."
)

# **********************************************************
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# **********************************************************




# ----------------------------------------------------------
# Function: set_common_compiler_flags_to_build_type
# Description:
#   This function applies the common compiler flags to the
#   target depending on the build type.
#   This only applies the build type flags which are
#   common to all files.
# Parameters:
#   target: The target to apply the flags to.
# ----------------------------------------------------------
function(set_common_compiler_flags_to_build_type target)
  assert_not_empty(${target})
  important_info("Adding common compile flags to build type for target ${target}")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${target} PRIVATE ${DEBUG_FLAGS})
    success("Flags applied to build type DEBUG: ${DEBUG_FLAGS}")
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${target} PRIVATE ${RELEASE_FLAGS})
    success("Flags applied to build type RELEASE: ${RELEASE_FLAGS}")
  endif ()
endfunction()

# ----------------------------------------------------------
# Function: set_compile_flags_to_common_files
# Description:
#   This function applies all the common compile flags to
#   the common project files.
# ----------------------------------------------------------
function(set_compile_flags_to_common_files)
  assert_not_empty(${SOURCE_FILES})
  assert_not_empty(${TEST_FILES})
  assert_not_empty(${MY_COMPILE_FLAGS})
  important_info("Adding compile flags to common files")
  set_source_files_properties(
      ${SOURCE_FILES} ${TEST_FILES}
      PROPERTIES
      COMPILE_FLAGS
      ${MY_COMPILE_FLAGS}
  )
  verbose_info("The following sources are affected:
\t\t${SOURCE_FILES} ${TEST_FILES}")
  success("Added compile flags: ${MY_COMPILE_FLAGS}")
endfunction()
# ----------------------------------------------------------
# Function: set_compile_flags_to_extra_files
# Description:
#   This function applies the common compile flags to
#   extra files. This is useful when a target needs extra
#   files to be compiled with the same flags as the project
#   files.
# Parameters:
#   files: The files to apply the flags to.
# ----------------------------------------------------------
function(set_compile_flags_to_extra_files files)
  assert_not_empty(${files})
  assert_not_empty(${MY_COMPILE_FLAGS})
  important_info("Adding compile flags to extra files")
  set_source_files_properties(
      ${files}
      PROPERTIES
      COMPILE_FLAGS
      ${MY_COMPILE_FLAGS}
  )
  verbose_info("The following sources are affected:
\t\t${files}")
  success("Added compile flags: ${MY_COMPILE_FLAGS}")
endfunction()