project(rtc_stats)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_STATS_SRC
  rtcstats.cc
  rtcstats_objects.cc
  rtcstatsreport.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_STATS_SRC})
