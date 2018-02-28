project(rtc_congestion_controller)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_CONGESTION_CONTROLLER_SRC
  probe_controller.cc
  probe_controller.h
  receive_side_congestion_controller.cc
  send_side_congestion_controller.cc
  send_time_history.cc
  transport_feedback_adapter.cc
  acknowledged_bitrate_estimator.cc
  bitrate_estimator.cc
  median_slope_estimator.cc
  probe_bitrate_estimator.cc
  trendline_estimator.cc
  delay_based_bwe.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_CONGESTION_CONTROLLER_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE "BWE_TEST_LOGGING_COMPILE_TIME_ENABLE=0")
