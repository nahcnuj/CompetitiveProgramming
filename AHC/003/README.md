# AtCoder Heuristic Contest 003

## Basic Strategy

For each query:
1. find and output the shortest path from _s_ to _t_ based on information got until now
2. Assume that the length of every edges including in the path is the given length divided by the number of the edges

## Usage

At first, download and build the official local tester in `./tools`.

| Command | Description |
|----|----|
| `make compile` | Compile `main.cpp` |
| `make test` | Execute `a.out` for `tools/in/0000.txt` |
| `make benchmark` | Execute `a.out` for all input files and summarize scores and execution times |
| `make compare-score` | Compare score file `./score.csv` with old one `./_score.csv` (unless `OLD_SCORE_FILE` is specified) |

See `Makefile` for details.
