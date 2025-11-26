cmake_minimum_required(VERSION 3.15)


project(UnitTests LANGUAGES CXX)

set(src_tests
  unit_tests.cpp
)

set(headers_tests
  ${CMAKE_SOURCE_DIR}/Microshell/
  ${CMAKE_SOURCE_DIR}/Tests/
)

add_executable(UnitTests ${src_tests})
target_include_directories(UnitTests PUBLIC ${headers_tests})

add_test(NAME UnitTests COMMAND UnitTests)