cmake_minimum_required(VERSION 3.15)



add_subdirectory(Microshell)


enable_testing()

add_subdirectory(Tests/UnitTests)
add_subdirectory(Tests/IntegrationTests)
