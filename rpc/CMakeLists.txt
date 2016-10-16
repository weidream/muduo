message(STATUS "[rpc]CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
#add_custom_command(OUTPUT rpc.pb.cc rpc.pb.h
#  COMMAND protoc
#  ARGS --cpp_out . ${CMAKE_CURRENT_SOURCE_DIR}/rpc.proto -I${CMAKE_CURRENT_SOURCE_DIR}
#  DEPENDS rpc.proto
#  VERBATIM )

set(im_RPCSRC
    RpcChannel.cc
    RpcServer.cc
   )
set(HEADERS
    RpcChannel.h
    RpcService.h
    RpcClosure.h
    rpc.pb.h
    )

set_source_files_properties(${im_RPCSRC} PROPERTIES COMPILE_FLAGS "-Wno-conversion -Wno-shadow")
add_library(imrpc ${im_RPCSRC})
target_link_libraries(imrpc protobuf improto improtobuf_codec muduo_net z)

install(FILES ${HEADERS} DESTINATION include/rpc)

#add_executable(rpc_service_test ${rpc_server_SRCS})
#target_link_libraries(rpc_service_test muduo_net imrpc improtobuf_codec improto protobuf z)
add_subdirectory(test)