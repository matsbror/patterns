# CMakeList.txt : CMake project for map, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.9)

# Add source to this project's executable.
add_executable (map "map.cpp" "map.h")

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(map PUBLIC OpenMP::OpenMP_CXX)
endif()

# TODO: Add tests and install targets if needed.
