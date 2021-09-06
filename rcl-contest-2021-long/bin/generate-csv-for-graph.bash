#/usr/bin/env bash

set -e

# scores_v2.2.2_*.csv
filename_pattern=${1:-scores_*.csv}

seeds=$(echo -n {0..9} | tr ' ' ',')

read -d '' calc_avg <<'EOS' || true
    BEGIN { mi=999999999; ma=-999999999 }
    { cnt++; sum+=$2; mi=mi>$2?$2:mi; ma=ma<$2?$2:ma; printf "%d,", $2 }
    END { avg=sum/cnt; printf "%.2f,%.2f,%.2f,", mi, avg, ma }
EOS

read -d '' calc_dev <<'EOS' || true
    { printf $0; for (i=2; i<NF-3; i++) stdev+=($i-$13)*($i-$13)/(NF-4-1); sterr=sqrt(stdev); printf "%.2f,%.2f,%.2f,", sterr, $13-sterr, $13+sterr }
EOS

echo parameter,${seeds},min,avg,max,σ,μ-σ,μ+σ,
for filename in $(find scores/ -name "${filename_pattern}" | sort -V); do
    parameter=$(basename ${filename} .csv | grep -o "[0-9]\+$")
    echo $filename $parameter 1>&2

    echo -n $parameter,
    tail -n 10 $filename | sort -n | awk -F',' "$calc_avg" | awk -F',' "$calc_dev"
    echo
done
