#[allow(unused_imports)]
use proconio::{marker::*, *};

#[fastout]
fn main() {
    input! {
        a: i32,
        b: i32,
    }

    for n in a..=b {
        if 100 % n == 0 {
            println!("Yes");
            return;
        }
    }

    println!("No");
}
