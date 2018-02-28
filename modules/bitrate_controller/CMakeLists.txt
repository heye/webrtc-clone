project(rtc_bitrate_controller)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_BITRATE_CONTROLLER_SRC
  bitrate_controller_impl.cc
  send_side_bandwidth_estimation.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_BITRATE_CONTROLLER_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE "BWE_TEST_LOGGING_COMPILE_TIME_ENABLE=0")
