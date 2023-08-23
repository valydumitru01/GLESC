# CMake generated Testfile for 
# Source directory: C:/Github_Repos/TFG---OpenGL-Engine
# Build directory: C:/Github_Repos/TFG---OpenGL-Engine/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyGameTest "C:/Github_Repos/TFG---OpenGL-Engine/bin/debug/game_test.exe")
set_tests_properties(MyGameTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Github_Repos/TFG---OpenGL-Engine/CMakeLists.txt;111;add_test;C:/Github_Repos/TFG---OpenGL-Engine/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
