// map.cpp : Defines the entry point for the application.
//

#include "map.h"
#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>

using namespace std;

const long N = 2000000000;

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

double map1(vector<int> &arr) {

	auto start = omp_get_wtime();
	for_each(arr.begin(), arr.end(),
		[](int& i) {
			i = i * 2;
		}
	);
	auto end = omp_get_wtime();

	return end - start;
}

double map2(vector<int>& arr) {

	auto start = omp_get_wtime();
	for (long i = 0; i < N; ++i) {
		arr[i] *= 2;
	}
	auto end = omp_get_wtime();

	return end - start;
}

double map3(vector<int>& arr) {

	auto start = omp_get_wtime();
#pragma omp parallel 
	#pragma omp taskloop
	for (long i = 0; i < N; ++i) {
		arr[i] *= 2;
	}
	auto end = omp_get_wtime();

	return end - start;
}

int main()
{
	cout << "Hello Map." << endl;

	vector<int> arr(N);

	auto gen = my_rand();

	cout << "arr is " << arr.size() << " elements\n";

	generate(begin(arr), end(arr), gen);

	// the map
	cout << "map 1 took " << map1(arr) << " seconds." << endl;
	cout << "map 1 took " << map1(arr) << " seconds." << endl;

	// the map
	cout << "map 2 took " << map2(arr) << " seconds." << endl;
	cout << "map 2 took " << map2(arr) << " seconds." << endl;

	// the map
	cout << "map 3 took " << map3(arr) << " seconds." << endl;
	cout << "map 3 took " << map3(arr) << " seconds." << endl;

	return 0;
}
