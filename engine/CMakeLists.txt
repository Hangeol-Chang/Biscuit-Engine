cmake_minimum_required(VERSION 3.10)
project(BiscuitEngine)  # project name 다시 생각해볼 것.

add_library(BiscuitEngine STATIC
    src/BiscuitEngine.cpp
    src/BakeBehaviour.cpp
)

# 외부에 공개될 api
target_include_directories(BiscuitEngine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

target_include_directories(BiscuitEngine PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# public copy