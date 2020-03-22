cmake_minimum_required(VERSION 3.0)

project(galaxy_server)

set(src 
main.cpp 
player.cpp
dot.cpp
field.cpp
gamechange.cpp
)

add_executable(galaxy_server ${src})

install(TARGETS galaxy_server RUNTIME DESTINATION bin)
