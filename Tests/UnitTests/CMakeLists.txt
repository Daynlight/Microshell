cmake_minimum_required(VERSION 3.15)


project(MicroshellTests LANGUAGES CXX)

set(src_tests
  tests.cpp
)

set(headers_tests
  ${CMAKE_SOURCE_DIR}/Microshell/
  ${CMAKE_SOURCE_DIR}/Tests/
)

add_executable(MicroshellTests ${src_tests})
target_include_directories(MicroshellTests PUBLIC ${headers_tests})

enable_testing()
add_test(NAME MicroshellTests COMMAND MicroshellTests)