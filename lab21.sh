#!/bin/bash
arr1=($(find . -name "*.cpp"))
arr2=($(find . -name "*.h"))
arr=("${arr1[@]}" "${arr2[@]}")
total=0
for i in ${!arr[@]}; do
    s=($(wc -l ${arr[$i]}))
    echo ${s[@]}
    total=$(($total+${s[0]}))
done
echo "total lines $total"