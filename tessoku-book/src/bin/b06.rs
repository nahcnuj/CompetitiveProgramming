#[allow(unused_imports)]
use proconio::{marker::*, *};

use std::cmp::Ordering;

#[fastout]
fn main() {
    input! {
        n: i32,
        a: [i32; n],
        q: i32,
        range: [(i32, i32); q],
    }

    // i回目までのアタリの数
    let mut s = vec![0];
    for a in a {
        s.push(s.last().unwrap() + a);
    }
    let s = s;

    for (l, r) in range.iter() {
        let lucky = s[*r as usize] - s[(l - 1) as usize];
        let unlucky = r - l + 1 - lucky;

        let ret = match lucky.cmp(&unlucky) {
            Ordering::Greater => "win",
            Ordering::Equal => "draw",
            Ordering::Less => "lose",
        };
        println!("{}", ret);
    }
}
