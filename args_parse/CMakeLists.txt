# ¬ современном CMake рекомендуетс€ сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# √оворим CMake что за проект.
project(CMakeProject1 LANGUAGES CXX)

# ќпредел€ем библиотеку и указываем из чего она состоит.
add_library(args_parse_lib STATIC ArgsParser.cpp ArgsParser.hpp argument.cpp argument.hpp IntArg.cpp IntArg.hpp BoolArg.cpp BoolArg.hpp StringArg.cpp StringArg.hpp)

target_include_directories(args_parse PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(args_parse PUBLIC cxx_std_17)