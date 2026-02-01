cmake_minimum_required(VERSION 3.15)


project(Microshell LANGUAGES C)

set(src
  microshell.c
)

add_executable(Microshell ${src})