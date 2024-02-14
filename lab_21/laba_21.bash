#!/bin/bash
transcode()
{
    dir=$(pwd)
    for file in "$dir"/* 
    do
        echo $file
        if [[ -f "$file" && $(file --brief --mime-type "$file") == "text/plain" ]]
        then
            iconv -f US-ASCII -t UTF-16 "$file" -o "$file"
        elif [ -d "$file" ]
        then
            cd "$file"
            transcode
            cd "$dir"
        fi
    done
}
transcode
