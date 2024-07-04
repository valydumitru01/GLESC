# ----------------------------------------------------------
# Function: include_cmake_once
# Description:
#   This function is used to include cmake files only once.
#   It creates a variable with the name CMAKE_INCLUDED_<file>
#   and checks if it is defined. If it is not defined, the
#   cmake file is included. If it is defined, the cmake file
#   is not included.
# Parameters:
#   path: The path to the cmake file to include.
# ----------------------------------------------------------
function(include_once path)
  string(REGEX REPLACE "[^a-zA-Z0-9]" "_" cmake_file_upper ${path})
  if (NOT DEFINED CMAKE_INCLUDED_${cmake_file_upper})
    include(${path})
    set(CMAKE_INCLUDED_${cmake_file_upper} TRUE PARENT_SCOPE)
  endif ()
endfunction()

function(include_cmake_once file)
  include_once(cmake/${file})
endfunction()