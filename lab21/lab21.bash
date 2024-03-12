#/bin/bash
i=0
while read line; do i=$((i+1)); done < <(find . -type f -executable)
echo $i 