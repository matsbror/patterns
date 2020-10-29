extern crate rand;

use std::time::{Instant};
use rand::thread_rng;
use rand::Rng;

fn main() {
    let mut rng = thread_rng();
    
    let arr: Vec<i64> = (0..200000000).map(|_| rng.gen_range(-100, 100)).collect();

    let start = Instant::now();
    let arr_result = map_seq(&arr, |i| i*2);
    let duration = start.elapsed();
    
    println!("Time for serial map: {:?}", duration);

    for i in 0..200000000 {
        assert!(arr[i] *2 == arr_result[i]);
    }
    

}


fn map_seq(arr: & Vec<i64>, foo: fn(&i64) -> i64) -> Vec<i64> {
    arr.iter().map(foo).collect()
}