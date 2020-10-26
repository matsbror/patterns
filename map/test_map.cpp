
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "map.h"

using namespace std;
using namespace std::chrono;


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



TEST_CASE( "Map 1 works OK", "[map1]" ) {
    std::vector<int> vec1 {1, 2, 3, 4, 5, 6};
    std::vector<int> vec2 {2, 4, 6, 8, 10, 12};

    map1(vec1, [](int i){return i*2;});

    REQUIRE( vec1.size() == vec2.size());

    REQUIRE( vec1 == vec2);
}

TEST_CASE( "Map 2 works OK", "[map2]" ) {
    std::vector<int> vec1 {1, 2, 3, 4, 5, 6};
    std::vector<int> vec2 {2, 4, 6, 8, 10, 12};

    map2(vec1, [](int i){return i*2;});
    REQUIRE( vec1 == vec2);
}

TEST_CASE( "Map 3 works OK", "[map3]" ) {
    std::vector<int> vec1 {1, 2, 3, 4, 5, 6};
    std::vector<int> vec2 {2, 4, 6, 8, 10, 12};

    map3(vec1, [](int i){return i*2;});
    REQUIRE( vec1 == vec2);
}

double time_a_map(vector<int> &arr, 
                                    function<int(int)> foo, 
                                    function<void(vector<int> &arr, function<int(int)>)> map_function) {

	auto start = steady_clock::now();
	map_function(arr, foo);
	auto end = steady_clock::now();

	return duration<double>(end - start).count();

}
