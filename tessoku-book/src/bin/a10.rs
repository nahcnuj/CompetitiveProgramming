#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp, cmp::*, convert::TryInto};

#[fastout]
fn main() {
    input! {
        n: i32,
        a: [i32; n],
        d: i32,
        range: [(i32, i32); d],
    }

    // max_from_left[i] = [0, i) 部屋目で最大の定員
    let mut max_from_left = a.clone();
    max_from_left.cumlative_op_in_place(cmp::max);

    // max_from_right[i] = [i, n) 部屋目で最大の定員
    let mut max_from_right = a.clone();
    max_from_right.reverse();
    max_from_right.cumlative_op_in_place(cmp::max);
    max_from_right.reverse();

    for &(l, r) in &range {
        let (l, r) = (l as usize - 1, r as usize - 1);
        println!(
            "{}",
            cmp::max(max_from_left[l - 1], max_from_right[r + 1])
        );
    }
}

pub trait Cumlative<T> {
    /// in-place に累積操作を行う
    fn cumlative_op_in_place<F>(&mut self, op: F) -> &Self
    where
        F: Fn(T, T) -> T;
}

impl Cumlative<i32> for Vec<i32> {
    fn cumlative_op_in_place<F>(&mut self, op: F) -> &Self
    where
        F: Fn(i32, i32) -> i32,
    {
        let mut cum = *self.get(0).unwrap();
        for v in self.iter_mut().skip(1) {
            *v = op(*v, cum);
            cum = *v;
        }
        self
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
