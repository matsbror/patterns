extern crate rand;

use rand::thread_rng;
use rand::Rng;
use std::time::{Duration, Instant};

const N: u32 = 10;

fn main() {
    let mut rng = thread_rng();
    let mut seq1_duration = Duration::new(0,0);
    let mut seq2_duration = Duration::new(0,0);

    for _ in 0..N {
        let mut arr: Vec<i64> = (0..200000000).map(|_| rng.gen_range(-10000, 10000)).collect();
        let arr_copy = arr.clone();

        let start = Instant::now();
        map_seq(arr, |i| i * 2);
        seq1_duration += start.elapsed();

        arr = arr_copy.clone();
        let start = Instant::now();
        map_seq2(arr, |i| i * 2);
        seq2_duration += start.elapsed();
    }
    println!("Time for seq1 map: {:?}", seq1_duration/N);
    println!("Time for seq2 map: {:?}", seq2_duration/N);
}

fn map_seq(arr: Vec<i64>, foo: fn(&i64) -> i64) -> Vec<i64> {
    arr.iter().map(foo).collect()
}

fn map_seq2(mut arr: Vec<i64>, foo: fn(&i64) -> i64) -> Vec<i64> {
    for i in 0..arr.len() {
        arr[i] = foo(&arr[i]);
    }

    arr
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_map_seq() {
        let arr1 = vec![1, 2, 3, 4, 5, 6];
        let arr2 = vec![2, 4, 6, 8, 10, 12];

        let arr_result = map_seq(arr1, |i| i * 2);

        assert_eq!(arr2, arr_result);
    }

    #[test]
    fn test_map_seq2() {
        let arr1 = vec![1, 2, 3, 4, 5, 6];
        let arr2 = vec![2, 4, 6, 8, 10, 12];

        let arr_result = map_seq2(arr1, |i| i * 2);

        assert_eq!(arr2, arr_result);
    }
}
