extern crate rand;
extern crate rayon;

use rand::thread_rng;
use rand::Rng;
use std::time::{Duration, Instant};
use rayon::prelude::*;


const N: u32 = 10;

fn main() {
    let mut rng = thread_rng();
    let mut seq1_duration = Duration::new(0,0);
    let mut par1_duration = Duration::new(0,0);

    for _ in 0..N {
        let mut arr: Vec<i64> = (0..200000000).map(|_| rng.gen_range(-10000, 10000)).collect();
        let arr_copy = arr.clone();

        let start = Instant::now();
        map_seq(arr, |i| i * 2);
        seq1_duration += start.elapsed();

        arr = arr_copy.clone();
        let start = Instant::now();
        map_par(arr, |i| i * 2);
        par1_duration += start.elapsed();

    }
    println!("Time for seq1 map: {:?}", seq1_duration.checked_div(N));
    println!("Time for par1 map: {:?}, speedup: {:?}", par1_duration.checked_div(N), 
                seq1_duration.as_secs_f64() / par1_duration.as_secs_f64());
}

fn map_seq(arr: Vec<i64>, foo: fn(&i64) -> i64) -> Vec<i64> {
    arr.iter().map(foo).collect()
}

fn map_par(arr: Vec<i64>, foo: fn(&i64) -> i64) -> Vec<i64> {
    arr.par_iter().map(foo).collect()
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
    fn test_map_par() {
        let arr1 = vec![1, 2, 3, 4, 5, 6];
        let arr2 = vec![2, 4, 6, 8, 10, 12];

        let arr_result = map_par(arr1, |i| i * 2);

        assert_eq!(arr2, arr_result);
    }
}
