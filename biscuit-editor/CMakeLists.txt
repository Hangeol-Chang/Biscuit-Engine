cmake_minimum_required(VERSION 3.10)
project(GtkExample)

# 패키지 구성 도구 사용
find_package(PkgConfig REQUIRED)

# GTK 찾기
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# 헤더 파일 및 라이브러리 추가
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# 실행 파일 추가
add_executable(gtk_example main.cpp)

# 라이브러리 링크
target_link_libraries(gtk_example ${GTK3_LIBRARIES})

# public file copy
configure_file(${CMAKE_SOURCE_DIR}/public/styles.css ${CMAKE_BINARY_DIR}/public/styles.css COPYONLY)
