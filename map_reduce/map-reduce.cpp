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
    return transform_reduce(
        arr1.begin(), arr1.end(), arr2.begin(), 
        0,                                  // Initial value
        [](int a, int b){return a+b;},      // reduction operator
        [](int a, int b){return a*b;}      // map operator
        );                           
    
}

int mapred_parstl(std::vector<int> &arr1, std::vector<int> &arr2) {
    return transform_reduce(
        std::execution::par_unseq,
        arr1.begin(), arr1.end(), arr2.begin(), 
        0,
        [](int a, int b){return a+b;},      // reduction operator
        [](int a, int b){return a*b;});     // map operator

}

int mapred_for(std::vector<int> &arr1, std::vector<int> &arr2){

    int sum = 0;
    for (long i = 0; i < arr1.size(); ++i) {
        sum = sum + arr1[i] * arr2[i];
    }
    return sum;
}

int mapred_openmp(std::vector<int> &arr1, std::vector<int> &arr2){

    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < arr1.size(); ++i) {
        sum = sum + arr1[i] * arr2[i];
    }
    return sum;
}

int mapred_threads(std::vector<int> &arr1, std::vector<int> &arr2){
    const auto num_procs = std::thread::hardware_concurrency();

    vector<thread> tpool(num_procs); // create a thread pool

    vector<int> results(num_procs);

    for (int p = 0; p < num_procs; p++) {
        tpool[p] = thread([&arr1, &arr2, p, num_procs, &results]() {
            size_t my_start = arr1.size() / num_procs * p;
            size_t my_end = arr1.size() / num_procs * (p + 1);
            if (p + 1 == num_procs) {
                my_end = arr1.size(); // make sure the last thread takes care of the rest of the array
            }
            int my_sum = 0;
            for (long i = my_start; i < my_end; ++i) {
                my_sum = my_sum + arr1[i] * arr2[i];
            }
            results[p] = my_sum;
        });
    }


    // wait for threads to finish
    int sum = 0;
    for (int p = 0; p < num_procs; p++) {
        tpool[p].join();
        sum = sum + results[p];
    }

    return sum;

}

int mapred_tbb(vector<int> &arr1,vector<int> &arr2) {

    return tbb::parallel_reduce(
        tbb::blocked_range<int>(0, arr1.size()),
        0,
        [&arr1, &arr2](tbb::blocked_range<int> r, int running_sum) {
            for (int i=r.begin(); i<r.end(); ++i){
                running_sum += arr1[i] * arr2[i];
            }
            return running_sum;
        },
        [](int a, int b) {return a+b;}
        );

}

double
time_a_map(vector<int> &arr1, vector<int> &arr2, 
    function<int(vector<int> &arr1,vector<int> &arr2)> const &map_function) {

    double acc{};

    for (int i = 0; i < 10; i++) {
        auto start = steady_clock::now();
        map_function(arr1, arr2);
        auto end = steady_clock::now();

        acc += duration<double>(end - start).count();
    }

    return acc / 10.0;
}

