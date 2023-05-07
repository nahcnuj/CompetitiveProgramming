#[allow(unused_imports)]
use proconio::{marker::*, *};

#[fastout]
fn main() {
    input! {
        n8: i32,
    }

    let mut n10 = 0;

    let mut d = 1;
    for i in 0..=8 {
        n10 += (1 << i) * (n8 / d % 10);
        d *= 10;
    }

    println!("{}", n10);
}
