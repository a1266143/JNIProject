#注意:当你重命名或者移出本CMakeList中的库的时候，需要Build>Clean Project

#指定CMake的最低版本，这将影响你能使用的Cmake的功能
cmake_minimum_required(VERSION 3.4.1)


#---------------------添加库-----------------------
add_library(
# 指定库名称
native-lib
#指定库类型,动态库还是静态库
SHARED
#指定源文件路径
src/main/cpp/native-lib.cpp )

#--------------------包含头文件------------------------
#include_directories(src/main/cpp/include/)

#--------------------添加NDK功能-----------------------
#预构建的NDK库已经添加到Android平台，所以你不需要构建或打包NDK库
#并且NDK库已经是Cmake的搜索路径的一部分，你甚至不需要指定NDK库在你本地已安装的NDK路径
#你仅仅需要给CMake提供你想要使用和链接的NDK库的名称

#通过find_library()命令定义一个变量来定位并存储NDK库的路径
#你可以通过这个变量在本脚本的另外的部分指定NDK库

#---------------------添加Oboe-------------------------
# Set the path to the Oboe directory.
set (OBOE_DIR ../../oboe)

# Add the Oboe library as a subdirectory in your project.
# add_subdirectory tells CMake to look in this directory to
# compile oboe source files using oboe's CMake file.
# ./oboe specifies where the compiled binaries will be stored
add_subdirectory (${OBOE_DIR} ./oboe)

# Specify the path to the Oboe header files.
# This allows targets compiled with this CMake (application code)
# to see public Oboe headers, in order to access its API.
include_directories (${OBOE_DIR}/include)


find_library(
#定义一个log库的别名
log-lib
#指定CMake需要定位的NDK库的名称
log
)


#----------------------链接---------------------------
#为了你自己写的本地的C++文件能够调用NDK中的log库，你需要通过target_link_libraries()命令来进行链接它们

target_link_libraries(
#指定链接的目标库
native-lib
#链接oboe
oboe
#指定你想要链接的库
${log-lib}
)
