cmake_minimum_required(VERSION 3.10)
project(MyProducerConsumer)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(MyProducerConsumer
    src/main.cpp
    src/producer.cpp
    src/consumer.cpp
    src/buffer.cpp
)

target_include_directories(MyProducerConsumer PRIVATE include)
target_link_libraries(MyProducerConsumer PRIVATE Threads::Threads)

