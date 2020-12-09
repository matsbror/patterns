# CMakeList.txt : CMake project for map, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.9)

project(map)
# Add source to this project's executable.
add_library (maplib map-reduce.cpp)

set_property(TARGET maplib PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD 17)  # doesn't work!
#SET(CMAKE_CXX_FLAGS "-std=c++17") 

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(maplib PUBLIC OpenMP::OpenMP_CXX)
endif()
find_package(TBB)
add_executable(map_main main.cpp)
target_link_libraries(map_main maplib tbb tbbmalloc)

# TODO: Add tests and install targets if needed.
find_package(Catch2 REQUIRED)
add_executable(map_tests test_map.cpp)

set_property(TARGET map_tests PROPERTY CXX_STANDARD 17)
target_link_libraries(map_tests Catch2::Catch2 maplib tbb tbbmalloc)

include(CTest)
include(Catch)
catch_discover_tests(map_tests)
