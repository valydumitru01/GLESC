# ==========================================================
# ================== FIND PACKAGES MODULE ==================
# ==========================================================
# Module description:
#   This module is in charge of providing functions
#   for function finding for the project

# **********************************************************
# ~~~~~~~~~~~~~~~~~~ Module initialization ~~~~~~~~~~~~~~~~~
# **********************************************************

set(common_packages
    Boost
    CACHE INTERNAL "" FORCE)

# **********************************************************
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# **********************************************************

# ----------------------------------------------------------
# Function: find_all_packages
# Description:
#   This function finds all packages that are passed as a
#   parameter. It's a utility function for finding packages
#   in a data oriented way.
# ----------------------------------------------------------
function(find_all_packages packages)

  foreach (package ${packages})
    find_package(${package} REQUIRED)
    if (${package}_FOUND)
      success("${package} found")
      # Apparently, the include directories are not set in the cache
      set("${package}_INCLUDE_DIRS" ${${package}_INCLUDE_DIRS} CACHE INTERNAL "" FORCE)
    endif ()
  endforeach ()

endfunction()


# ----------------------------------------------------------
# Function: find_common_packages
# Description:
#   This function finds common packages that are
#   required for the project. Currently, it looks
#   for the Boost library.
# ----------------------------------------------------------
function(find_common_packages)

  important_info("Finding common packages
\t\tPackages to find: ${common_packages}")
  find_all_packages("${common_packages}")
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
function(find_extra_packages packages)
  important_info("Finding extra packages
\t\tExtra packages to find: ${packages}")
  find_all_packages("${packages}")
endfunction()