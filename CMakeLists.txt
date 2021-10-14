cmake_minimum_required(VERSION 3.6)
project(Core VERSION 0.3.0 DESCRIPTION "Core Engine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/")


#       Build options
# HH:MM:SS:ms -> YY/MM/DD HH:MM:SS.ms
option(CORE_LOG_DATE "Adds year, month and date to each log entry"         OFF)

# at [filename:line] -> at [full/file/path/filename:line]
option(CORE_LOG_FULL_PATH "LOG_HERE adds full filepath to log"             OFF)

# Adds core::VkRenderer -> core::Renderer kind of typedefs. Gives better looking client-side
# code, but you will not be able to include two modules with same typedefs in the same file
# (e.g. VkRenderer and BgfxRenderer)
option(CORE_SIMPLIFY_SYNTAX "Adds typedefs for modules and components"     ON)


#       Core Engine
set( CORE_INCLUDE_DIR include )
set( CORE_LIB_DIR     lib )
set( CORE_SRC_DIR     src )

file( GLOB_RECURSE CORE_SOURCES
        ${CORE_INCLUDE_DIR}/core/*.h
        ${CORE_INCLUDE_DIR}/core/*.hpp
        ${CORE_SRC_DIR}/*.cpp )

add_library( core STATIC ${CORE_SOURCES} )
target_include_directories( core PUBLIC ${CORE_INCLUDE_DIR} )

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


#       assimp
set(ASSIMP_BUILD_ASSIMP_TOOLS   OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS          OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT            ON  CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS           OFF CACHE BOOL "" FORCE)
set(INJECT_DEBUG_POSTFIX        OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)


#       Dear ImGUI
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/imgui")
set(IMGUI_DIR lib/imgui)


#       magnum
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)
set(MAGNUM_PLUGINS_DIR lib/magnum-plugins)

set(WITH_ANYSCENEIMPORTER   ON CACHE BOOL "" FORCE)
set(WITH_ANYIMAGEIMPORTER   ON CACHE BOOL "" FORCE)
set(WITH_STBIMAGEIMPORTER   ON CACHE BOOL "" FORCE)
set(WITH_TINYGLTFIMPORTER   ON CACHE BOOL "" FORCE)
set(WITH_SDL2APPLICATION    ON CACHE BOOL "" FORCE)
set(WITH_ASSIMPIMPORTER     ON CACHE BOOL "" FORCE)
set(WITH_OBJIMPORTER        ON CACHE BOOL "" FORCE)
set(WITH_IMGUI              ON CACHE BOOL "" FORCE)

add_subdirectory(${CORE_LIB_DIR}/assimp             EXCLUDE_FROM_ALL)
add_subdirectory(${CORE_LIB_DIR}/corrade            EXCLUDE_FROM_ALL)
add_subdirectory(${CORE_LIB_DIR}/magnum             EXCLUDE_FROM_ALL)
add_subdirectory(${CORE_LIB_DIR}/magnum-plugins     EXCLUDE_FROM_ALL)
add_subdirectory(${CORE_LIB_DIR}/magnum-integration EXCLUDE_FROM_ALL)

add_dependencies(core MagnumPlugins::StbImageImporter)

find_package(MagnumIntegration REQUIRED
        ImGui)

find_package(Magnum REQUIRED
        GL
        Trade
        Shaders
        MeshTools
        SceneGraph
        Primitives
        ObjImporter
        Sdl2Application
        AnySceneImporter)

target_link_libraries(core PUBLIC
        Corrade::Main
        Magnum::GL
        Magnum::Trade
        Magnum::Magnum
        Magnum::Shaders
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::SceneGraph
        Magnum::ObjImporter
        Magnum::Application
        Magnum::Sdl2Application
        Magnum::AnySceneImporter
        MagnumPlugins::AssimpImporter
        MagnumIntegration::ImGui)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_link_options(-pthread -lpthread)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -O3 -Wa,-mbig-obj" )
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -O3 -Wa,-mbig-obj" )
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /W3" )

    # required by corrade
    set(MSVC2019_COMPATIBILITY ON)
endif()