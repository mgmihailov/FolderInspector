cmake_minimum_required(VERSION 3.10)

# set the project name
project(FolderInspector)

# add the executable
add_executable(FolderInspector)

target_sources(FolderInspector
    PUBLIC
        FolderInspector/FolderInspector.cpp
        FolderInspector/main.cpp
        FolderInspector/minitrace.c
        FolderInspector/TextFileInfoWriter.cpp
        FolderInspector/Utils.cpp
        FolderInspector/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_NAME}FileInfoReader.cpp
        FolderInspector/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_NAME}Utils.cpp)
