cmake_minimum_required(VERSION 3.8)

project(cwtrainer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#------------sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#------------qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

#------------boost::ext-di
add_library(di STATIC "../lib/boost/di.hpp")
target_include_directories(di PUBLIC "../lib/boost")
target_compile_features(di PUBLIC cxx_std_17)

#------------boost
find_package(Boost REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
#------------morse
aux_source_directory("../src/morse" MORSE)
add_library(morse STATIC ${MORSE})
target_include_directories(morse PUBLIC "../src/morse")
target_compile_features(morse PUBLIC cxx_std_17)

#------------config
aux_source_directory("../src/configuration" CONFIG)
add_library(configuration STATIC ${CONFIG})
target_include_directories(configuration PUBLIC "../src/configuration")
target_compile_features(configuration PUBLIC cxx_std_17)

#------------dictionary
aux_source_directory("../src/dictionary" DICTIONARY)
add_library(dictionary STATIC ${DICTIONARY})
target_include_directories(dictionary PUBLIC "../src/dictionary")
target_compile_features(dictionary PUBLIC cxx_std_17)

#------------display
aux_source_directory("../src/display" DISPLAY)
add_library(display STATIC ${DISPLAY})
target_include_directories(display PUBLIC "../src/display")
target_compile_features(display PUBLIC cxx_std_17)

#------------beeper
aux_source_directory("../src/beeper" BEEPER)
add_library(beeper STATIC ${BEEPER})
target_include_directories(beeper PUBLIC "../src/beeper")
target_compile_features(beeper PUBLIC cxx_std_17)

#------------presenter
aux_source_directory("../src/presenter" PRESENTER)
add_library(presenter STATIC ${PRESENTER})
target_include_directories(presenter PUBLIC "../src/presenter")
target_compile_features(presenter PUBLIC cxx_std_17)

#------------#utilities
aux_source_directory("../src/utility" UTILITY)
add_library(utility STATIC ${UTILITY})
target_include_directories(utility PUBLIC "../src/utility") 

#------------executable
add_executable(cwtrainer ../src/main.cpp)

#------------link libraries
target_link_libraries(morse PUBLIC utility)
target_link_libraries(configuration PUBLIC utility ${Boost_LIBRARIES})
target_link_libraries(beeper PUBLIC morse ${SDL2_LIBRARIES})
target_link_libraries(dictionary PUBLIC configuration)
target_link_libraries(presenter PUBLIC beeper utility configuration dictionary Qt5::Core ${Boost_LIBRARIES})
target_link_libraries(display PUBLIC beeper presenter Qt5::Core Qt5::Gui Qt5::Widgets di)
target_link_libraries(cwtrainer PUBLIC presenter display configuration dictionary beeper di)


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



