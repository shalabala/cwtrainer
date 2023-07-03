cmake_minimum_required(VERSION 3.8)

project(cwtrainer VERSION 0.1 LANGUAGES CXX)

#------------sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#------------morse
aux_source_directory("../src/morse" MORSE)
add_library(morse STATIC ${MORSE})
target_include_directories(morse PUBLIC "../src/morse")
target_compile_features(morse PUBLIC cxx_std_11)

#------------beeper
aux_source_directory("../src/beeper" BEEPER)
add_library(beeper STATIC ${BEEPER})
target_include_directories(beeper PUBLIC "../src/beeper")
target_compile_features(beeper PUBLIC cxx_std_11)

#------------#utilities
aux_source_directory("../src/utility" UTILITY)
add_library(utility STATIC ${UTILITY})
target_include_directories(utility PUBLIC "../src/utility") 

#------------executable
set(CMAKE_BUILD_TYPE Debug)
add_executable(cwtrainer ../src/main.cpp)

#------------link libraries
target_link_libraries(morse PUBLIC utility)
target_link_libraries(beeper PUBLIC morse ${SDL2_LIBRARIES})
target_link_libraries(cwtrainer PUBLIC ${SDL2_LIBRARIES} morse utility beeper)


#------------TESTS

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

aux_source_directory("../test" TEST)

add_executable(cwtrainer_test ${TEST})
target_link_libraries(
    cwtrainer_test
  GTest::gtest_main
  morse
)

include(GoogleTest)
gtest_discover_tests(cwtrainer_test)



