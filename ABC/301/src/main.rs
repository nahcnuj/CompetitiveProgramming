#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, collections::HashMap, convert::TryInto};

#[allow(unused_imports)]
use lib::*;

#[fastout]
fn main() {
    input! {
        s: Chars,
        n: i64,
    }

    // 確定済み桁
    let mut most: i64 = 0;
    for (i, c) in s.iter().enumerate() {
        if c == &'1' {
            most |= 1 << (s.len() - i - 1);
        }
    }

    let mut ret: i64 = if most <= n { most } else { -1 };
    for (i, c) in s.iter().enumerate() {
        if c != &'?' {
            continue;
        }

        let cand = most | (1 << (s.len() - i - 1));
        if cand <= n {
            most = cand;
            ret = cand;
        }
    }
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
