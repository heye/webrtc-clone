project(rtc_utility)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_UTILITY_SRC
  source/process_thread_impl.cc
)
if(rtc_build_android)
list(APPEND RTC_UTILITY
  source/helpers_android.cc
  source/jvm_android.cc
)
endif(rtc_build_android)

add_library(${PROJECT_NAME} STATIC ${RTC_UTILITY_SRC})