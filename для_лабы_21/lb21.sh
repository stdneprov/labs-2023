find . -name "*$1" -size -$2c -exec cat {} + > output.txt

