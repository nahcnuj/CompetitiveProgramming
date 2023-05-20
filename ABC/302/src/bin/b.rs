#[allow(unused_imports)]
use proconio::{marker::*, *};

#[allow(unused_imports)]
use std::{cmp::Ordering, convert::TryInto};

#[allow(unused_imports)]
use itertools::Itertools;

#[fastout]
fn main() {
    input! {
        h: usize,
        w: usize,
        s: [Chars; h],
    }
    for y in 0..h {
        for x in 0..w {
            if x + 4 < w {
                // 横
                let s = (0..5_usize).map(|i| s[y][x + i]).collect::<String>();
                if s == "snuke" {
                    for dx in 0..5_usize {
                        println!("{} {}", y + 1, x + 1 + dx);
                    }
                    return;
                } else if s == "ekuns" {
                    for dx in (0..5_usize).rev() {
                        println!("{} {}", y + 1, x + 1 + dx);
                    }
                    return;
                }
            }
            if y + 4 < h {
                // 縦
                let s = (0..5_usize).map(|i| s[y + i][x]).collect::<String>();
                if s == "snuke" {
                    for dy in 0..5_usize {
                        println!("{} {}", y + dy + 1, x + 1);
                    }
                    return;
                } else if s == "ekuns" {
                    for dy in (0..5_usize).rev() {
                        println!("{} {}", y + dy + 1, x + 1);
                    }
                    return;
                }
            }
            if x + 4 < w && y + 4 < h {
                // みぎななめした
                let s = (0..5_usize).map(|i| s[y + i][x + i]).collect::<String>();
                if s == "snuke" {
                    for d in 0..5_usize {
                        println!("{} {}", y + d + 1, x + d + 1);
                    }
                    return;
                } else if s == "ekuns" {
                    for d in (0..5_usize).rev() {
                        println!("{} {}", y + d + 1, x + d + 1);
                    }
                    return;
                }
            }
            if x as i32 - 4 >= 0 && y + 4 < h {
                // ひだりななめした
                let s = (0..5_usize).map(|i| s[y + i][x - i]).collect::<String>();
                if s == "snuke" {
                    for d in 0..5_usize {
                        println!("{} {}", y + d + 1, x - d + 1);
                    }
                    return;
                } else if s == "ekuns" {
                    for d in (0..5_usize).rev() {
                        println!("{} {}", y + d + 1, x - d + 1);
                    }
                    return;
                }
            }
        }
    }
}
