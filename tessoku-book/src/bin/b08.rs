#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

const W: usize = 1500;
const H: usize = 1500;

#[fastout]
fn main() {
    input! {
        n: i32,
        p: [(usize, usize); n],
        q: i32,
        range: [((usize, usize), (usize, usize)); q],
    }

    // x[py][px] = (px, py) の点の数
    let mut x = vec![vec![0; W + 1]; H + 1];
    for (px, py) in p {
        x[py][px] += 1;
    }

    // s[y][x] = 左上 (-1,-1) 右下 (x,y) の長方形内の点の数
    let s = x.cumlative_sum();

    for ((left, top), (right, bottom)) in range {
        let left = left + 1;
        let top = top + 1;
        let right = right + 1;
        let bottom = bottom + 1;

        let ret = s[bottom][right] - s[bottom][left - 1] - s[top - 1][right] + s[top - 1][left - 1];
        println!("{}", ret);
    }
}

pub trait CumlativeSum {
    // 累積和
    fn cumlative_sum(&self) -> Self;
}

impl CumlativeSum for Vec<i32> {
    fn cumlative_sum(&self) -> Self {
        let mut s = vec![0; self.len() + 1];
        for (i, v) in self.iter().enumerate() {
            s[i + 1] = s[i] + v;
        }

        s
    }
}

impl CumlativeSum for Vec<Vec<i32>> {
    fn cumlative_sum(&self) -> Self {
        let h = self.len() as usize;
        let w = self.get(0).unwrap().len() as usize;

        let mut s = Vec::with_capacity(h + 1);
        s.push(vec![0; w+1]);
        // 横方向合計
        for xs in self.iter() {
            s.push(xs.cumlative_sum());
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
