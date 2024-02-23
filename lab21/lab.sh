#!/bin/zsh

catolog="./$1"
file=$2
for i in $(find $catolog -print0)
    do
    if [ -f $i ]
    then 
        echo $i
    fi
    done > outpath.txt


if grep -r $2 outpath.txt
then
    grep -r $2 outpath.txt   | tr '\\' '/' > ask.txt
fi
