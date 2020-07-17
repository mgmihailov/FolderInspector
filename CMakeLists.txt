cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(FolderInspector)

# add the executable
add_executable(FolderInspector)

target_sources(FolderInspector
    PUBLIC
        Source/FolderInspector.cpp
        Source/minitrace.c
        Source/TextFileInfoWriter.cpp
        Source/Utils.cpp
        Source/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_NAME}Main.cpp
        Source/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_NAME}FileInfoReader.cpp
        Source/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_NAME}Utils.cpp)
