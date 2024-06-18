#!/bin/bash
a=$2
for file in *.$1; do
    if [ $(stat -c %s "$file") -lt $a ]; then
     first_letter=$(echo "$file" | cut -c1)
        mv "$file" "${file%.$1}.$first_letter"
    fi
done