// map.cpp : Defines the entry point for the application.
//

#include "map.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <omp.h>
#include <chrono>

using namespace std;

void map1(vector<int> &arr, std::function<int(int)> foo) {

	transform(arr.begin(), arr.end(), arr.begin(), foo);

}

void map2(vector<int>& arr, std::function<int(int)> foo) {

	for (long i = 0; i < arr.size(); ++i) {
		arr[i] = foo(arr[i]);
	}
}

void map3(vector<int>& arr, std::function<int(int)> foo)  {

#pragma omp parallel for
	for (long i = 0; i < arr.size(); ++i) {
		arr[i] = foo(arr[i]);
	}
}

