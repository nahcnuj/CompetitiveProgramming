#/usr/bin/env bash

num=0
sum_diff=0
while read line
do
    seed=$(echo $line | grep -oe "^[^,]\+")
    diff=$(echo $line | sed "s/^[^,]\+,\([^,]\+\)[^|]*|[^,]\+,\([^,]\+\).*/\2 - \1/" | bc)
    (( sum_diff  += $diff ))
    (( sum_diff2 += $diff * $diff ))
    printf "%4d: %15d\n" $seed $diff
    (( num++ ))
done < <(sdiff -s $@)
[ $num -eq 0 ] && echo 'No diff!' && exit
printf " SUM: %15d\n" $sum_diff
printf " AVG: %18.2f\n" $(echo "$sum_diff / $num" | bc -l)
