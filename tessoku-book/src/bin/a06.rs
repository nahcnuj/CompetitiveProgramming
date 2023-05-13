#[allow(unused_imports)]
use proconio::{marker::*, *};

#[fastout]
fn main() {
    input! {
        n: i32,
        q: i32,
        a: [i32; n],
        range: [(i32, i32); q],
    }

    let mut s = vec![0];
    for a in a {
        s.push(s.last().expect("") + a);
    }
    let s = s;

    for (l, r) in range.iter() {
        let ret = s[*r as usize] - s[(l-1) as usize];
        println!("{}", ret);
    }
}
