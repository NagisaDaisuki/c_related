cmake_minimum_required(VERSION 3.16)
project(LyricWidget VERSION 0.1 LANGUAGES CXX)

# 设置 C++ 17 标准 (Qt6 推荐)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启 Qt 的三个自动处理神器
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 让 CMake 输出 compile_commands.json 供 Neovim clangd 读取
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 寻找 Qt6 组件和 LayerShellQt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets DBus)
find_package(LayerShellQt REQUIRED)

# 定义你的可执行文件
add_executable(${PROJECT_NAME} src/main.cpp)

# 链接 Qt 库与 Layer Shell 接口
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::DBus
    LayerShellQt::Interface
)
