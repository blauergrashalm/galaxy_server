cmake_minimum_required(VERSION 3.0)

project(galaxy_server)

AUX_SOURCE_DIRECTORY(src src)

add_definitions(-DDEBUG_MEDIUM)

find_package (Threads)
find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem)
find_package(nlohmann_json REQUIRED)

add_subdirectory(lib/json-schema-validator)
include_directories(${Boost_INCLUDE_DIRS} )

add_library(galaxy_server_lib STATIC ${src})
add_executable(galaxy_server main.cpp)

target_include_directories(galaxy_server PRIVATE include)
target_include_directories(galaxy_server_lib PRIVATE include)

link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries (galaxy_server_lib ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} nlohmann_json::nlohmann_json nlohmann_json_schema_validator)
target_link_libraries (galaxy_server galaxy_server_lib)

install(TARGETS galaxy_server RUNTIME DESTINATION bin)

add_subdirectory(lib/googletest)
add_subdirectory(test)
