cmake_minimum_required(VERSION 3.15)


project(Microshell LANGUAGES C)

set(src
  main.c
)

add_executable(Microshell ${src})



add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/main.pp.c
  COMMAND ${CMAKE_C_COMPILER}
          -E
          -P
          $<TARGET_PROPERTY:Microshell,COMPILE_DEFINITIONS>
          $<TARGET_PROPERTY:Microshell,INCLUDE_DIRECTORIES>
          ${CMAKE_CURRENT_SOURCE_DIR}/main.c
          -o ${CMAKE_BINARY_DIR}/main.pp.c
  DEPENDS main.c
  COMMENT "Generating fully preprocessed main.c"
)

add_custom_target(preprocess ALL
    DEPENDS ${CMAKE_BINARY_DIR}/main.pp.c
)