# 指定CMake最低版本要求
cmake_minimum_required(VERSION 3.16)

# 设置项目名称和使用的语言
project(ChatRoom2 LANGUAGES CXX)

# 设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 导出编译命令供IDE使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 跨平台编译器配置
if(MSVC)
    # Windows MSVC编译器
    add_compile_options(/utf-8)
    add_compile_options(/W3)  # 警告级别
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Linux GCC编译器
    add_compile_options(-Wall -Wextra -O2)
    add_compile_options(-fPIC)  # 位置无关代码
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # macOS Clang编译器
    add_compile_options(-Wall -Wextra -O2)
endif()

# 平台特定定义
if(WIN32)
    add_compile_definitions(PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(PLATFORM_LINUX)
elseif(APPLE)
    add_compile_definitions(PLATFORM_MACOS)
endif()

# 启用Qt的自动MOC、RCC和UIC功能，自动处理元对象、资源和UI文件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt6所需模块（Core、Gui、Widgets、Network）
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# 列出所有源文件
set(SOURCES
    # logic
    main.cpp
    httpmanager.cpp
    TcpManager.cpp
    global.cpp
    UserManager.cpp
    # ui
    mainwindow.cpp
    logindialog.cpp
    registerdialog.cpp
    resetdialog.cpp
    ChatDialog.cpp

    # custom widgets
    timerbtn.cpp
    clickedlabel.cpp
)

# 列出所有头文件
set(HEADERS
    # logic
    global.h
    httpmanager.h
    TcpManager.h
    singleton.h
    UserManager.h
    
    # ui
    mainwindow.h
    logindialog.h
    registerdialog.h
    resetdialog.h
    ChatDialog.h
    
    # custom widgets
    timerbtn.h
    clickedlabel.h
)

# 列出所有UI文件
set(UIS
    mainwindow.ui
    logindialog.ui
    registerdialog.ui
    resetdialog.ui
    ChatDialog.ui
)

# 创建可执行文件，包含源文件、头文件、UI文件和资源文件
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UIS}
    resources.qrc # 添加资源文件
)   

# 链接Qt6库
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

# 收集resources下的所有png文件
file(GLOB RESOURCE_IMAGES "${CMAKE_SOURCE_DIR}/resources/*.png")

set(RESOURCE_FILES
    ${RESOURCE_IMAGES}
)

foreach(RES_FILE ${RESOURCE_FILES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RES_FILE}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/
    )
endforeach()

# 复制配置文件 config.ini 到可执行文件目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/config.ini
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# 复制样式表文件到可执行文件目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/styles
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/styles/stylesheet.qss
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/styles/stylesheet.qss
)