cmake_minimum_required(VERSION 3.0)

project(galaxy_server)

AUX_SOURCE_DIRECTORY(src src)

add_definitions(-DDEBUG_HIGH)

find_package (Threads)
find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(galaxy_server ${src})
add_library(galaxy_server_lib STATIC ${src})

target_include_directories(galaxy_server PRIVATE include)
target_include_directories(galaxy_server_lib PRIVATE include)

link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries (galaxy_server ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
target_link_libraries (galaxy_server_lib ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

install(TARGETS galaxy_server RUNTIME DESTINATION bin)


add_subdirectory(lib/googletest)
add_subdirectory(test)
