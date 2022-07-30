CMakeLists文件语法：

1. cmake_minimum_required(VERSION 3.4.1)
该命令用于指定cmake的最小版本
```cmake
cmake_minimum_required(VERSION 2.8)
```

2. project(XXX)
该命令用于确定工程名
```cmake
project(vinJava)
project(demo CXX)
```

3. set (CMAKE_BUILD_TYPE Release/Debug)
该命令用于设置编译模式
```cmake
set(CMAKE_BUILD_TYPE Release)
```

4. include_directories()
该命令用于设置.h文件所在路径
```cmake
include_directories(/usr/local/include/opencv4)
include_directories(${OpenCV_INCLUDE_DIRS})
# 私有so的include文件路径
include_directories("../show_img")
```

5. link_directories()
该命令用于设置链接库文件所在路径
```cmake
link_directories(/usr/local/lib64/opencv4/3rdparty)
# 添加so文件的连接地址
link_directories ("../show_img/lib")
```
>Linux下静态库文件的后缀为 .a
Linux下动态库文件的后缀为 .so
windows下的动态库文件的后缀为 .dll
windows下的静态库文件为 .lib

6. set()
该命令用于设置变量的值，第一个参数为变量名，之后的参数为所需的文件名
```cmake
SET(VIN_SRCS sources/LSY_regression.cpp sources/other_deal.cpp)
SET(VIN_OPENCV libopencv_highgui.a libopencv_imgcodecs.a)
```

7. target_link_libraries()
该命令用于连接指定的库文件，第一个参数为生成的目标文件的文件名
```cmake
# 连接opencv库文件 
target_link_libraries(demo ${OpenCV_LIBS})
# 连接私有so的库文件 
target_link_libraries(${PROJECT_NAME} libshowimg.so libprintstring.so)
```

8. add_library()
该命令的主要作用就是将指定的源文件生成链接文件
```cmake
add_library(showimage SHARED ${DIR_SRC})
```
>该命令的第一个参数为生成的目标文件的文件名，第二个参数是指定生成的库文件的类型，分别为为STATIC、SHARED和MODULE，STATIC代表生成的目标文件为静态库，SHARED代表生成的目标文件为动态库。

9. find_package()
该命令可用于查找安装库的依赖包
```cmake
find_package(OpenCV 4.1.0 REQUIRED)
```

10. add_executable()
该命令用于生成可执行文件
```cmake
# 设置可执行文件的保存路径
set(EXECUTABLE_OUTPUT_PATH ..)#..表示Release文件夹在当前文件夹内生成
# 生成可执行文件
add_executable (demo ${DIR_SRC})
```

add_library()或add_executable()一定要放在include_directories()和link_directories()后面，否则可能会报找不到某些库文件的错误！

其他常用命令：
```cmake
# 待编译文件的地址:添加show_img内头文件的地址，如果目录结构有变化，修改“.”的内容
aux_source_directory(. DIR_SRC)
message(STATUS "SRC: ${DIR_SRC}")
# 设置编译得到的so文件的保存目录为【${PROJECT_SOURCE_DIR}】
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
# 设置so文件的名字为【showimg】，生成的so文件名字为【libshowimg】
# 并设置文件在保存目录下的保存文件夹为【lib】，该文件夹会自动被创立 
install(TARGETS showimg LIBRARY DESTINATION lib)
```

#References

__CmakeLists语法__
[Ubuntu下编译CPP动态链接库及使用方法](https://blog.csdn.net/sunzhao1000/article/details/115264790?spm=1001.2014.3001.5501)
[在CentOS/Ubuntu系统上将opencv的静态库(.a)打包成项目中所需的动态库文件(.so)(使用CMakeLists.txt实现)](https://www.it610.com/article/1274409352542830592.htm)
[如何通过cmake自动拷贝运行所需dll到executable目录](https://www.jianshu.com/p/47370c584356)

__引用函数__
[cmake生成动态链接库dll](https://jasonkayzk.github.io/2021/01/27/cmake%E7%94%9F%E6%88%90%E5%8A%A8%E6%80%81%E9%93%BE%E6%8E%A5%E5%BA%93dll/)
[Lib和DLL调用与实现](https://blog.csdn.net/weixin_45239587/article/details/118990836)
[cmake使用教程（五）调用opencv外部库和自己生成的库](https://blog.csdn.net/weixin_42398658/article/details/121701995)
[C++生成dll和调用dll以及利用CMAKE生成c++ dll的问题](https://blog.csdn.net/yangjj2005/article/details/124673281)

__其他__
[导出DLL的namespace](https://bbs.csdn.net/topics/330143626)