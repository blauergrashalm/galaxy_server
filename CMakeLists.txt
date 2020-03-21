cmake_minimum_required(VERSION 3.0)

project(galaxy_server)

add_executable(galaxy_server main.cpp)

install(TARGETS galaxy_server RUNTIME DESTINATION bin)
