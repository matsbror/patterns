// map.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <chrono>

void map1(std::vector<int> &arr, std::function<int(int)> foo);

void map2(std::vector<int>& arr, std::function<int(int)> foo);

void map3(std::vector<int>& arr, std::function<int(int)> foo);
