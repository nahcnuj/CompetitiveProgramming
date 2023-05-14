#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

#[fastout]
fn main() {
    input! {
        h: usize,
        w: usize,
        n: i32,
        range: [((usize, usize), (usize, usize)); n],
    }

    // x[y][x] = (y, x) の右/上との差分
    let mut x = vec![vec![0; w + 2]; h + 2];
    for ((top, left), (bottom, right)) in range {
        x[top][left] += 1;
        x[top][right + 1] -= 1;
        x[bottom + 1][left] -= 1;
        x[bottom + 1][right + 1] += 1;
    }

    // x[y][x] = (y, x) の積雪
    let x = x.cumlative_sum_in_place();

    for row in x.iter().skip(1).take(h) {
        println!(
            "{}",
            row.iter()
                .skip(1)
                .take(w)
                .map(|v| v.to_string())
                .collect::<Vec<_>>()
                .join(" ")
        );
    }
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
        let mut prev = 0;
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
        for c in 1..w {
            for r in 1..h {
                self[r][c] += self[r - 1][c];
            }
        }

        self
    }
}
