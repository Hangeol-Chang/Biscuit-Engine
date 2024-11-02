cmake_minimum_required(VERSION 3.10)
project(BiscuitEngine)  # project name 다시 생각해볼 것.

find_package(jsoncpp 1.8 REQUIRED)

add_library(BiscuitEngine STATIC
    src/BiscuitEngine.cpp
    src/BakeBehaviour.cpp
    src/FileManager.cpp
    src/EngineDebugger.cpp
)

# 외부에 공개될 api
target_include_directories(BiscuitEngine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

target_include_directories(BiscuitEngine PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# jsoncpp 헤더 경로를 포함
include_directories(${JSONCPP_INCLUDE_DIRS})

# jsoncpp 라이브러리를 BiscuitEngine에 링크
target_link_libraries(BiscuitEngine jsoncpp_lib)
