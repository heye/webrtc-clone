project(rtc_video_processing)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

if(NOT rtc_buildfor_arm OR NOT rtc_buildfor_arm64)
  set(build_video_processing_sse2 TRUE)
endif()
if(build_video_processing_sse2)
  list(APPEND RTC_VIDEO_PROCESSING_SRC
    util/denoiser_filter_sse2.cc
  )

endif(build_video_processing_sse2)

if (rtc_build_with_neon)
  list(APPEND RTC_VIDEO_PROCESSING_SRC
    util/denoiser_filter_neon.cc
    ) 
endif(rtc_build_with_neon)

if(rtc_build_with_neon AND rtc_buildfor_arm)
  target_compile_options(${PROJECT_NAME} -mfpu=neon)
endif(rtc_build_with_neon AND rtc_buildfor_arm)

if(rtc_build_linux OR rtc_build_mac)
  target_compile_options(${PROJECT_NAME} -msse2)
endif()

add_library(${PROJECT_NAME} STATIC ${RTC_VIDEO_PROCESSING_SRC})