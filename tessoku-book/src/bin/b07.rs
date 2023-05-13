#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

#[fastout]
fn main() {
    input! {
        t: i32,
        n: i32,
        range: [(i32, i32); n],
    }

    // diff[0] = 0
    // diff[i] = 時刻 i-1 から時刻 i の従業員の増減 (i > 0)
    let mut diff = vec![0; (t + 2).try_into().unwrap()];
    for (l, r) in range {
        diff[l as usize] += 1;
        diff[r as usize] -= 1;
    }

    let mut w = 0;
    for t in 0..t {
        w += diff[t as usize];
        println!("{}", w);
    }
}
