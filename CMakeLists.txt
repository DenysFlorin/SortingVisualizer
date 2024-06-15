cmake_minimum_required(VERSION 3.26)
project(SortingVisualizer)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(SortingVisualizer main.cpp
        Data.cpp
        Data.h
        Viewer.cpp
        Viewer.h
        Algorithm.cpp
        Algorithm.h
        Algorithm.h
        StatusBar.cpp
        StatusBar.h)

target_link_libraries(SortingVisualizer sfml-graphics)