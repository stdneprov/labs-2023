#!/bin/bash

# Определение переменных
SUFFIX=$1
TARGET_LENGTH=$2
PADDING_FILE=$3
# Получение списка файлов с указанным суффиксом
files=$(find ./ -type f -name "$SUFFIX*")

for file in $files; do
  # Получение текущей длины файла
  current_length=$(wc -c < "$file")

  # Расчет необходимого количества копий файла-заполнителя
  padding_count=`expr $TARGET_LENGTH - $current_length`

  # Удлинение файла
  yes `cat $PADDING_FILE` | dd of=$file conv=notrunc oflag=append bs=1 count=$padding_count status=none

  # Вывод информации
  echo "Файл $file удлинен до $TARGET_LENGTH байт."
done
