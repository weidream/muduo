set(redis_SRC
    redisPool.cc
    connection.cc
)
set(redis_HEAD
    redisPool.h
    reply.h
    connection.h
    command.h
)
SET(REDIS_INCLUDE_DIR /usr/local/include/hiredis/)

install(FILES ${redis_HEAD} DESTINATION include/dbserver/redis)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${REDIS_INCLUDE_DIR})

add_library(redispool ${redis_SRC})
target_link_libraries(redispool muduo_net hiredis)