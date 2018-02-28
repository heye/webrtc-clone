project(rtc_system_wrappers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_SYS_WRAPPER_SRC
  source/aligned_malloc.cc
  source/clock.cc
  source/cpu_features.cc
  source/cpu_info.cc
  source/event.cc
  source/file_impl.cc
  source/rtp_to_ntp_estimator.cc
  source/rw_lock.cc
  source/sleep.cc
  source/timestamp_extrapolator.cc
  source/field_trial_default.cc
  source/metrics_default.cc
)
list(APPEND PLATFORM_SRC "")
if(rtc_build_linux)
  list(APPEND PLATFORM_SRC source/cpu_features_linux.c)
elseif(rtc_build_android)
  list(APPEND PLATFORM_SRC source/cpu_features_android.c)
endif(rtc_build_linux)
if(rtc_build_win)
  list(APPEND PLATFORM_SRC source/event_timer_win.cc source/rw_lock_win.cc)
else()
  list(APPEND PLATFORM_SRC source/event_timer_posix.cc source/rw_lock_posix.cc)
endif()



add_library(${PROJECT_NAME} STATIC ${RTC_SYS_WRAPPER_SRC} ${PLATFORM_SRC})
if(rtc_build_android OR rtc_build_linux OR rtc_build_mac OR rtc_build_ios)
  target_compile_definitions(${PROJECT_NAME} PUBLIC WEBRTC_THREAD_RR)
endif(rtc_build_android OR rtc_build_linux OR rtc_build_mac OR rtc_build_ios)
if(rtc_build_linux)
  target_link_libraries(${PROJECT_NAME} rt)
elseif(rtc_build_win)
  target_link_libraries(${PROJECT_NAME} winmm)
endif(rtc_build_linux)