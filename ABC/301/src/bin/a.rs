#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

#[allow(unused_imports)]
use lib::*;

#[fastout]
fn main() {
    input! {
        n: i32,
        s: Chars,
    }

    let mut t = 0;
    let mut a = 0;
    for c in &s {
        match c {
            'T' => { t += 1; },
            'A' => { a += 1; },
            _ => panic!(),
        }
    }
    let ret = match t.cmp(&a) {
        Ordering::Greater => String::from("T"),
        Ordering::Less => String::from("A"),
        Ordering::Equal => String::from(if s.last().unwrap().to_string() == String::from("T") { "A" } else { "T" }),
    };
    println!("{}", ret);
}

mod lib {
    pub trait CumlativeSum {
        // 累積和
        fn cumlative_sum(&self) -> Self;
    }

    impl CumlativeSum for Vec<Vec<i32>> {
        fn cumlative_sum(&self) -> Self {
            let h = self.len() as usize;
            let w = self.get(0).unwrap().len() as usize;

            let mut s = vec![vec![0; w + 1]; h + 1];
            // 横方向合計
            for (r, xs) in self.iter().enumerate() {
                let r = r as usize + 1;
                for (c, x) in xs.iter().enumerate() {
                    let c = c as usize + 1;
                    s[r][c] = s[r][c - 1] + x;
                }
            }
            // 縦方向合計
            for c in 1..=w {
                for r in 1..=h {
                    s[r][c] += s[r - 1][c];
                }
            }

            s
        }
    }
}
