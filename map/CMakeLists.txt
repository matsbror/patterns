# CMakeList.txt : CMake project for map, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.9)

project(map)
# Add source to this project's executable.
add_library (maplib map.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(maplib PUBLIC OpenMP::OpenMP_CXX)
endif()
add_executable(map_main main.cpp)
target_link_libraries(map_main maplib)

# TODO: Add tests and install targets if needed.
find_package(Catch2 REQUIRED)
add_executable(map_tests test_map.cpp)
#target_include_directories(map_tests PUBLIC /usr/local/include)
target_link_libraries(map_tests Catch2::Catch2 maplib)

include(CTest)
include(Catch)
catch_discover_tests(map_tests)
