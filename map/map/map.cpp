// map.cpp : Defines the entry point for the application.
//

#include "map.h"
#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>
#include <chrono>

using namespace std;

const long N = 20000000;

auto my_rand() -> auto {
	// First create an instance of an engine.
	random_device rnd_device;
	// Specify the engine and distribution.
	mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
	uniform_int_distribution<int> dist{ 1, 52 };

	return [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};

}

auto my_rand2() -> auto {
	return []() {
		return rand();
	};

}

auto map1(vector<int> &arr) {

	auto start = chrono::steady_clock::now();
	for_each(arr.begin(), arr.end(),
		[](int& i) {
			i = i * 2;
		}
	);
	auto end = chrono::steady_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

auto map2(vector<int>& arr) {

	auto start = chrono::steady_clock::now();
	for (long i = 0; i < N; ++i) {
		arr[i] *= 2;
	}
	auto end = chrono::steady_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

auto map3(vector<int>& arr) {

	auto start = chrono::steady_clock::now();
#pragma omp parallel 
	#pragma omp taskloop
	for (long i = 0; i < N; ++i) {
		arr[i] *= 2;
	}
	auto end = chrono::steady_clock::now();

	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int main()
{
	cout << "Hello Map." << endl;

	vector<int> arr(N);

	auto gen = my_rand2();

	cout << "arr is " << arr.size() << " elements\n";

	generate(begin(arr), end(arr), gen);

	// the map
	cout << "map 1 took " << map1(arr) << " ms." << endl;
	cout << "map 1 took " << map1(arr) << " ms." << endl;

	// the map
	cout << "map 2 took " << map2(arr) << " ms." << endl;
	cout << "map 2 took " << map2(arr) << " ms." << endl;

	// the map
	cout << "map 3 took " << map3(arr) << " ms." << endl;
	cout << "map 3 took " << map3(arr) << " ms." << endl;

	return 0;
}
