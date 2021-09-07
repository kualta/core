cmake_minimum_required(VERSION 3.6)
project(Core VERSION 0.1.0 DESCRIPTION "Core engine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/" ${CMAKE_MODULE_PATH})


#       Build options
# Reduces amount of includes in client-side code by cost of slightly increased build time.
# Includes classes like core::Vector, ::Matrix and ::Object into Essential.h
option(CORE_HEAVY_ESSENTIALS "Adds basic types includes into Essential.h"  OFF)

# HH:MM:SS:ms -> YY/MM/DD HH:MM:SS.ms
option(CORE_LOG_DATE "Adds year, month and date to each log entry"         OFF)

# at [filename:line] -> at [full/file/path/filename:line]
option(CORE_LOG_FULL_PATH "LOG_HERE adds full filepath to log"             OFF)

# Adds core::VkRenderer -> core::Renderer kind of typedefs. Gives better looking client-side
# code, but you will not be able to include two modules with same typedefs in the same file
# (e.g. VkRenderer and BgfxRenderer)
option(CORE_SIMPLIFY_SYNTAX "Adds typedefs for modules and components"     ON)


#       core
set( CORE_INCLUDE_DIR include )
set( CORE_SRC_DIR     src )

set( CORE_ENGINE_RES  )

file( GLOB_RECURSE CORE_SOURCES ${CMAKE_CURRENT_LIST_DIR}/include/core/ ${CMAKE_CURRENT_LIST_DIR}/src/ "src/*.cpp" "core/*.hpp" "core/*.h" )
add_library( core STATIC ${CORE_SOURCES} )
target_include_directories( core PUBLIC ${CORE_INCLUDE_DIR} )

if ( CORE_HEAVY_ESSENTIALS )
    target_compile_definitions( core PUBLIC CORE_HEAVY_ESSENTIALS )
endif()
if ( CORE_LOG_DATE )
    target_compile_definitions( core PUBLIC CORE_LOG_DATE )
endif()
if ( CORE_LOG_FULL_PATH )
    target_compile_definitions( core PUBLIC CORE_LOG_FULL_PATH )
endif()
if ( CORE_SIMPLIFY_SYNTAX )
    target_compile_definitions( core PUBLIC CORE_SIMPLIFY_SYNTAX )
endif()


#       SDL2
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/SDL2-2.0.10")
set(SDL_ATOMIC     OFF CACHE BOOL "" FORCE)
set(SDL_CPUINFO    OFF CACHE BOOL "" FORCE)
set(SDL_EVENTS     OFF CACHE BOOL "" FORCE)
set(SDL_FILE       OFF CACHE BOOL "" FORCE)
set(SDL_FILESYSTEM OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC     OFF CACHE BOOL "" FORCE)
set(SDL_LOCALE     OFF CACHE BOOL "" FORCE)
set(SDL_POWER      OFF CACHE BOOL "" FORCE)
set(SDL_RENDER     OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR     OFF CACHE BOOL "" FORCE)
set(SDL_THREADS    OFF CACHE BOOL "" FORCE)
set(SDL_TIMERS     OFF CACHE BOOL "" FORCE)
set(SDL_SHARED     OFF CACHE BOOL "" FORCE)


#       magnum
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)
set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
set(WITH_ANYSCENEIMPORTER ON CACHE BOOL "" FORCE)

add_subdirectory(lib/corrade EXCLUDE_FROM_ALL)
add_subdirectory(lib/magnum EXCLUDE_FROM_ALL)

find_package(Magnum REQUIRED
        GL
        Trade
        Sdl2Application)

target_link_libraries(core PUBLIC
        Magnum::GL
        Magnum::Trade
        Magnum::Magnum
        Magnum::Application
        Magnum::Sdl2Application
        Magnum::AnySceneImporter)


if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # required by magnum
    set(MSVC2019_COMPATIBILITY ON)
endif()
