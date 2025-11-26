cmake_minimum_required(VERSION 3.15)


project(IntegrationTests LANGUAGES CXX)

set(src_tests
  integration_tests.cpp
)

set(headers_tests
  ${CMAKE_SOURCE_DIR}/Microshell/
  ${CMAKE_SOURCE_DIR}/Tests/
)

add_executable(IntegrationTests ${src_tests})
target_include_directories(IntegrationTests PUBLIC ${headers_tests})

add_test(NAME IntegrationTests COMMAND $<TARGET_FILE:IntegrationTests>)