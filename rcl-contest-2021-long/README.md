# RECRUIT 日本橋ハーフマラソン 2021 〜増刊号〜 ― 農場王 X

## 戦略

その日取れる行動を、その行動をした翌日の行動前資金と、その状態で終了までに得られる資金の和を基準に選択する。


## Usage

At first, download and build the official local tester in `./tools`.

```
wget 'https://img.atcoder.jp/rcl-contest-2021-long/9ee3ca1da522fff7e369dd7f470f1e7a.zip' -O /tmp/tools.zip
unzip -nj /tmp/tools.zip -d tools
```

| Command | Description |
|----|----|
| `make compile` | Compile `main.cpp` |
| `make test` | Execute `a.out` for an input file of `./tools/input_*.txt` (unless `TEST_IN` is specifed) |
| `make bench` | Execute `a.out` for all input files and summarize scores and execution times |
| `make compare-score` | Compare score file `./score.csv` with old one `./_score.csv` (unless `OLD_SCORE_FILE` is specified) |
| `bin/generate-csv-for-graph.bash <pattern>` | Aggregate score files that `<pattern>` matched against to create a chart |

See `Makefile` for details.
