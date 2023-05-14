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
        range: [((usize, usize), (usize, usize)); n],
    }

    // x[y][x] = (y, x) の右/上との差分
    let mut x = vec![vec![0; W + 2]; H + 2];
    for ((top, left), (bottom, right)) in range {
        x[top][left] += 1;
        x[top][right] -= 1;
        x[bottom][left] -= 1;
        x[bottom][right] += 1;
    }

    // x[y][x] = (y + 0.5, x + 0.5) の紙の枚数
    let x = x.cumlative_sum_in_place();

    // eprintln!("{:?}", x);
    let ret = x
        .iter().take(H)
        .map(|row| row.iter().take(W).map(|&v| if v > 0 { 1 } else { 0 }).sum::<i32>())
        .sum::<i32>();
    println!("{}", ret);
}

pub trait CumlativeSum {
    /// 累積和を取る
    /// 返り値の先頭要素は番兵の 0 である。
    fn cumlative_sum(&self) -> Self;

    /// in-place に累積和を取る
    fn cumlative_sum_in_place(&mut self) -> &Self;
}

impl CumlativeSum for Vec<i32> {
    fn cumlative_sum(&self) -> Self {
        let mut s = vec![0; self.len() + 1];
        for (i, v) in self.iter().enumerate() {
            s[i + 1] = s[i] + v;
        }

        s
    }

    fn cumlative_sum_in_place(&mut self) -> &Self {
        let mut prev = *self.get(0).unwrap();
        for v in self.iter_mut().skip(1) {
            *v += prev;
            prev = *v;
        }
        self
    }
}

impl CumlativeSum for Vec<Vec<i32>> {
    fn cumlative_sum(&self) -> Self {
        let h = self.len() as usize;
        let w = self.get(0).unwrap().len() as usize;

        let mut s = Vec::with_capacity(h + 1);
        s.push(vec![0; w + 1]);
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

    fn cumlative_sum_in_place(&mut self) -> &Self {
        let h = self.len() as usize;
        let w = self.get(0).unwrap().len() as usize;

        // 横方向合計
        for xs in self.iter_mut() {
            xs.cumlative_sum_in_place();
        }

        // 縦方向合計
        for c in 0..w {
            for r in 1..h {
                self[r][c] += self[r - 1][c];
            }
        }

        self
    }
}
