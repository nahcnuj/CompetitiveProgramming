#/usr/bin/env bash

num=0
sum_diff=0
while read line
do
    seed=$(echo $line | grep -oe "^[^,]\+")
    diff=$(echo $line | sed "s/^[^,]\+,\([^,]\+\)[^|]*|[^,]\+,\([^,]\+\).*/\1 - \2/" | bc)
    (( sum_diff  += $diff ))
    (( sum_diff2 += $diff * $diff ))
    printf "%4d: %10d\n" $seed $diff
    (( num++ ))
done < <(sdiff -s $@)
printf " SUM: %10d\n" $sum_diff
printf " AVG: %13.2f\n" $(echo "$sum_diff / $num" | bc -l)