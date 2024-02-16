#!/bin/bash

if [[ $1 == "?" ]];then
    echo -e "Hello! This program concatenates the smallest files until their total
size exceeds a file system block.
You can set the input parameters: directory path and
file system block size (you can skip setting them,
there are default values).
You must also confirm that the program is ready to
execute after setting the parameters - enter Y or N
(case does not matter). If the input is incorrect, the program
will exit with an error message. The result of the program is a 
file in which the remaining files are written.
As a result of the work, the file will be placed in the specified directory.
When you run the script again in this folder, all small files will be added to the final file again.
So don't forget to remove it before starting\n"
fi

echo "Enter the path to the desired folder (Default '/home/ares/papka')"
read directory
if [ -z "$directory" ];then
    directory="/home/ares/papka"
fi
if [ ! -d "$directory" ]; then
    
    echo "error: $directory is a not directory"
    exit 1
fi


echo "Enter the block size of the specified device (file system) (Default '4096')"
read block_size
if [ -z "$block_size" ];then
    block_size=4096
fi
re='^[0-9]+$'
if ! [[ $block_size =~ $re ]] ; then
   echo "error: Not a number" >&2; exit 1
fi

echo "The directory and size are set correctly. Do you want to continue (Y or N)"
read ask
if [[ $ask != "Y" ]] && [[ $ask != "N" ]] && [[ $ask != "y" ]] && [[ $ask != "n" ]]; then
    echo "error: You did not answer the question"
    exit 1
fi
if [[ $ask == "N" ]] || [[ $ask == "n" ]]; then
    echo "You interrupted the program"
    exit 0
fi

files=$(find "$directory" -type f -printf "%s %p\n" | sort -n | awk '{print $2}')

concatenated_file="RESULT.txt"
current_size=0

>"$concatenated_file"

for file in $files; do
    file_size=$(stat -c "%s" "$file")
    if ((current_size + file_size <= block_size));then
        cat "$file" >> "$concatenated_file"
        current_size=$((current_size + file_size))
    else
        break
    fi
done

echo "Res file created $concatenated_file"
mv $concatenated_file $directory
exit