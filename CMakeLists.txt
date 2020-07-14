cmake_minimum_required(VERSION 3.10)

# set the project name
project(FolderInspector)

# add the executable
add_executable(FolderInspector)

FILE(GLOB COMMON_SOURCES FolderInspector/FolderInspector.cpp FolderInspector/main.cpp)
FILE(GLOB PLATFORM_SOURCES FolderInspector/${CMAKE_SYSTEM_NAME}/*.*)

target_sources(FolderInspector
    PUBLIC
        FolderInspector/FolderInspector.cpp
        FolderInspector/main.cpp
        FolderInspector/minitrace.c
        FolderInspector/TextFileInfoWriter.cpp
        FolderInspector/Utils.cpp
        FolderInspector/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_NAME}FileInfoReader.cpp)
