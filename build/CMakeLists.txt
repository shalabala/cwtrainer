cmake_minimum_required(VERSION 3.8)

project(cwtrainer VERSION 0.1 LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
add_executable(cwtrainer ../src/main.cpp)

# Finde die SDL2-Bibliothek
find_package(SDL2 REQUIRED)

# Füge die Header-Dateien zur Include-Pfadliste hinzu
include_directories(${SDL2_INCLUDE_DIRS})

# Füge die Bibliotheken zur Linker-Liste hinzu
target_link_libraries(cwtrainer ${SDL2_LIBRARIES})