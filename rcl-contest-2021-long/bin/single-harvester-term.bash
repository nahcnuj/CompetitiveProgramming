#/usr/bin/env bash

set -e

begin=${1:-0}
end=${2:-1000}
skip=${3:-1}

git checkout -q rcl-contest-2021-long_v3.0.0
trap 'git checkout -; exit 1' SIGINT SIGQUIT SIGKILL SIGTERM

for days in $(seq ${begin} ${skip} ${end}); do
    echo ${days}
    make DEBUG=-DSINGLE_HARVESTER_TERM=${days} clean all
    cp scores.csv "scores/v3.0.0_single-harvester-term/scores_v3.0.0_${days}.csv"
done

git checkout -
