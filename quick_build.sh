#!/bin/bash

# ChatRoom2 快速编译脚本
QT_PATH="D:/dev/Qt6.9/6.9.0/msvc2022_64"

echo "开始编译 ChatRoom2..."

# 创建并进入build目录
mkdir -p build && cd build

# CMake配置
echo "配置项目..."
cmake .. -DCMAKE_PREFIX_PATH="$QT_PATH" || exit 1

# 编译
echo "编译项目..."
cmake --build . --config Debug || exit 1

# 部署Qt依赖
echo "部署Qt依赖..."
"$QT_PATH/bin/windeployqt.exe" ./Debug/ChatRoom2.exe || exit 1

echo "编译完成！可执行文件: $(pwd)/Debug/ChatRoom2.exe"

# 可选：直接运行
# ./Debug/ChatRoom2.exe
