set(dbserver_SRC
    db_pool.cc
)
set(dbserver_HEAD
    db_pool.h
    db_errdef.h
)

set(db_pool_test
   db_pool_test.cc
   )
install(FILES ${dbserver_HEAD} DESTINATION include/dbserver)

SET(MYSQL_INCLUDE_DIR /usr/include/mysql)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${MYSQL_INCLUDE_DIR})

set_source_files_properties(${dbserver_SRC} PROPERTIES COMPILE_FLAGS "-Werror=old-style-cast")
add_library(dbserver ${dbserver_SRC})
target_link_libraries(dbserver muduo_net mysqlclient z)

add_executable(db_pool_test ${db_pool_test})
target_link_libraries(db_pool_test dbserver)