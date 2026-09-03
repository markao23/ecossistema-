cmake_minimum_required(VERSION 3.16)
project(mini_claude_code LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mini_claude_code
    src/main.cpp
    src/Mapa.cpp
    src/Animal.cpp
    include/Genoma.h
    src/Genoma.cpp
)

target_include_directories(mini_claude_code PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
