# ==========================================================
# ================== FIND PACKAGES MODULE ==================
# ==========================================================
# Module description:
#   This module is in charge of providing functions
#   for function finding for the project




# ----------------------------------------------------------
# Function: find_common_packages
# Description:
#   This function finds common packages that are
#   required for the project. Currently, it looks
#   for the Boost library.
# ----------------------------------------------------------
function(find_common_packages)
  message(STATUS "Finding common packages")
  find_package(Boost REQUIRED)
  if (Boost_FOUND)
    message(STATUS "Boost found")
  else ()
    message(FATAL_ERROR "Boost not found")
  endif ()
endfunction()




# ----------------------------------------------------------
# Function: find_extra_package
# Description:
#   This function finds extra packages that are required for
#   the project. It must be use in case a specific target
#   needs a package that is not common for the project.
# Parameters:
#   package: The name of the package to find.
# ----------------------------------------------------------
function(find_extra_package package)
  message(STATUS "Finding extra package ${package}")
  find_package(${package} REQUIRED)
  if (${package}_FOUND)
    message(STATUS "${package} found")
  else ()
    message(FATAL_ERROR "${package} not found")
  endif ()
endfunction()