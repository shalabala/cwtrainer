cmake_minimum_required(VERSION 3.8)

project(cwtrainer VERSION 0.1 LANGUAGES CXX)

#sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#morse
aux_source_directory("../src/morse" MORSE)
add_library(morse STATIC ${MORSE})
target_include_directories(morse PUBLIC "../src/morse")
target_compile_features(morse PUBLIC cxx_std_11)

#beeper
aux_source_directory("../src/beeper" BEEPER)
add_library(beeper STATIC ${BEEPER})
target_include_directories(beeper PUBLIC "../src/beeper")
target_compile_features(beeper PUBLIC cxx_std_11)

#utilities
aux_source_directory("../src/utility" UTILITY)
add_library(utility STATIC ${UTILITY})
target_include_directories(utility PUBLIC "../src/utility") 

#executable
set(CMAKE_BUILD_TYPE Debug)
add_executable(cwtrainer ../src/main.cpp)

#tests

# link libraries
target_link_libraries(morse PUBLIC utility)
target_link_libraries(beeper PUBLIC morse ${SDL2_LIBRARIES})
target_link_libraries(cwtrainer PUBLIC ${SDL2_LIBRARIES} morse utility beeper)

