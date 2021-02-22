cmake_minimum_required(VERSION 3.16)
project(Core VERSION 0.0.1 DESCRIPTION "Core game engine")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/bgfx.cmake)

set(CORE_INCLUDE_DIR include)
file( GLOB CORE_SOURCES ${CORE_INCLUDE_DIR}/*.h src/*.cpp )

# Create core target
add_library(core STATIC ${CORE_SOURCES})


target_include_directories(core PUBLIC ${CORE_INCLUDE_DIR})

# Link bgfx renderer
target_link_libraries(core PUBLIC bgfx)


install(
        TARGETS core
        DESTINATION out
        INCLUDES DESTINATION ${CORE_INCLUDE_DIR}
)