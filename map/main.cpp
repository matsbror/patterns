#include "map.h"
#include <assert.h>
#include <random>
#include <algorithm>
#include <thread>
#include <omp.h>

using namespace std;


auto my_rand() -> auto {
    return []() {
        return rand();
    };
}


int main() {
    const auto N{200000000ul};
    vector<int> arr(N);

    auto gen = my_rand();

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
