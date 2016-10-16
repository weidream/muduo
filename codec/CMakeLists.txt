add_library(improtobuf_codec codec.cc)
target_link_libraries(improtobuf_codec protobuf muduo_net z)
set(HEADERS
    codec.h
    dispatcher_lite.h
    dispatcher.h
    )
install(FILES ${HEADERS} DESTINATION include/codec)
