set(msgserver_SRCS
  msg_server_proc.cc
  user_manager.cc
  user.cc
  msg_server.cc
  msg_client_db.cc
  main.cc
  )
set(clientserver_SRCS
   test_client.cc
   )
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${PROJECT_BINARY_DIR})

message(STATUS "PROTOBUF_INCLUDE_DIRS = ${PROTOBUF_INCLUDE_DIRS}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "PROTOBUF_INCLUDE_DIR = ${PROTOBUF_INCLUDE_DIR}")
message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")

set_source_files_properties(${msgserver_SRCS} PROPERTIES COMPILE_FLAGS "-Wno-conversion -Wno-shadow")
set_source_files_properties(${clientserver_SRCS} PROPERTIES COMPILE_FLAGS "-Wno-conversion -Wno-shadow")

add_executable(msgserver ${msgserver_SRCS})
target_link_libraries(msgserver muduo_net improtobuf_codec improto protobuf z)

add_executable(msgserver_test_client ${clientserver_SRCS})
target_link_libraries(msgserver_test_client muduo_net improtobuf_codec improto protobuf z)


