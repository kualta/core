cmake_minimum_required(VERSION 3.16)
project(Core VERSION 0.0.1 DESCRIPTION "Core game engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#      core
# Specify include dir name
set(CORE_INCLUDE_DIR include)
# Get Core's headers and sources
file( GLOB CORE_SOURCES ${CORE_INCLUDE_DIR}/core/*.h src/*.cpp )
# Create core target
add_library(core STATIC ${CORE_SOURCES})
# Include Core's headers
target_include_directories(core PUBLIC ${CORE_INCLUDE_DIR})


#       bgfx
add_subdirectory(lib/bgfx.cmake)
target_link_libraries(core PUBLIC bgfx)


#       SDL2
# Specify SDL2 location
set(SDL2_DIR lib/SDL2)
# Find SDL2
find_package(SDL2 REQUIRED)
# Add SDL2 into include directories
target_include_directories(core PUBLIC ${SDL2_INCLUDE_DIRS})
# Link SDL2 libs
target_link_libraries(core PUBLIC ${SDL2_LIBRARIES})
