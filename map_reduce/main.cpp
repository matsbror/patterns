#include "map-reduce.h"
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
    vector<int> arr1(N);
    vector<int> arr2(N);

    auto gen = my_rand();

    cout << "arr's are " << arr1.size() << " elements\n";
    cout << "using " << std::thread::hardware_concurrency() << " threads\n";
    cout << "using " << omp_get_num_procs() << " OpenMP threads\n";

    generate(begin(arr1), end(arr1), gen);
    generate(begin(arr2), end(arr2), gen);

    auto seq = time_a_map(arr1, arr2, mapred_for);
    auto par_threads = time_a_map(arr1, arr2, mapred_threads);
    auto par_openmp = time_a_map(arr1, arr2, mapred_openmp);
    auto par_tbb = time_a_map(arr1, arr2, mapred_tbb);

    cout << "Sequential map: " << seq << " s\n";
    cout << "Threads map: " << par_threads << " s, speedup: " << seq / par_threads << "\n";
    cout << "OpenMP map: " << par_openmp << " s, speedup: " << seq / par_openmp << "\n";
    cout << "TBB map: " << par_tbb << " s, speedup: " << seq / par_tbb << "\n";

    auto seqstl = time_a_map(arr1, arr2, mapred_stl);
    auto par_stl = time_a_map(arr1, arr2, mapred_parstl);

    cout << "Sequential map using stl: " << seqstl << " s\n";
    cout << "Parallel map using stl: " << par_stl << " s, speedup: " << seqstl / par_stl << "\n";

    return 0;
}
