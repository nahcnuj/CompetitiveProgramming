#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

#[fastout]
fn main() {
    input! {
        d: i32,
        n: i32,
        range: [(i32, i32); n],
    }

    // diff[i] = i日目の出席者数の前日比
    let mut diff = vec![0; (d + 2).try_into().unwrap()];
    for (l, r) in range {
        diff[l as usize] += 1;
        diff[(r + 1) as usize] -= 1; // 参加最終日の翌日に -1
    }

    let mut a = 0;
    for d in 1..=d {
        a += diff[d as usize];
        println!("{}", a);
    }
}
