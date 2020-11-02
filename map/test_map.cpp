
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "map.h"
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

    map_stl(vec1, [](int i) { return i * 2; });

    REQUIRE(vec1.size() == vec2.size());

    REQUIRE(vec1 == vec2);
}

TEST_CASE("Map stl parallel works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    map_parstl(vec1, [](int i) { return i * 2; });

    REQUIRE(vec1.size() == vec2.size());

    REQUIRE(vec1 == vec2);
}

TEST_CASE("Map parallel stl works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    map_parstl(vec1, [](int i) { return i * 2; });

    REQUIRE(vec1.size() == vec2.size());

    REQUIRE(vec1 == vec2);
}

TEST_CASE("Map 2 works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    map_for(vec1, [](int i) { return i * 2; });
    REQUIRE(vec1 == vec2);
}

TEST_CASE("Map threads works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    map_threads(vec1, [](int i) { return i * 2; });
    REQUIRE(vec1 == vec2);
}

TEST_CASE("Map 3 works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    map_openmp(vec1, [](int i) { return i * 2; });
    REQUIRE(vec1 == vec2);
}

TEST_CASE("TBB Map works OK", "[map function]") {
    vector<int> vec1{1, 2, 3, 4, 5, 6};
    vector<int> vec2{2, 4, 6, 8, 10, 12};

    map_tbb(vec1, [](int i) {
        return i * 2;
    });
    REQUIRE(vec1 == vec2);
}

TEST_CASE("Time maps", "[map timing]") {

    const auto N{20000000u};
    vector<int> arr(N);

    auto gen = my_rand();

    cout << "arr is " << arr.size() << " elements\n";

    generate(begin(arr), end(arr), gen);

    auto seq = time_a_map(
            arr, [](int i) { return i * 2; }, map_for);
    auto par_openmp = time_a_map(
            arr, [](int i) { return i * 2; }, map_openmp);

    REQUIRE(seq > par_openmp);

    auto par_tbb = time_a_map(
            arr, [](int i) { return i * 2; }, map_tbb);

    REQUIRE(seq > par_tbb);
}
