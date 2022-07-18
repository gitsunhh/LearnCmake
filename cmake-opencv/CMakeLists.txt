cmake_minimum_required(VERSION 2.8)

set(Project_Name DisplayImage)
PROJECT(${Project_Name})

#set(OpenCV_DIR "D:\\programming\\vs library\\opencv\\build") #如果加入环境变量则不需要手动设置
find_package( OpenCV CONFIG REQUIRED )
 
include_directories( ${OpenCV_INCLUDE_DIRS} )
 
add_executable( DisplayImage DisplayImage.cpp )
 
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

message(STATUS "---------------OpenCV library status-----------------")
message(STATUS "version: ${OpenCV_VERSION}")
message(STATUS "libraries: ${OpenCV_LIBS}")
message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "---------------OpenCV library status-----------------")