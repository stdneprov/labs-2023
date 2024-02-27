#!/bin/bash
transcode()
{
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

if [[ $1 == "?" ]]; then
    echo -e "Hello! This program goes through the subdirectories recursively and changes the encoding from US-ASCII to UTF-16. 
    You can specify the directory in which you want to recode the files as a parameter, otherwise the script will start from the directory in which it is located.\n"
else
    if [ $# -eq 0 ]; 
    then
	    dir=$(pwd)
    else
        dir=$1
    fi
    transcode
fi
