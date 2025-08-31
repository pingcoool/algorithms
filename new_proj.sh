#!/bin/bash

proj_name="$1"

SOURCE_DIR="./.templates/gtest_template"
DEST_DIR="./$proj_name"

if [[ -e "$DEST_DIR" ]]; then
    echo "错误: 路径已存在: $DEST_DIR"
    exit 1
fi

# 先完整拷贝目录
cp -r "$SOURCE_DIR" "$DEST_DIR"

# 然后在目标目录中替换所有文件的内容
find "$DEST_DIR" -type f -exec sed -i "" "s/01_tree/$1/g" {} \;

/Applications/CLion.app/Contents/MacOS/clion $1

