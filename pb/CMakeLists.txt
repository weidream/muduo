find_package(Protobuf REQUIRED)
FILE(GLOB protofiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message(STATUS ${protofiles})
PROTOBUF_GENERATE_CPP(PROTOSRCS PROTOHDRS ${protofiles})

#include_directories(${PROTOBUF_INCLUDE_DIRS})
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#include_directories(${PROTOBUF_INCLUDE_DIR})
#include_directories(${PROJECT_BINARY_DIR})

set_source_files_properties(${PROTOSRCS} PROPERTIES COMPILE_FLAGS "-Wno-conversion -Wno-shadow")
add_library(improto STATIC ${PROTOSRCS} ${PROTOHDRS})
target_link_libraries(improto protobuf)
target_include_directories(improto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

install(FILES ${PROTOHDRS} DESTINATION include/pb)


install(TARGETS improto DESTINATION lib)
message(STATUS "improto2")
