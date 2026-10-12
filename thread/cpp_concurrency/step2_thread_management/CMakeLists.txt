cmake_minimum_required(VERSION 3.10)
project(Step2_Thread)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 关键！必须开启这个

add_executable(my_app src/start_thread.cpp src/con.cpp)
target_include_directories(my_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
