#!/bin/bash

source_dir="./mandatory"
destination_dir="./bonus"
new_suffix="_bonus"

for bonus_file in "$destination_dir"/*; do
    extension="${bonus_file##*.}"
    filename=$(basename "$bonus_file" ."$extension")
    original_filename="${filename%$new_suffix}.$extension"
    original_file="$source_dir/$original_filename"

    if [ -f "$bonus_file" ] && [ -f "$original_file" ]; then
        diff "$original_file" "$bonus_file"
    fi
    echo "-----------------------------------------------------------------------------------"
done