# Code Style Guide for GLESC engine
## [Direct Link to C++ Code Style Guide](#c-code-style-guide)
## [Direct Link CMake Code Style Guide](#cmake-code-style-guide)


**Table of Contents**
<!-- TOC -->
* [Code Style Guide for GLESC engine](#code-style-guide-for-glesc-engine)
  * [Direct Link to C++ Code Style Guide](#direct-link-to-c-code-style-guide)
  * [Direct Link CMake Code Style Guide](#direct-link-cmake-code-style-guide)
* [C++ Code Style Guide](#c-code-style-guide)
  * [Files](#files)
  * [Code practices](#code-practices)
    * [Class Definition](#class-definition)
      * [Separation of Definition and Implementation](#separation-of-definition-and-implementation)
        * [Example of a Class Definition](#example-of-a-class-definition)
      * [Example of Templates](#example-of-templates)
      * [Access Restriction Order](#access-restriction-order)
        * [Example](#example)
      * [Friend Classes and Methods](#friend-classes-and-methods)
        * [Example](#example-1)
    * [Namespaces](#namespaces)
      * [Example of Namespace Declaration](#example-of-namespace-declaration)
      * [Example of Namespace Usage](#example-of-namespace-usage)
    * [Forward Declarations](#forward-declarations)
    * [Comments](#comments)
        * [Example](#example-2)
        * [Example](#example-3)
    * [Variable Initialization](#variable-initialization)
    * [Scopes](#scopes)
        * [Example](#example-4)
    * [Directives](#directives)
      * [Include](#include)
      * [Define](#define)
      * [Pragma](#pragma)
    * [Cast](#cast)
    * [Pointers](#pointers)
    * [Loops](#loops)
    * [Functions](#functions)
      * [Function parameters](#function-parameters)
    * [Error Handling](#error-handling)
      * [Example of custom asserts usage](#example-of-custom-asserts-usage)
  * [Testing](#testing)
  * [Naming](#naming)
    * [Example macro naming](#example-macro-naming)
    * [Example class naming](#example-class-naming)
    * [Example variable naming](#example-variable-naming)
    * [Example function naming](#example-function-naming)
    * [Example namespace naming](#example-namespace-naming)
    * [Example enum naming](#example-enum-naming)
    * [Example struct naming](#example-struct-naming)
  * [Formatting](#formatting)
    * [Braces](#braces)
    * [Indentation](#indentation)
    * [Line Length](#line-length)
* [CMake Code Style Guide](#cmake-code-style-guide)
  * [General Guidelines](#general-guidelines)
      * [Example of visual separators](#example-of-visual-separators)
      * [Example single line comments](#example-single-line-comments)
      * [Example function comments and multi-line comments](#example-function-comments-and-multi-line-comments)
  * [Formatting](#formatting-1)
    * [Indentation](#indentation-1)
    * [Line Length](#line-length-1)
    * [Spacing](#spacing)
      * [Example](#example-5)
    * [Name conventions](#name-conventions)
      * [Example variables](#example-variables)
      * [Example functions](#example-functions)
      * [Example targets](#example-targets)
<!-- TOC -->

# C++ Code Style Guide

## Files

1. Use the extension `.cpp` for implementation and `.h` for headers.
3. Use kebab-case for file naming.
4. Group related files in the same directory, this is very important for the organization of the project.

## Code practices

### Class Definition

#### Separation of Definition and Implementation

- **Definitions** of classes should be in header files (`.h`), and **implementation** should be in source
  files (`.cpp`). Exceptions are templates and inline functions.

##### Example of a Class Definition

```c++
class Example {
private:
    void doSomething();
};

// In Example.cpp
void Example::doSomething() {
    std::cout << "I’m doing stuff!" << std::endl;
}
```

**Reason**: This is a widely recognized standard in the C++ community and has significant benefits. Methods that use
templates should be implemented in the same header file, immediately following the class definition.

#### Example of Templates

```c++
class Example {
private:
    template <typename T>
    void doSomething();
};

// In the same Example.h
template <typename T>
void Example::doSomething() {
    std::cout << "I’m doing stuff with a template" << typeid(T).name << std::endl;
}
```

**Reason**: Templates need to know the code at compile time, and headers don't know about their implementation
files (`cpp`) until link time, which occurs later. Implementing templates immediately after the class definition
simulates this separation and keeps the code compact.

#### Access Restriction Order

- Follow a classic style where members are ordered from least to most restrictive access.

##### Example

```c++
class Example {
public:
    // Declarations
protected:
    // Declarations
private:
    // Declarations
};
```

#### Friend Classes and Methods

- The definition of friend classes and methods should be right below the class name in the header.

##### Example

```c++
class Example {
    friend class FriendClassExample;
    friend void ExampleClass::exampleMethodInClass(int exampleParam);
    friend void exampleMethod(int exampleParam);
public:
    // Declarations
protected:
    // Declarations
private:
    // Declarations
};
```

### Namespaces

- Use namespaces to avoid naming conflicts and to organize code.
- Use namespaces to group related classes, functions, and variables.
- Use namespaces to avoid polluting the global namespace.
- Use namespaces to improve code readability and maintainability.
- Use namespaces to avoid naming conflicts with third-party libraries.
- Namespaces must be nested without nesting indentation.

#### Example of Namespace Declaration

```c++ 
// Good
namespace GLESC::Module::Submodule {}
// Bad
namespace GLESC { namespace Module { namespace Submodule {} } }
```

#### Example of Namespace Usage

```c++
namespace GLESC {
    class Point {
    }; // class Point
    
    class Mesh {
    }; // class Mesh
} // namespace GLESC
```

### Forward Declarations

- Avoid using forward declarations.

**Reasons**:

1. Forward declarations can hide dependencies and lead to problems with significant changes in the header file.
2. They make it difficult for automatic tools to find symbol definitions.
3. They can break with library changes.
4. Forward declarations of `std::` namespace are not allowed and result in undefined behavior.
5. Deciding between a forward declaration and a full include can silently change code behavior.
6. Using multiple forward declarations can be more verbose than including the header.
7. Structuring code to allow forward declarations can make it slower and more complex.

### Comments

1. No grammatical errors.
2. In headers, use Doxygen-style block comments with tags.

##### Example

```
/**
  * @brief description
  * @details details
  * 
  * @tparam tparameter description
  * @param parameter description
  * @return return description
  */
```

3. Within methods, use single-line comments above the desired code.

##### Example

```c++
// Core functions of OpenGL a.k.a. full modern OpenGL functionality.
// More info: https://wiki.libsdl.org/SDL_GLprofile
setGlAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
```

4. Follow good practices:

- Comments should not duplicate code.
- Good comments do not excuse confusing code.
- If you can't write a clear comment, there may be a problem with the code.
- Comments should dispel confusion, not cause it.
- Explain non-idiomatic code in comments.
- Provide links to the original source of copied code.
- Include links to external references where useful.
- Add comments when fixing bugs.
- Use comments to mark incomplete implementations.

### Variable Initialization

1. Initialize variables in the class constructor's initializer list, unless explicitly needed otherwise.
2. Prefer initializing variables using `{}` instead of `=` unless there is a compelling reason.

### Scopes

For large scope definitions (classes, namespaces, structs), indicate the scope name along with its type.

##### Example

```c++
namespace GLESC {
    struct Point {
    }; // struct Point

    class Mesh 
    }; // class Mesh
} // namespace GLESC
```

### Directives

#### Include

- Use `< >` for libraries and `""` for your headers. This helps the preprocessor quickly find what is included.
- For a consistent style, follow this order in source files:
    - The header being implemented, with `""`.
    - Necessary external library headers, with `< >`.
    - Necessary internal headers, with `""`.

#### Define

- Use the same style as functions defined within classes.

#### Pragma

- Use `#pragma once` instead of `#ifdef`.
- Use `#pragma` in all header files to avoid repeated inclusion of headers. This significantly reduces compilation time.
- `#pragma once` is preferred over `#ifdef` guards because it is simpler, requires less code, and is widely supported by
  most compilers.

### Cast

1. Use `static_cast` for casting. Never use C-style casts.

```c++
// Good
float x = static_cast<float>(var);

// Bad
float x = (float)var;
```

### Pointers

1. Use `nullptr` instead of `NULL` or `0`.

```c++
// Good
int* x = nullptr;

// Bad
int* x = NULL;
int* x = 0;
```

2. Use `std::unique_ptr` or `std::shared_ptr` instead of raw pointers when possible. This helps avoid memory leaks.
   With the exception of functions or classes that do not need to manage memory.

```c++
// Good
std::unique_ptr<int> x = std::make_unique<int>(5);

// Bad
int* x = new int(5);
```

### Loops

1. Use range-based loops when possible.

```c++
// Good
std::vector<int> vec = {1, 2, 3, 4, 5};
for (const auto& i : vec) {
    std::cout << i << std::endl;
}

// Bad
for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
}
```

**Reason**: Range-based loops are more readable and less error-prone.

### Functions

1. Use `const` whenever possible.
2. Use `noexcept` when a function does not throw exceptions.
3. Use `override` when overriding a virtual function.
4. Use `final` when a function should not be overridden.
5. Use `delete` when a function should not be used.
6. Use `default` when a function should use the default implementation.
7. Use `explicit` when a constructor should not be used for implicit conversions.
8. Use `inline` for small functions.
9. Use `constexpr` for functions that can be evaluated at compile time.
10. Use `[[nodiscard]]` for functions that should not be ignored.
11. Use `[[maybe_unused]]` for functions that are not used.

**Reason**: These keywords help the compiler optimize the code and prevent errors.
They also make the code more readable.

#### Function parameters

1. Use `const` for parameters that should not be modified.
2. Use `&` for parameters that should not be copied.
3. Use `&&` for parameters that should be moved.

### Error Handling

1. Use the custom asserts defined in the `Assert.h` file.
2. Avoid using exceptions for error handling, for a game engine, exceptions are not recommended. Asserts make the code
   more readable and prevent errors. If the state is invalid, the program should crash, avoiding silent errors.

#### Example of custom asserts usage

```c++
// Good
void doSomething(int* ptr, bool boolVar) {
    D_ASSERT_NOT_NULLPTR(ptr);
    D_ASSERT_FALSE(boolVar);
    // Do something
}

// Bad
void doSomething(int* ptr, bool boolVar) {
    if (ptr == nullptr) {
        throw std::invalid_argument("ptr is null");
    }
    if (boolVar) {
        throw std::invalid_argument("boolVar is true");
    }
    // Do something
}
```

## Testing

1. Use unit tests to test individual components.
2. Use integration tests to test the interaction between components.
3. Use end-to-end tests to test the entire system.

## Naming

1. General code: camelCase
2. Macros: SCREAMING_SNAKE_CASE
3. Except for function-like macros, which should follow normal code style.
4. Classes, namespaces, enums, structs: PascalCase
5. Avoid starting any symbol with `_` and avoid any symbol with double `__` to prevent collision with function names and
   signatures.

**Exceptions**: Words that are easier to read or understand in uppercase, such as `componentID` or `GLESC`.

### Example macro naming

```c++ 
// Good
#define MAX_SIZE 100
#define functionLikeMacro(x) (x * x)

// Bad
#define MAXSIZE 100
#define FUNCTIONLIKEMACRO(x) (x * x)
```

### Example class naming

```c++
// Good
class ExampleClass {
};

// Bad
class example_class {
};
```

### Example variable naming

```c++
// Good
int exampleVariable;

// Bad
int example_variable;
```

### Example function naming

```c++
// Good
void exampleFunction();

// Bad
void ExampleFunction();
```

### Example namespace naming

```c++
// Good
namespace ExampleNamespace {
};

// Bad
namespace example_namespace {
};
```

### Example enum naming

```c++
// Good
enum class ExampleEnum {
};

// Bad
enum class example_enum {
};
```

### Example struct naming

```c++
// Good
struct ExampleStruct {
};

// Bad
struct example_struct {
};
```

## Formatting

### Braces

1. Use the K&R style recommended by C++ Core Guidelines.

```c++
// Good
if (x == y) {
    something();
    somethingElse();
}

// Bad
if (x == y)
{
    something();
    somethingElse();
}

// Also bad
if (x == y){
    something();
    somethingElse();
}

// Also bad

if (x == y)
    {
    something();
    somethingElse();
    }
```

2. Use braces for all control structures, even if they are not required.

```c++
// Good
if (x == y) {
    something();
}


// Bad
if (x == y)
    something();
```

3. Use braces for single-line control structures if they contain multiple statements.

```c++
// Good
if (x == y) {
    something();
    somethingElse();
}

// Bad
if (x == y) {
    something();
}
```

### Indentation

1. Use the K&R style recommended by C++ Core Guidelines.

```c++
// Good
while (x == y) {
    something();
    somethingElse();
}

// Bad
while (x == y)
{
    something();
    somethingElse();
}
// Also bad
while (x == y){
    something();
    somethingElse();
}
// Also bad
while (x == y)
    {
    something();
    somethingElse();
    }
```

2. Use spaces for indentation, specifically 4 spaces per indentation level.

### Line Length

1. Limit lines to 80 characters. For exceptions, lines can extend up to 100 characters. Only for project code, if the
   project contains a header library, its lines are not limited.
2. Break long lines into multiple lines to improve readability.
3. Break lines after a comma or operator.

# CMake Code Style Guide

## General Guidelines

- **File Structure**: Organize your CMake files logically, with one primary `CMakeLists.txt` at the root and additional
  `.cmake` files in the `cmake` directory. If the file is for reuse, consider placing it in the `cmake/modules`.
- **Comments**:
    - Use comments to describe the purpose of each section and any non-obvious logic. Use `#` for single-line
      comments.
    - For multi-line comments, use `#` at the beginning of each line.
    - Function comments must be placed inside a box with 60 characters of length. It must contain the name of the
      function, a brief description, and a list of parameters with their descriptions.
    - It's also recommended to separate different parts of a file using visual separators.
    - Visual separators and visual functions boxes must have 60 characters of length (including the # and
      the space at the beginning of the line).
- **Variables**: Use meaningful variable names and follow a consistent naming convention explained in
  [Formatting](#formatting)
- **Functions**: Define reusable functions for common tasks to avoid redundancy.
- **Error Handling**: Use the common functions for error handling defined in
  [`ErrorChecking.cmake`](../cmake/modules/ErrorChecking.cmake).
- **Including Files**: Use `include_once()` to include files to avoid multiple inclusions, defined in
  [`Include.cmake`](../cmake/core/Include.cmake).

#### Example of visual separators

```cmake

# `````````````````````````````````````````````````````````- # 60 characters visual separator
# Setting the source files
foreach (target ${targets})
    set_common_sources(${target})
endforeach ()

if (TARGET game_test)
    add_extra_sources(game_test "${TEST_SOURCE_FILES}")
endif ()


# `````````````````````````````````````````````````````````- # 60 characters

# `````````````````````````````````````````````````````````- # 60 characters
# Setting compiler definitions
foreach (target ${targets})
    set_common_definitions(${target})
endforeach ()

if (TARGET game_test)
    add_extra_definitions(game_test "GTEST_HAS_DEATH_TEST")
endif ()

# `````````````````````````````````````````````````````````- # 60 characters
```

#### Example single line comments

```cmake
# Defining release build flags
set(RELEASE_FLAGS
        # Optimization flag, -O3 is not always faster than -O2
        "-O3"
        # Enable miscellaneous release features
        "-DRELEASE"
)
```

#### Example function comments and multi-line comments

```cmake

# `````````````````````````````````````````````````````````- # 60 characters box start
# Function: set_common_compiler_flags_to_build_type
# Description: * Description of the function *
# Parameters:
#   param1: * Description of the parameter *
#   param2: * Description of the parameter *
# `````````````````````````````````````````````````````````- # 60 characters box end
function(set_common_compiler_flags_to_build_type target)
    assert_not_empty(${target})
    important_info("Adding common compile flags to build type for target ${target}")
    #...
endfunction()

```

## Formatting

### Indentation

- Use 4 spaces for indentation. Do not use tabs.
- Indent nested blocks and function parameters.

### Line Length

- Limit lines to 80 characters. For exceptions, lines can extend up to 100 characters.

### Spacing

- Place a space between the command name and the opening parenthesis.
- Place a space after each comma in lists.
- Align arguments vertically when a command spans multiple lines.

#### Example

```cmake
# Good
add_executable(my_app
        main.cpp
        helper.cpp
)

# Bad
add_executable(my_app main.cpp helper.cpp)
```

### Name conventions

- Variables: Use UPPER_SNAKE_CASE for variables.
- Functions and Macros: Use snake_case for functions and macros.
- Targets: Use snake_case for target names.

#### Example variables

```cmake
# Good
set(SOURCE_FILES main.cpp helper.cpp)
set(CMAKE_CXX_STANDARD 17)

# Bad
set(sourceFiles main.cpp helper.cpp)
set(CMAKE_CXX_STANDARD 17)
```

#### Example functions

```cmake
# Good
function(add_sources target)
    target_sources(${target} PRIVATE ${ARGN})

endfunction()

# Bad
function(AddSources target)
    target_sources(${target} PRIVATE ${ARGN})
endfunction()

```

#### Example targets

```cmake
# Good
set(SOURCE_FILES main.cpp helper.cpp)
add_executable(my_app ${SOURCE_FILES})

# Bad
set(sourcefiles main.cpp helper.cpp)
add_executable(MyApp ${sourcefiles})
```

