# 设置变量
SET(LIBHELLO_SRC ./my_dll.h ./my_dll.cpp)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib_out) #../

# 第一个参数为你需要构建的dll的名字，第二个为类型
ADD_LIBRARY(my_dll SHARED ${LIBHELLO_SRC})
INSTALL(TARGETS my_dll)
# 为dll设置linker
# 指定dll的生成目录，这里是：./lib_out
SET_TARGET_PROPERTIES(my_dll PROPERTIES LINKER_LANGUAGE CXX#c
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        OUTPUT_NAME "my_dll"
        PREFIX "")