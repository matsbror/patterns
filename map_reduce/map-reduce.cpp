// map.cpp : Defines the entry point for the application.
//

#include "map-reduce.h"
#include <numeric>
#include <execution>
#include <chrono>
#include <functional>
#include <omp.h>
#include <tbb/tbb.h>
#include <vector>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace tbb;

int mapred_stl(std::vector<int> &arr1, std::vector<int> &arr2) {
    return transform_reduce(arr1.begin(), arr1.end(), arr2.begin(), std::plus, std::multiplies);
}

int mapred_parstl(std::vector<int> &arr1, std::vector<int> &arr2) {

    return transform_reduce(std::execution::par_unseq, arr1.begin(), arr1.end(), arr2.begin(), std::plus, std::multiplies);
}

int mapred_for(std::vector<int> &arr1, std::vector<int> &arr2){

    int sum = 0;
    for (long i = 0; i < arr1.size(); ++i) {
        sum = std::plus(sum, std::multiplies(arr1[i], arr2[i]));
    }
    return sum;
}

int mapred_openmp(std::vector<int> &arr1, std::vector<int> &arr2){

    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < arr1.size(); ++i) {
        sum = std::plus(sum, std::multiplies(arr1[i], arr2[i]));
    }
    return sum;
}

int mapred_threads(std::vector<int> &arr1, std::vector<int> &arr2){
    const auto num_procs = std::thread::hardware_concurrency();

    vector<thread> tpool(num_procs); // create a thread pool

    vector<int> results(num_procs);

    for (int p = 0; p < num_procs; p++) {
        tpool[p] = thread([&arr1, &arr2, p, num_procs]() {
            size_t my_start = arr1.size() / num_procs * p;
            size_t my_end = arr1.size() / num_procs * (p + 1);
            if (p + 1 == num_procs) {
                my_end = arr1.size(); // make sure the last thread takes care of the rest of the array
            }
            int my_sum = 0;
            for (long i = my_start; i < my_end; ++i) {
                my_sum = std::plus(my_sum, std::multiplies(arr1[i], arr2[i]));
            }
            result[p] = my_sum;
        });
    }

    // wait for threads to finish
    int sum = 0;
    for (int p = 0; p < num_procs; p++) {
        sum = sum + result[p]
        tpool[p].join();
    }

    return sum;

}

int mapred_tbb(std::vector<int> &arr1, std::vector<int> &arr2){

#pragma omp parallel for shared(arr, foo) num_threads(omp_get_num_procs())
    for (long i = 0; i < arr.size(); ++i) {
        arr[i] = foo(arr[i]);
    }
}

void map_tbb(vector<int> &arr, std::function<int(int)> const &foo) {

    parallel_for((size_t) 0, arr.size(), [&](int i) { arr[i] = foo(arr[i]); });
}

double
time_a_map(vector<int> &arr, function<int(int)> const &foo,
           function<void(vector<int> &arr, function<int(int)>)> const &map_function) {

    double acc{};

    for (int i = 0; i < 10; i++) {
        auto start = steady_clock::now();
        map_function(arr, foo);
        auto end = steady_clock::now();

        acc += duration<double>(end - start).count();
    }

    return acc / 10.0;
}

