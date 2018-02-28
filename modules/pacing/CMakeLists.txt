project(rtc_pacing)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_PACING_SRC
  alr_detector.cc
  bitrate_prober.cc
  interval_budget.cc
  paced_sender.cc
  packet_queue.cc
  packet_queue_interface.cc
  packet_router.cc
  round_robin_packet_queue.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_PACING_SRC})
