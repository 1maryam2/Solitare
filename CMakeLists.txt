cmake_minimum_required(VERSION 3.23)

set(project "SolitareGame_practics")
project(${project})
set(${project}_SOURCES
        main.cpp)

add_subdirectory(SolitareGame_practics)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})
