cmake_minimum_required(VERSION 3.15)

project(Microshell LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(Microshell)


add_subdirectory(Examples)


enable_testing()

add_subdirectory(Tests/UnitTests)
add_subdirectory(Tests/IntegrationTests)


install(TARGETS Microshell DESTINATION bin CONFIGURATIONS Release)
