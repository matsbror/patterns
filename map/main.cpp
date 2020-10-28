#include "map.h"
#include <assert.h>
#include <random>
#include <algorithm>
#include <thread>
#include <omp.h>

using namespace std;


auto my_rand2() -> auto {
    return []() {
        return rand();
    };
}


auto my_rand() -> auto {
    // First create an instance of an engine.
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine{rnd_device()}; // Generates random integers
    uniform_int_distribution<int> dist{1, 52};

    return [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
}

int main() {
    const auto N{200000000ul};
    vector<int> arr(N);

    auto gen = my_rand2();

    cout << "arr is " << arr.size() << " elements\n";
    cout << "using " << std::thread::hardware_concurrency() << " threads\n";
    cout << "using " << omp_get_num_procs() << " OpenMP threads\n";

    generate(begin(arr), end(arr), gen);

    auto seq = time_a_map(
            arr, [](int i) { return i * 2; }, map_for);
    auto par_threads = time_a_map(
            arr, [](int i) { return i * 2; }, map_threads);
    auto par_openmp = time_a_map(
            arr, [](int i) { return i * 2; }, map_openmp);
    auto par_tbb = time_a_map(
            arr, [](int i) { return i * 2; }, map_tbb);

    cout << "Sequential map: " << seq << " s\n";
    cout << "Threads map: " << par_threads << " s, speedup: " << seq / par_threads << "\n";
    cout << "OpenMP map: " << par_openmp << " s, speedup: " << seq / par_openmp << "\n";
    cout << "TBB map: " << par_tbb << " s, speedup: " << seq / par_tbb << "\n";

    auto seqstl = time_a_map(
            arr, [](int i) { return i * 2; }, map_stl);
    auto par_stl = time_a_map(
            arr, [](int i) { return i * 2; }, map_parstl);

    cout << "Sequential map using stl: " << seqstl << " s\n";
    cout << "Parallel map using stl: " << par_stl << " s, speedup: " << seqstl / par_stl << "\n";

    return 0;
}
