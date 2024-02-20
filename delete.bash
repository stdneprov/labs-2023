#!/bin/bash

# если первый аргумент равен "?", то выводим подсказку и завершаем программу
if [ "$1" == "?" ]; then
    echo "Usage: $0 [block_size]"
    exit 0
fi

# если первый аргумент не был передан, запрашиваем у пользователя значение числа блоков (block_size)
if [ -z "$1" ]; then
    read -p "Enter block size: " block_size
else
    block_size=$1
fi

# проверка block_size на положительное целое число.
if ! [[ $block_size =~ ^[0-9]+$ ]]; then
    echo "Error: Block size must be a positive integer."
    exit 1
fi

echo "Deleting files with total block size >= $block_size"

total_size=0
deleted_files=0


# проходим по всем файлам в текущем каталоге.
for file in *; do
    # получаем размер каждого файла в блоках
    size=$(stat -c '%b' "$file")
    
    # если размер файла больше или равен block_size, удаляем файл
    if [ $size -ge $block_size ]; then
        rm "$file"
        # увеличиваем суммарный размер удаленных файлов и количество удаленных файлов
        total_size=$((total_size + size))
        deleted_files=$((deleted_files + 1))
    fi
done

# выводим информацию о суммарном размере удаленных файлов и количестве удаленных файлов
echo "Total size of deleted files: $total_size"
echo "Number of deleted files: $deleted_files"