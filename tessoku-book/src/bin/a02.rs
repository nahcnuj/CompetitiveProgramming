#[allow(unused_imports)]
use proconio::{marker::*, *};

#[fastout]
fn main() {
    input! {
        n: i32,
        x: i32,
        a: [i32; n],
    }

    for a in a {
        if a == x {
            println!("Yes");
            return;
        }
    }

    println!("No");
}
