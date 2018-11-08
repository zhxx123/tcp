# 最低版本
cmake_minimum_required(VERSION 2.8)

# 工程名称
project(mnserver C CXX)

# 编译类型
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# 编译选项
if (UNIX)
	set(CMAKE_CXX_FLAGS "-g -std=c++1y -pthread")
endif()
execute_process(COMMAND echo ${CMAKE_CXX_FLAGS})
# 输出目录
set(BINARY_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BINARY_LIB_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 开启分组
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# 配置asio
if (WIN32)
  add_definitions(-DASIO_MSVC)
endif()
add_definitions(-DASIO_STANDALONE)
set(ASIO_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/asio/asio/include)

# 配置mnserver
set(MNSERVER_LIBRARY mnserver)
set(MNSERVER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/mnserver)
# 编译mnserver
add_subdirectory(mnserver)

