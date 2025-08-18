# 指定CMake最低版本要求
cmake_minimum_required(VERSION 3.16)

# 设置项目名称和使用的语言
project(ChatRoom2 LANGUAGES CXX)

# 设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)

# 导出编译命令供IDE使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置编译器标志以支持UTF-8编码
if(MSVC)
    add_compile_options(/utf-8)
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
    UserInfoWidget.cpp
    AddFriendDialog.cpp
    
    # custom widgets
    timerbtn.cpp
    ClickedLabel.cpp
    SelectedLabel.cpp
    ClickedButton.cpp
    SelectedButton.cpp
    MessageItem.cpp
    MessageListWidget.cpp
    ContactItem.cpp
    ContactListWidget.cpp
    CustomScrollArea.cpp
    ChatListWidget.cpp
    ChatBubble.cpp
    TextBubble.cpp
    ChatItem.cpp
)

# 列出所有头文件
set(HEADERS
    # logic
    global.h
    httpmanager.h
    TcpManager.h
    singleton.h
    UserManager.h
    UserInfo.h
    
    # ui
    mainwindow.h
    logindialog.h
    registerdialog.h
    resetdialog.h
    ChatDialog.h
    UserInfoWidget.h
    AddFriendDialog.h

    
    # custom widgets
    timerbtn.h
    ClickedLabel.h
    SelectedLabel.h
    ClickedButton.h
    SelectedButton.h
    MessageItem.h
    MessageListWidget.h
    ContactItem.h
    ContactListWidget.h
    CustomScrollArea.h
    ChatListWidget.h
    ChatBubble.h
    ChatItem.h
    TextBubble.h
)

# 列出所有UI文件
set(UIS
    mainwindow.ui
    logindialog.ui
    registerdialog.ui
    resetdialog.ui
    ChatDialog.ui
    UserInfoWidget.ui
    AddFriendDialog.ui
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

# 拷贝 resources 目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# 复制配置文件 config.ini 到可执行文件目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/config.ini
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)