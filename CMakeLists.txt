cmake_minimum_required(VERSION 3.6)
project(Core VERSION 0.1.0 DESCRIPTION "Core engine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/lib/")


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

set( CORE_ENGINE_RES     ${CORE_INCLUDE_DIR}/core/*.h            ${CORE_SRC_DIR}/*.cpp
                         ${CORE_INCLUDE_DIR}/core/*.tpp )
set( CORE_MODULES_RES    ${CORE_INCLUDE_DIR}/core/Modules/*.h    ${CORE_SRC_DIR}/Modules/*.cpp )
set( CORE_COMPONENTS_RES ${CORE_INCLUDE_DIR}/core/Components/*.h ${CORE_SRC_DIR}/Components/*.cpp )

set( CORE_FILES
        ${CORE_ENGINE_RES}
        ${CORE_MODULES_RES}
        ${CORE_COMPONENTS_RES}
   )

file( GLOB CORE_SOURCES ${CORE_FILES} )
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


#       assimp
add_subdirectory(lib/assimp)
target_link_libraries(core PUBLIC assimp)


#       SDL2
set(SDL2_DIR lib/SDL2)
find_package(SDL2 REQUIRED FATAL_ERROR)
target_include_directories(core PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(core PUBLIC ${SDL2_LIBRARY})
add_custom_command(TARGET core
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL2_DLL}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
                   COMMENT "Copying SDL2.dll to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} directory" VERBATIM)


#       magnum
add_subdirectory(lib/corrade EXCLUDE_FROM_ALL)
add_subdirectory(lib/magnum EXCLUDE_FROM_ALL)
find_package(Magnum REQUIRED GL)
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)
target_link_libraries(core PRIVATE
        Magnum::GL
        Magnum::Magnum)


if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(MSVC2019_COMPATIBILITY ON)
endif()
