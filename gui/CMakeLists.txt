cmake_minimum_required(VERSION 3.10)
project(BiscuitGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# vulkan debug flag
# add_definitions(-DGUI_DEBUG)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(../engine ${CMAKE_BINARY_DIR}/engine)

add_executable(BiscuitGUI main.cpp
    src/BiscuitGUI.cpp
    src/VulkanAPI.cpp
    src/VulkanHelper.cpp
    src/BiscuitGUI.cpp
)

# 헤더 폴더 추가
target_include_directories(BiscuitGUI
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/common
    PRIVATE ${Vulkan_INCLUDE_DIRS}
)

# 라이브러리 링크
target_link_libraries(BiscuitGUI 
    ${Vulkan_LIBRARIES}
    glfw
    BiscuitEngine
)

# add_custom_command(
#     TARGET BiscuitGUI
#     PRE_BUILD
#     COMMAND "shader\\compile_shader.bat"
# )

# copy shader files
configure_file(${CMAKE_SOURCE_DIR}/shaders/vert.spv ${CMAKE_BINARY_DIR}/shaders/vert.spv COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shaders/frag.spv ${CMAKE_BINARY_DIR}/shaders/frag.spv COPYONLY)

file(COPY ${CMAKE_SOURCE_DIR}/public DESTINATION ${CMAKE_BINARY_DIR})