# 版本判断
cmake_minimum_required(VERSION 3.16)

# 工程名
project(dll_learn)

#拷贝.dll文件到.exe所在的同级目录下
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/Release/my_dll.dll ${CMAKE_CURRENT_SOURCE_DIR}/build/Release)

# 查找opencv的path
find_package(OpenCV CONFIG REQUIRED)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
# 打印opencv的相关信息
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# 添加子目录，该目录为库目录,会调用子目录的cmake文件，进行构建库
ADD_SUBDIRECTORY(lib)
# 构建可执行文件
add_executable(run_dll run_dll.cpp)
# 添加链接库
# 把子目录src的编译成的动态库文件链接到这里
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(run_dll my_dll ${OpenCV_LIBS})
# 把子目录src编译成的静态库链接到这里
# target_link_libraries(main libmylib.a)
# target_link_libraries(main PRIVATE ${OpenCV_LIBS})
# target_link_libraries(main PRIVATE ${OpenCV_LIBS})