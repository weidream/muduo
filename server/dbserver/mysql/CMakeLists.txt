set(mysqlpool_SRC
    db_pool.cc
)
set(mysqlpool_HEAD
    db_pool.h
    db_errdef.h
)

set(db_pool_test
   db_pool_test.cc
   )
install(FILES ${mysqlpool_HEAD} DESTINATION include/dbserver/mysql)

SET(MYSQL_INCLUDE_DIR /usr/include/mysql)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${MYSQL_INCLUDE_DIR})

set_source_files_properties(${mysqlpool_SRC} PROPERTIES COMPILE_FLAGS "-Werror=old-style-cast")
add_library(mysqlpool ${mysqlpool_SRC})
target_link_libraries(mysqlpool muduo_net mysqlclient z)

add_executable(db_pool_test ${db_pool_test})
target_link_libraries(db_pool_test mysqlpool)