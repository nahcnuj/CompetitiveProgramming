#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto, collections::{HashMap, HashSet}};

#[fastout]
fn main() {
    input! {
        x: i64,
        y: i64,
        z: i64,
        s: Chars,
    }

    let mut dp = vec![vec![1_000_000_000_000_000_000_i64; 2]; s.len() + 1];
    dp[0][0] = 0;
    dp[0][1] = z;

    for i in 0..s.len() {
        if s[i] == 'a' {
            dp[i+1][0] = std::cmp::min(dp[i][0] + x, dp[i][1] + z + x).min(dp[i][1] + y + z);
            dp[i+1][1] = std::cmp::min(dp[i][0] + y + z, dp[i][1] + y).min(dp[i][0] + z + x);
        } else {
            dp[i+1][0] = std::cmp::min(dp[i][0] + y, dp[i][1] + z + x).min(dp[i][1] + y + z);
            dp[i+1][1] = std::cmp::min(dp[i][0] + z + x, dp[i][1] + x).min(dp[i][0] + y + z);
        }
    }

    println!("{}", dp[s.len()][0].min(dp[s.len()][1]));
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
