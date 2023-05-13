#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

use lib::CumlativeSum;

#[fastout]
fn main() {
    input! {
        h: i32,
        w: i32,
        x: [[i32; w]; h],
        q: i32,
        range: [((usize, usize), (usize, usize)); q],
    }

    // s[h][w] = 左上 (0,0) 右下 (h,w) の長方形内の整数の合計
    let s  = x.cumlative_sum();

    for ((top, left), (bottom, right)) in range {
        let ret = s[bottom][right] - s[bottom][left - 1] - s[top - 1][right] + s[top - 1][left - 1];
        println!("{}", ret);
    }
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
