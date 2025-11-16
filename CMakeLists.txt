cmake_minimum_required(VERSION 3.15)

project(Microshell LANGUAGES C)

set(src
  microshell.c
)

add_executable(Microshell ${src})

project(MicroshellTests LANGUAGES CXX)

set(src_tests
  tests.cpp
)

add_executable(MicroshellTests ${src_tests})

enable_testing()
add_test(NAME MicroshellTests COMMAND MicroshellTests)