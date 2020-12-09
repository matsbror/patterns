
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "map-reduce.h"
#include <catch2/catch.hpp>
#include <random>

using namespace std;
using namespace std::chrono;

auto my_rand() -> auto {
    return []() {
        return rand();
    };
}

TEST_CASE("Map stl works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    int val = mapred_stl(vec1, vec2);

    REQUIRE(val == 182);

}

TEST_CASE("Map parallel stl works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    int val = mapred_parstl(vec1, vec2);

    REQUIRE(val == 182);
}

TEST_CASE("Map 2 works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    int val = mapred_for(vec1, vec2);
    
    REQUIRE(val == 182);
}

TEST_CASE("Map threads works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    int val = mapred_threads(vec1, vec2);
    REQUIRE(val == 182);
}

TEST_CASE("Map 3 works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    int val = mapred_openmp(vec1, vec2);
    REQUIRE(val == 182);
}

TEST_CASE("TBB Map works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    int val = mapred_tbb(vec1, vec2);
    REQUIRE(val == 182);
}

