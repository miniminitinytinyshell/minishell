#!/bin/bash

# 원래 파일들이 있는 디렉토리
source_dir="./mandatory"

# 새로운 파일들이 있는 디렉토리
destination_dir="./bonus"

# 원하는 새로운 파일 이름 접미사
new_suffix="_bonus"

# destination_dir에서 모든 파일에 대해 루프를 실행합니다.
for bonus_file in "$destination_dir"/*; do
    # 파일의 확장자 추출
    extension="${bonus_file##*.}"
    # 파일의 기본 이름 추출 (디렉토리 경로를 제외한 이름)
    filename=$(basename "$bonus_file" ."$extension")
    # 원래 파일 이름으로 변환
    original_filename="${filename%$new_suffix}.$extension"
    # 원래 파일의 경로
    original_file="$source_dir/$original_filename"
    
    # destination_dir의 파일이 존재하고 original_file도 존재하는 경우에만 diff 실행
    if [ -f "$bonus_file" ] && [ -f "$original_file" ]; then
        diff "$original_file" "$bonus_file"
    fi
done