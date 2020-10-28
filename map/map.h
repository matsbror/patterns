// map.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <functional>

void map_stl(std::vector<int> &arr, std::function<int(int)> const &foo);

void map_parstl(std::vector<int> &arr, std::function<int(int)> const &foo);

void map_for(std::vector<int> &arr, std::function<int(int)> const &foo);

void map_openmp(std::vector<int> &arr, std::function<int(int)> const &foo);

void map_threads(std::vector<int> &arr, std::function<int(int)> const &foo);

void map_tbb(std::vector<int> &arr, std::function<int(int)> const &foo);

double
time_a_map(std::vector<int> &arr, std::function<int(int)> const &foo,
           std::function<void(std::vector<int> &arr, std::function<int(int)>)> const &map_function);

