cmake_minimum_required(VERSION 3.16)
project(ChatRoom LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Network)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Network
)
qt_standard_project_setup()


include_directories(${CMAKE_SOURCE_DIR}/header)
include_directories(${CMAKE_SOURCE_DIR}/source)
include_directories(${CMAKE_SOURCE_DIR}/ui)


# 自动收集所有源文件、头文件、UI文件
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/source/*.cpp")
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/header/*.h")
file(GLOB UIS "${CMAKE_SOURCE_DIR}/ui/*.ui")

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")
set(PROJECT_SOURCES ${SOURCES} ${HEADERS} ${UIS})

# QT6 手动添加qrc文件
qt_add_resources(APP_RESOURCES resources.qrc)

# 生成可执行文件
qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${APP_RESOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
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
