function(log  msg mode color bold)
  # Set default values if not provided
  if("${mode}" STREQUAL "")
    set(mode "STATUS")
  endif()

  if("${color}" STREQUAL "")
    set(color "white")
  endif()

  if("${bold}" STREQUAL "")
    set(bold FALSE)
  endif()

  # Color mapping
  if(${color} STREQUAL "red")
    set(color_code "31")
  elseif(${color} STREQUAL "green")
    set(color_code "32")
  elseif(${color} STREQUAL "blue")
    set(color_code "34")
  elseif(${color} STREQUAL "yellow")
    set(color_code "33")
  elseif(${color} STREQUAL "magenta")
    set(color_code "35")
  elseif(${color} STREQUAL "white")
    set(color_code "37")
  else()
    set(color_code "0")
  endif()

  # Bold mapping
  if(${bold})
    set(bold_code "1")
  else()
    set(bold_code "0")
  endif()

  string(ASCII 27 Esc)
  message(${mode} "${Esc}[${bold_code};${color_code}m${msg}${Esc}[0m")
endfunction()

function(warning msg)
  log("${msg}" "WARNING" "yellow" TRUE)
endfunction()

function(error msg)
  log("${msg}" "FATAL_ERROR" "red" TRUE)
endfunction()

function(verbose_info msg)
  log("${msg}" "VERBOSE" "white" TRUE)
endfunction()

function(info msg)
  log("${msg}" "STATUS" "" FALSE)
endfunction()

function(important_info msg)
  log("${msg}" "STATUS" "blue" TRUE)
endfunction()

function(success msg)
  log("${msg}" "STATUS" "green" TRUE)
endfunction()

function(debug msg)
  log("__DEBUG__MESSAGE__:" "DEBUG" "magenta" TRUE)
  log("    ${msg}" "DEBUG" "magenta" TRUE)
endfunction()
