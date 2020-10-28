// map.cpp : Defines the entry point for the application.
//

#include "map.h"
#include <algorithm>
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

void map_stl(vector<int> &arr, std::function<int(int)> const &foo) {

    transform(arr.begin(), arr.end(), arr.begin(), foo);
}

void map_parstl(vector<int> &arr, std::function<int(int)> const &foo) {

    transform(std::execution::par_unseq, arr.begin(), arr.end(), arr.begin(), foo);
}

void map_for(vector<int> &arr, std::function<int(int)> const &foo) {

    for (long i = 0; i < arr.size(); ++i) {
        arr[i] = foo(arr[i]);
    }
}

void map_threads(vector<int> &arr, std::function<int(int)> const &foo) {
    const auto num_procs = std::thread::hardware_concurrency();

    vector<thread> tpool(num_procs); // create a thread pool

    for (int p = 0; p < num_procs; p++) {
        tpool[p] = thread([&arr, &foo, p, num_procs]() {
            size_t my_start = arr.size() / num_procs * p;
            size_t my_end = arr.size() / num_procs * (p + 1);
            if (p + 1 == num_procs) {
                my_end = arr.size(); // make sure the last thread takes care of the rest of the array
            }
            for (long i = my_start; i < my_end; ++i) {
                arr[i] = foo(arr[i]);
            }
        });
    }

    // wait for threads to finish
    for (auto &t : tpool) {
        t.join();
    }

}

void map_openmp(vector<int> &arr, std::function<int(int)> const &foo) {

#pragma omp parallel for shared(arr, foo) num_threads(omp_get_num_procs())
    for (long i = 0; i < arr.size(); ++i) {
        arr[i] = foo(arr[i]);
    }
}

void map_tbb(vector<int> &arr, std::function<int(int)> const &foo) {

    parallel_for((size_t) 0, arr.size(), foo);

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

