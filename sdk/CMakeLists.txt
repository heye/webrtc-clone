project(rtc_sdk)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

if(rtc_build_ios OR rtc_build_mac)
  set(rtc_use_metal_rendering ON)
else()
  set(rtc_use_metal_rendering ON)
endif(rtc_build_ios OR rtc_build_mac)

if(rtc_build_ios OR rtc_build_mac)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes/Audio)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes/Common)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes/Metal)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes/PeerConnection)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes/UI)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes/Video)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Classes/VideoToolbox)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/objc/Framework/Headers)
  list(APPEND RTC_SDK_SRC
  )
endif(rtc_build_ios OR rtc_build_mac)

if(rtc_build_ios)
  list(APPEND RTC_SDK_SRC
  )
endif(rtc_build_ios)


add_library(${PROJECT_NAME} STATIC ${RTC_SDK_SRC})
