# 兼容Qt6.3之前的CMake配置文件
if(QT_VERSION VERSION_LESS 6.3)
    macro(qt_standard_project_setup)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTORCC ON)
        set(CMAKE_AUTOUIC ON)
    endmacro()
endif()

# 兼容6.0之前的qt_add_executable。
if(QT_VERSION VERSION_LESS 6.0)
    macro(qt_add_executable name)
         if(ANDROID)
            add_library(name SHARED ${ARGN})
        else()
            add_executable(${ARGV})
        endif()
    endmacro()
endif()
