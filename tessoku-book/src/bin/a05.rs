#[allow(unused_imports)]
use proconio::{marker::*, *};

#[fastout]
fn main() {
    input! {
        n: i32,
        k: i32,
    }

    let mut count = 0;

    for red in 1..=n {
        for blue in 1..=n {
            let white = k - red - blue;
            if 1 <= white && white <= n {
                count += 1;
            }
        }
    }

    println!("{}", count);
}
