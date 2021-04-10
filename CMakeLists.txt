cmake_minimum_required(VERSION 3.16)
project(Core VERSION 0.1.0 DESCRIPTION "Core engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#       Build options

# Reduces amount of includes in client-side code by cost of slightly increased build time.
# Includes classes like core::Vector, ::Matrix and ::Object into Essential.h
option( CORE_HEAVY_ESSENTIALS "Adds basic types includes into Essential.h"  ON )


#       core
set( CORE_INCLUDE_DIR include )
set( CORE_COMPONENTS_RES ${CORE_INCLUDE_DIR}/core/components/*.h )
set( CORE_HEADERS ${CORE_INCLUDE_DIR}/core/*.h ${CORE_INCLUDE_DIR}/core/*.tpp ${CORE_COMPONENTS_RES} )
# Get Core's headers and sources
file( GLOB CORE_SOURCES ${CORE_HEADERS} src/*.cpp )
# Create core target
add_library( core STATIC ${CORE_SOURCES} )
# Include Core's headers
target_include_directories( core PUBLIC ${CORE_INCLUDE_DIR} )
# Specify compile definitions
if ( CORE_HEAVY_ESSENTIALS )
    target_compile_definitions( core PRIVATE CORE_HEAVY_ESSENTIALS )
endif()


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
