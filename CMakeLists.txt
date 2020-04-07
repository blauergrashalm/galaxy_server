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
find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(galaxy_server ${src})

link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries (galaxy_server ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

install(TARGETS galaxy_server RUNTIME DESTINATION bin)
