# 工程名称
set(CURRENT_PROJECT_NAME mnserver)

# 添加编译列表
set(CURRENT_PROJECT_SRC_LISTS 
  thread_pool.cpp
  net_message.cpp
  io_service_thread.cpp
  io_service_thread_manager.cpp
  message_filter.cpp
  tcp_client.cpp
  tcp_server.cpp
  tcp_session.cpp
  tcp_session_handler.cpp
  tcp_session_queue.cpp
)

# 包含目录
include_directories(
  ${ASIO_INCLUDE_DIRS}
)

# 链接目录
link_directories(
  ${BINARY_LIB_OUTPUT_DIR}
)

# 配置生成库
if (WIN32)
  add_library(${CURRENT_PROJECT_NAME} STATIC
    ${CURRENT_PROJECT_SRC_LISTS}
  )
else()
  add_library(${CURRENT_PROJECT_NAME} SHARED
    ${CURRENT_PROJECT_SRC_LISTS}
  )
endif()

set_target_properties(${CURRENT_PROJECT_NAME}
  PROPERTIES
  OUTPUT_NAME ${MNSERVER_LIBRARY}
  ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${BINARY_LIB_OUTPUT_DIR}
)
