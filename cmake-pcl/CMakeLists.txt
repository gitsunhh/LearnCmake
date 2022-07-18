# cmake 最低版本要求
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# 项目名称
project(pcl_visualizer_viewports)

# 查找PCL相关库文件，要求PCL最低版本为1.3
find_package(PCL 1.2 REQUIRED)
#find_package(PCL 1.3 REQUIRED COMPONENTS common io)#只需要common 与io模块


include_directories(${PCL_INCLUDE_DIRS})# 头文件包含目录
link_directories(${PCL_LIBRARY_DIRS})# 库目录
add_definitions(${PCL_DEFINITIONS})# 一些PCL宏定义

# 添加项目可执行文件,编译main.cpp
add_executable (pcl_visualizer_demo pcl_visualizer_demo.cpp)

# 链接PCL库文件
target_link_libraries (pcl_visualizer_demo ${PCL_LIBRARIES})
