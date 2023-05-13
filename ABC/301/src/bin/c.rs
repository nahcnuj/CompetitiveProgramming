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
        t: Chars,
    }

    let mut s_chars: HashMap<&char, i32> = HashMap::new();
    let mut t_chars: HashMap<&char, i32> = HashMap::new();

    for c in &s {
        if let Some(count) = s_chars.get_mut(c) {
            *count += 1;
        } else {
            s_chars.insert(c, 1);
        }
    }

    for c in &t {
        if let Some(count) = t_chars.get_mut(c) {
            *count += 1;
        } else {
            t_chars.insert(c, 1);
        }
    }

    let atcoder = ['a', 't', 'c', 'o', 'd', 'e', 'r'];
    for c in &atcoder {
        let c_s = s_chars.get(c).copied().unwrap_or(0);
        let c_t = t_chars.get(c).copied().unwrap_or(0);
        if c_s == c_t {
            continue;
        }
        if c_s < c_t {
            let rem = c_t - c_s;
            if let Some(at) = s_chars.get_mut(&'@') {
                if *at < rem {
                    println!("No");
                    return;
                }
                *at -= rem;
            } else {
                println!("No");
                return;
            }
        } else {
            let rem = c_s - c_t;
            if let Some(at) = t_chars.get_mut(&'@') {
                if *at < rem {
                    println!("No");
                    return;
                }
                *at -= rem;
            } else {
                println!("No");
                return;
            }
        }
    }

    for (c, v) in s_chars.iter() {
        if atcoder.contains(&c) {
            continue;
        }
        if v != t_chars.get(c).unwrap_or(&0) {
                println!("No");
                return;
        }
    }
    for (c, v) in t_chars.iter() {
        if atcoder.contains(&c) {
            continue;
        }
        if v != s_chars.get(c).unwrap_or(&0) {
                println!("No");
                return;
        }
    }

    println!("Yes");
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
