set(timingWheel_SRCS
   timingWheel_test.cc
)
set(timeHEADERS
    timingWheel.h
    )
install(FILES ${timeHEADERS} DESTINATION include/server)
add_executable(timingWheel_test ${timingWheel_SRCS})
target_link_libraries(timingWheel_test muduo_net)