cmake_minimum_required(VERSION 3.10)
project(BiscuitEditor)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})

# 실행 파일 추가
add_executable(BiscuitEditor main.cpp    
    src/BiscuitEditor.cpp
    src/components/RibonMenu.cpp
)

# 헤더 폴더 추가
target_include_directories(BiscuitEditor 
    PRIVATE ${CMAKE_SOURCE_DIR}/interface
    PRIVATE ${CMAKE_SOURCE_DIR}/interface/components
    PRIVATE ${CMAKE_SOURCE_DIR}/interface/types
)

# 라이브러리 링크
target_link_libraries(BiscuitEditor ${GTKMM_LIBRARIES})
target_compile_options(BiscuitEditor PRIVATE -std=c++17 ${GTKMM_CFLAGS_OTHER})

# public file copy
configure_file(${CMAKE_SOURCE_DIR}/public/styles.css ${CMAKE_BINARY_DIR}/public/styles.css COPYONLY)
