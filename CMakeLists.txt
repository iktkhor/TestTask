cmake_minimum_required(VERSION 3.13)

project(TestTask VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    TinyXML/tinyxml2.h
    TinyXML/tinyxml2.cpp
    main.cpp
)

add_executable(ConvertApp ${PROJECT_SOURCES})