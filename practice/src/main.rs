#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

#[allow(unused_imports)]
use std::io::{stdout, Write};

fn main() {
    let stdin = std::io::stdin();
    let mut source = proconio::source::line::LineSource::new(stdin.lock());
    input! {
        from &mut source,
        n: i32,
        q: i32,
    }
    let mut s = String::new();
    for i in 0..n {
        s.push((i as u8 + 'A' as u8) as char);
    }

    let mut s: Vec<char> = s.chars().collect();
    for i in 0..n {
        for j in 0..n-1 {
            println!("? {} {}", s[j as usize], s[j as usize +1]);
            stdout().flush().unwrap();

            input! {
                from &mut source,
                c: char,
            }
            if c == '>' {
                (s[j as usize], s[j as usize+1]) = (s[j as usize+1], s[j as usize]);
            }
        }
    }
    let s: String = s.into_iter().collect();
    println!("! {}", s);
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
