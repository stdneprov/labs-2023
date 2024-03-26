#!/binbash

prefix=$1
if ! [ -n "$prefix" ]; then  #  если не ввели префикс
    prefix="copy_"
fi

folder=~/Desktop/маи_лабы/lab21/files

if [ -z "$(find $folder -mindepth 1 -maxdepth 1)" ]; then  #  проверка на пустую папку
    echo "folder is empty"
else
    for file in "$folder"/*; do
        bn="${file##*/}"   #  берёт краткое имя файла

        if ! [ -w $file ]; then  #  если файл без записи
            copy_file="$folder/$prefix${bn%%.*}.txt"
            cp "$file" "$copy_file"
            chmod 0666 "$copy_file"
            echo "you've copied $bn"
        else
            echo "you can write in file $bn"
        fi
    done
fi
