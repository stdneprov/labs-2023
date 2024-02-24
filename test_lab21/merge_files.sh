suffix=".txt"
max_size=1048576  # 1MB = 1024 * 1024 bytes

output_file="output.txt"

for file in *$suffix; do
    if [ -f "$file" ] && [ "$(stat --printf='%s' "$file")" -lt $max_size ]; then
        cat "$file" >> "$output_file"
    fi
done

echo "All files with suffix $suffix and size less than $max_size have been merged into $output_file"

