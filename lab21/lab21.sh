# Кодирование по Цезарю всех текстовых файлов в указанном каталоге и его поддиректориях с помощью утилиты tr.
if [ $# -eq 0 ]; then
    echo "Directory path not provided"
    exit 1
fi

TEMP_FILE=$(mktemp)
for FN in $(find $1 -type f -iname '*.txt'); do
    tr '[A-Za-z]' '[D-ZA-Cd-za-c]' < $FN > $TEMP_FILE
    cat $TEMP_FILE > $FN
done
rm "$TEMP_FILE"
