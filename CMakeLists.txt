cmake_minimum_required(VERSION 3.16)
project(Core VERSION 0.0.1 DESCRIPTION "Core game engine")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_INCLUDE_DIR include)

add_subdirectory(lib/bgfx.cmake)


file( GLOB CORE_SOURCES ${CORE_INCLUDE_DIR}/*.h src/*.cpp )

# Create core target
add_library(core STATIC ${CORE_SOURCES})

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})


#set_target_properties(core PROPERTIES PUBLIC_HEADER include/core.h)

target_include_directories(core PUBLIC ${CORE_INCLUDE_DIR})

include(GNUInstallDirs)

# Link bgfx renderer
target_link_libraries(core PUBLIC bgfx)

#install(TARGETS core
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#install(FILES ${CORE_SOURCES} DESTINATION include)