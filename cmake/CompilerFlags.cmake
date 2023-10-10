# ------------ COMPILER FLAGS ------------
# We're setting the compiler flags only for the files in the source directory, not the library files
# That is why we're using set_source_files_properties instead of target_compile_options
# Also we're using list instead of string because it allows us to add comments to the flags

# Initialize an empty list to store compile flags
set(aux_compile_flags "")

# Append flags one by one (with comments)
list(APPEND aux_compile_flags "-Wall")           # Enable all warnings
list(APPEND aux_compile_flags "-Wextra")          # Enable extra warnings
list(APPEND aux_compile_flags "-Wpedantic")       # Enable pedantic warnings
list(APPEND aux_compile_flags "-Wshadow")         # Warn if a variable declaration shadows one from a parent context
list(APPEND aux_compile_flags "-Wconversion")     # Warn for implicit conversions that may alter a value
list(APPEND aux_compile_flags "-Wuninitialized")  # Warn if an automatic variable is used without first being initialized
list(APPEND aux_compile_flags "-Wold-style-cast") # Warn for c-style casts
list(APPEND aux_compile_flags "-Wfloat-equal")    # Warn if floating point values are used in equality comparisons
list(APPEND aux_compile_flags "-Wcast-qual")      # Warn if a pointer is cast so as to remove a type qualifier
list(APPEND aux_compile_flags "-Wcast-align")     # Warn for potential performance problem casts

# Convert the list to a single string separated by spaces
string(JOIN " " MY_COMPILE_FLAGS ${aux_compile_flags})


set(aux_debug_flags
        "-O0" # Optimization flag, no optimization
        "-g"  # Produce debugging information
        "-ggdb" # Produce debugging information for gdb
        #"-v" # Verbose output
)

string(JOIN " " DEBUG_FLAGS ${aux_debug_flags})

set(aux_release_flags
        "-O3" # Optimization flag, -O3 is not always faster than -O2 TODO: Test which one is faster
        "-DRELEASE" # Enable miscellaneous release features
        "-DNDEBUG" # This disables the assert statements, avoiding the overhead of checking the condition
        "-DNLOGGING" # This disables the logging statements, avoiding the overhead of writing to the log file
        "-DDEBUG_GAPI" # This disables debugging for graphics API, avoiding the overhead
        "-flto" # Link time optimization, optimizes code at link time but increases compilation time
        "-s" # Strip symbols from binary, reduces the size of the binary but makes debugging harder
)

string(JOIN " " RELEASE_FLAGS ${aux_release_flags})
