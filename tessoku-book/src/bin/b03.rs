#[allow(unused_imports)]
use proconio::{marker::*, *};

#[fastout]
fn main() {
    input! {
        n: i32,
        a: [i32; n],
    }

    for (i, a1) in a.iter().enumerate() {
        for (j, a2) in a.iter().enumerate() {
            if i >= j {
                continue;
            }
            for (k, a3) in a.iter().enumerate() {
                if j >= k {
                    continue;
                }
                if a1 + a2 + a3 == 1000 {
                    println!("Yes");
                    return;
                }
            }
        }
    }

    println!("No");
}
