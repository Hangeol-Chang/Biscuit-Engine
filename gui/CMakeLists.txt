cmake_minimum_required(VERSION 3.10)
project(BiscuitGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# vulkan debug flag
# add_definitions(-DGUI_DEBUG)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(BiscuitGUI main.cpp
    src/BiscuitGUI.cpp
    src/VulkanAPI.cpp
    src//VulkanHelper.cpp
)

# 헤더 폴더 추가
target_include_directories(BiscuitGUI
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${Vulkan_INCLUDE_DIRS}
)

# 라이브러리 링크
target_link_libraries(BiscuitGUI 
    ${Vulkan_LIBRARIES}
    glfw    
)