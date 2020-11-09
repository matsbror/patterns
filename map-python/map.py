from multiprocessing import Pool
import time
import random
import numpy as np

def foo(x):
    return x*2

def map_for(arr, foo):
    for el in arr:
        el = foo(el)
    return arr

def map_seq(arr, foo):
    return list(map(foo, arr))

def map_par(arr, foo, pool):
    return pool.map(foo, arr, 10000)

def main():
    arr = [random.randint(-100,100) for i in range(100000000)]

    for_duration = 0
    seq_duration = 0
    par_duration = 0
    np_par_duration = 0

    pool = Pool(4)

    np_arr = np.array(arr)

    for i in range(10):
        
        start = time.time()

        print("for map ", i)
        arr_for = map_for(arr, foo)

        for_end = time.time()

        print("seq map ", i)
        arr_seq = map_seq(arr, foo)

        seq_end = time.time()

        print("par map ", i)
        arr_par = map_par(arr, foo, pool)

        par_end = time.time()

        print("np map ", i)
        np_arr_map = foo(np_arr)
        
        np_par_end = time.time()

        for_duration += (for_end - start)
        seq_duration += (seq_end - for_end)
        par_duration += (par_end - seq_end)
        np_par_duration += (np_par_end - par_end)


    print("For map time: ", for_duration / 10)
    print("Seq map time: ", seq_duration / 10)
    print("Par map time: ", par_duration /10 )
    print("Speedup: ", seq_duration / par_duration)

    print("np map time: ", np_par_duration /10 )
    print("Speedup: ", seq_duration / np_par_duration)

    
def test_map():
    arr = [1, 2, 3, 4, 5, 6]
    arr2 = [2, 4, 6, 8, 10, 12]

    pool = Pool(2)
    arr3 = map_par(arr, foo, pool)

    print(arr)
    print(arr3)

    assert(arr3 == arr2)

    

if __name__ == "__main__":
    test_map()
    main()