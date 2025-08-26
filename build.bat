@echo off
chcp 65001 >nul
setlocal

REM ChatRoom2 一键编译脚本 (Windows版本)
set PROJECT_NAME=ChatRoom
set QT_PATH=D:\dev\Qt6.9\6.9.0\msvc2022_64
set BUILD_TYPE=Debug

echo ================================================
echo      %PROJECT_NAME% 一键编译脚本
echo ================================================

REM 检查Qt路径
if not exist "%QT_PATH%" (
    echo 错误: Qt路径不存在: %QT_PATH%
    echo 请修改脚本中的QT_PATH变量为正确的Qt安装路径
    pause
    exit /b 1
)

REM 步骤1: 创建build目录
echo 步骤1: 创建build目录...
if not exist "build" (
    mkdir build
    echo ✓ build目录创建成功
) else (
    echo ✓ build目录已存在
)

cd build

REM 步骤2: CMake配置
echo 步骤2: 配置CMake项目...
cmake .. -DCMAKE_PREFIX_PATH="%QT_PATH%"
if errorlevel 1 (
    echo ✗ CMake配置失败
    pause
    exit /b 1
)
echo ✓ CMake配置成功

REM 步骤3: 编译项目
echo 步骤3: 编译项目...
cmake --build . --config %BUILD_TYPE%
if errorlevel 1 (
    echo ✗ 项目编译失败
    pause
    exit /b 1
)
echo ✓ 项目编译成功

REM 步骤4: 部署Qt依赖
echo 步骤4: 部署Qt依赖库...
"%QT_PATH%\bin\windeployqt.exe" .\%BUILD_TYPE%\%PROJECT_NAME%.exe
if errorlevel 1 (
    echo ✗ Qt依赖库部署失败
    pause
    exit /b 1
)
echo ✓ Qt依赖库部署成功

REM 完成
echo ================================================
echo 🎉 编译完成！
echo 可执行文件位置: %cd%\%BUILD_TYPE%\%PROJECT_NAME%.exe
echo ================================================

REM 询问是否运行程序
set /p answer="是否现在运行程序? (y/n): "
if /i "%answer%"=="y" (
    echo 启动 %PROJECT_NAME%...
    .\%BUILD_TYPE%\%PROJECT_NAME%.exe
) else if /i "%answer%"=="yes" (
    echo 启动 %PROJECT_NAME%...
    .\%BUILD_TYPE%\%PROJECT_NAME%.exe
)

pause
