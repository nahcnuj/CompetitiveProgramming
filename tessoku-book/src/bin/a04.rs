#[allow(unused_imports)]
use proconio::{marker::*, *};

#[fastout]
fn main() {
    input! {
        n: i32,
    }

    let mut s = "0".repeat(10);

    for i in 0..10 {
        let d = 1 << i;
        s.replace_range((10-i-1)..(10-i), if n / d % 2 == 0 { "0" } else { "1" });
    }

    println!("{}", s);
}
