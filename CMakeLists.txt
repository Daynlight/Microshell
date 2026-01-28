cmake_minimum_required(VERSION 3.15)


project(Microshell LANGUAGES C)



add_subdirectory(Microshell)


install(TARGETS Microshell DESTINATION bin CONFIGURATIONS Release)
