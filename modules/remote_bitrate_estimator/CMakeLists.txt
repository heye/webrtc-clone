project(rtc_remote_bitrate_estimator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_REMOTE_BITRATE_ESTIMATOR_SRC
  aimd_rate_control.cc
  bwe_defines.cc
  inter_arrival.cc
  overuse_detector.cc
  overuse_estimator.cc
  remote_bitrate_estimator_abs_send_time.cc
  remote_bitrate_estimator_single_stream.cc
  remote_estimator_proxy.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_REMOTE_BITRATE_ESTIMATOR_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE "BWE_TEST_LOGGING_COMPILE_TIME_ENABLE=0")
