cmake_minimum_required(VERSION 3.0)

project(galaxy_server)

set(src 
main.cpp 
player.cpp
dot.cpp
field.cpp
gamechange.cpp
gamestate.cpp
galaxy.cpp
network.cpp
)

find_package (Threads)

add_executable(galaxy_server ${src})

target_link_libraries (galaxy_server ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS galaxy_server RUNTIME DESTINATION bin)
