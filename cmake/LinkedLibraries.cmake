# ············· MODULE DEPENDENCIES ·············
include_cmake_once(FileLocations.cmake)
# ···············································


# ==========================================================
# ================ LINKED LIBRARIES MODULE =================
# ==========================================================
# Module description:
#   This module is in charge of providing functions to link
#   the libraries that the project depends on. It also
#   defines the libraries that the project depends on.

# This is the list of all the libraries that are needed to
# build the game
set(MAIN_LIBS
    # This is the tool we use to compile the project, so it
    # is necessary to link it.
    mingw32

    # This is the SDL library, Simple DirectMedia Layer,
    # used for window creation and input handling
    SDL2

    # This is the main component of the SDL library
    SDL2main

    # This is the networking component of the SDL library
    SDL2_net

    # This is the audio component of the SDL library
    SDL2_mixer

    # This is the image component of the SDL library
    SDL2_image

    # This is the glew library, OpenGL Extension Wrangler,
    # used to load OpenGL functions
    glew32s
)
if (WIN32)
  list(APPEND
      MAIN_LIBS
      # This is the OpenGL library, needed to use OpenGL
      # in Windows.
      opengl32

      # library is a component of Microsoft Windows that
      # provides Input Method Editor (IME) capabilities.
      # This is necessary for the SDL library, it allows
      # more characters than the standard keyboard
      imm32

      # Debug Help Library, It allows stacktraces to be
      # printed in Windows.
      # Currently not used, we're using booststacktrace
      # and addr2line.
      # DbgHelp

      # This is a dependency of the SDL library, is used on
      # Windows to obtain version information about operating
      # system components, files, and other resources
      version

      # This is a dependency of the SDL library, handles
      # installation, enumeration, and management of
      # hardware devices
      setupapi

      # This is a dependency of the SDL library,
      # Windows-specific library that provides a range of
      # multimedia functionalities, such as playing sound
      # files, providing timers, and accessing joysticks
      winmm
  )
elseif (LINUX)
  # TODO: Add libraries for Linux
elseif (APPLE)
  # TODO: Add libraries for Mac
endif ()




# ----------------------------------------------------------
# Function: link_common_libs
# Description:
#   This function links the common libraries that the
#   project depends on to the target.
# Parameters:
#   target: The target to link the libraries to.
# ----------------------------------------------------------
function(link_common_libs target)
  message(VERBOSE
      "A new flag has been added to the
            linker: ${CMAKE_EXE_LINKER_FLAGS}")



  message(STATUS
      "Adding linking libraries to ${target}")
  target_link_libraries(${target}
      # These are the libraries that the project depends on.
      # Defined in LinkedLibraries.cmake
      ${MAIN_LIBS}
  )
  message(VERBOSE
      "The linked static libraries are located
      in ${LIB_STATIC_DIR}")
  message(VERBOSE
      "The following libraries have been linked
      to ${target}: ${MAIN_LIBS}")
endfunction()

# ----------------------------------------------------------
# Function: link_extra_libs
# Description:
#   This function links the extra libraries a specific
#   target depends on.
# Parameters:
#   target: The target to link the libraries to.
#   extra_libs: The extra libraries to link to the target.
# ----------------------------------------------------------
function(link_extra_libs target extra_libs)
  message(STATUS "Adding extra linking libraries to ${target}")
  target_link_libraries(${target}
      ${extra_libs}
  )
endfunction()