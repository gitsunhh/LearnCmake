# 获取本目录下的所有文件的列表
aux_source_directory(. DIR_LIB_SRCS)
SET(LIBHELLO_SRC ./my_dll.h ./my_dll.cpp)# 设置变量

find_package(OpenCV CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 指定编译库输出的位置，这个可以设置也可以不设置
#set(LIBRARY_OUTPUT_PATH lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib) #../
# 生成动态库
ADD_LIBRARY(my_dll SHARED ${LIBHELLO_SRC})# 第一个参数为你需要构建的dll的名字，第二个为类型
 
target_link_libraries(my_dll ${OpenCV_LIBS})
# 想要生成动态库和静态库相同名称的的库文件，则需要一个指令set_target_properties
# 这里只是通过重新命名的方法使其名字相同的，构建时还需不能相同
#set_target_properties(mylib_static PROPERTIES OUTPUT_NAME "mylib")
# 为dll设置linker
# 指定dll的生成目录，这里是：./lib_out
SET_TARGET_PROPERTIES(my_dll PROPERTIES LINKER_LANGUAGE CXX#c
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        OUTPUT_NAME "my_dll"
        PREFIX "")

# 这里为了完整也把安装的命令写了上去，这没使用到他
# 安装共享库和头文件
# 将动态库和静态库安装到<prefix>/lib
# install(TARGETS mylib mylib_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
# 安装头文件
#install(FILES func.h DESTINATION include)
INSTALL(TARGETS my_dll)

