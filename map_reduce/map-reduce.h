// map.h : Include file for standard system include files,
// or project specific include files.

// all of the map reduce functions perform a dot-product

#pragma once

#include <iostream>
#include <vector>
#include <functional>

int mapred_stl(std::vector<int> &arr1, std::vector<int> &arr2);

int mapred_parstl(std::vector<int> &arr1, std::vector<int> &arr2);

int mapred_for(std::vector<int> &arr1, std::vector<int> &arr2);

int mapred_openmp(std::vector<int> &arr1, std::vector<int> &arr2);

int mapred_threads(std::vector<int> &arr1, std::vector<int> &arr2);

int mapred_tbb(std::vector<int> &arr1, std::vector<int> &arr2);

double
time_a_map(std::vector<int> &arr1, std::vector<int> &arr2,
           std::function<int(std::vector<int> &arr1, std::vector<int> &arr2)> const &mapred_function);

