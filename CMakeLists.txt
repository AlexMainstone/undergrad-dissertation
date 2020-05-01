cmake_minimum_required(VERSION 3.0)
project(dissertation-project)

set (CMAKE_CXX_STANDARD 17)

# Header files
list(APPEND HEADERS
    "${CMAKE_SOURCE_DIR}/include/Scenes/Game.hpp"
    "${CMAKE_SOURCE_DIR}/include/World/Map.hpp"
    "${CMAKE_SOURCE_DIR}/include/World/MapGenerator.hpp"
    )

# Source Files
list(APPEND SOURCES
    "${CMAKE_SOURCE_DIR}/src/Main.cpp"

    "${CMAKE_SOURCE_DIR}/src/Scenes/Game.cpp"
    "${CMAKE_SOURCE_DIR}/src/World/Map.cpp"
    "${CMAKE_SOURCE_DIR}/src/World/MapGenerator.cpp"
    )

# Include Directories
list(APPEND INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/lib/Voronoi-master/include"
    "${CMAKE_SOURCE_DIR}/lib/PerlinNoise-master/"
    "${CMAKE_SOURCE_DIR}/lib/jezov/include"
    )

file(GLOB VLIB_SOURCE "${PROJECT_SOURCE_DIR}/lib/Voronoi-master/src/*.cpp" "${PROJECT_SOURCE_DIR}/lib/Voronoi-master/include/*.h")
add_library(voronoi ${VLIB_SOURCE})

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

if (WIN32)
    #set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/SFML-master/build")
endif(WIN32)


find_package(SFML 2 COMPONENTS graphics network audio REQUIRED)

add_executable(dissertation-project ${SOURCES} ${HEADERS})

if(MSVC)
    target_compile_options(dissertation-project PRIVATE /W4)
else()
    target_compile_options(dissertation-project PRIVATE
            -Wall
            -Wextra # reasonable and standard
            -Wshadow # warn the user if a variable declaration shadows one from a parent context
            -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
            -Wold-style-cast # warn for c-style casts
            -Wcast-align # warn for potential performance problem casts
            -Wunused # warn on anything being unused
            -Woverloaded-virtual # warn if you overload (not override) a virtual function
            -Wpedantic # warn if non-standard C++ is used
            -Wconversion # warn on type conversions that may lose data
            -Wsign-conversion # warn on sign conversions
            -Wmisleading-indentation # warn if identation implies blocks where blocks do not exist
            -Wduplicated-cond # warn if if / else chain has duplicated conditions
            -Wduplicated-branches # warn if if / else branches have duplicated code
            -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
            -Wnull-dereference # warn if a null dereference is detected
            -Wuseless-cast # warn if you perform a cast to the same type
            -Wdouble-promotion # warn if float is implicit promoted to double
            -Wformat=2 # warn on security issues around functions that format output (ie printf)
            -std=c++17
            "$<$<CONFIG:DEBUG>:-DDEBUG>")
endif()

target_include_directories(dissertation-project PRIVATE ${INCLUDE_DIRS})
target_link_libraries(dissertation-project PRIVATE voronoi sfml-graphics sfml-audio sfml-network)
