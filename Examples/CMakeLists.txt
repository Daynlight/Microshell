cmake_minimum_required(VERSION 3.15)


project(Examples LANGUAGES C)

set(src
  examples.c
)

set(headers
  ${CMAKE_SOURCE_DIR}/Microshell/
  ${CMAKE_SOURCE_DIR}/Examples/
)

add_executable(Examples ${src})
target_include_directories(Examples PUBLIC ${headers})