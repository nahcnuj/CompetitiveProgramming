#/usr/bin/env bash

set -e

for window in {1..1000}; do
    make DEBUG=-DFUTURE_WINDOW=${window} clean all
    cp scores.csv "scores/scores_v2.2.2_${window}.csv"
done
