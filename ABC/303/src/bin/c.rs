#[allow(unused_imports)]
use proconio::{marker::*, *};

use std::collections::{HashMap, HashSet};
#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

#[fastout]
fn main() {
    input! {
        n: usize,
        m: usize,
        mut h: i32,
        k: i32,
        s: Chars,
        mut items: [(i32, i32); m],
    }

    let mut can_consume = HashSet::new();
    for item in items {
        can_consume.insert(item);
    }

    let mut p = (0, 0);

    for i in 0..n {
        h -= 1;
        match s[i] {
            'R' => { p.0 += 1 },
            'L' => { p.0 -= 1 },
            'U' => { p.1 += 1 },
            'D' => { p.1 -= 1 },
            _ => unreachable!(),
        }
        if h < 0 {
            println!("No");
            return;
        } else {
            if can_consume.contains(&p) {
                if h < k {
                    can_consume.remove(&p);
                    h = k;
                }
            }
        }
    }

    println!("Yes");
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
