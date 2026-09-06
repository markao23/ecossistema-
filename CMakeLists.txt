cmake_minimum_required(VERSION 3.16)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(Ecossistema3D VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    add_compile_options(/w4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -march=native)
    endif()
endif()

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

set( SOURCES
    src/main.cpp
    src/Animal.cpp
    src/Genoma.cpp
    src/Mapa.cpp
)

set( HEADERS
    include/Animal.h
    include/Genoma.h
    include/Mapa.h
)

add_executable(Ecossistema3D ${SOURCES} ${HEADERS})
target_include_directories(Ecossistema3D PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Link raylib target provided by FetchContent (raylib's CMake defines a target named "raylib")
target_link_libraries(Ecossistema3D PRIVATE raylib)

if(UNIX AND NOT APPLE) 
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
elseif(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
endif()

