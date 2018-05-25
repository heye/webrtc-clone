project(rtc_media)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libyuv)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libyuv/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/usrsctp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/usrsctp/usrsctplib)

set(have_usrsctp_h TRUE CACHE BOOL "workaround" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/usrsctp "${CMAKE_BINARY_DIR}/usrsctp")

list(APPEND RTC_MEDIA_SRC
  base/h264_profile_level_id.cc
  base/adaptedvideotracksource.cc
  base/codec.cc
  base/mediaconstants.cc
  base/mediaengine.cc
  base/rtpdataengine.cc
  base/rtputils.cc
  base/streamparams.cc
  base/turnutils.cc
  base/videoadapter.cc
  base/videobroadcaster.cc
  base/videocapturer.cc
  base/videocommon.cc
  base/videosourcebase.cc
  engine/constants.cc
  engine/convert_legacy_video_factory.cc
  engine/internaldecoderfactory.cc
  engine/internalencoderfactory.cc
  engine/multiplexcodecfactory.cc
  engine/scopedvideodecoder.cc
  engine/scopedvideoencoder.cc
  engine/simulcast_encoder_adapter.cc
  engine/vp8_encoder_simulcast_proxy.cc
  engine/videodecodersoftwarefallbackwrapper.cc
  engine/videoencodersoftwarefallbackwrapper.cc
  engine/adm_helpers.cc
  engine/apm_helpers.cc
  engine/payload_type_mapper.cc
  engine/simulcast.cc
  engine/webrtcmediaengine.cc
  engine/webrtcvideocapturer.cc
  engine/webrtcvideocapturerfactory.cc
  engine/webrtcvideodecoderfactory.cc
  engine/webrtcvideoencoderfactory.cc
  engine/webrtcvideoengine.cc
  engine/webrtcvoiceengine.cc
)

if (rtc_enable_sctp)
  list(APPEND RTC_MEDIA_SRC
    sctp/sctptransport.cc
  )
else()
  list(APPEND RTC_MEDIA_SRC
    sctp/noop.cc
  )
endif()

add_library(${PROJECT_NAME} STATIC ${RTC_MEDIA_SRC})

target_compile_definitions(${PROJECT_NAME} PRIVATE "WEBRTC_INTELLIGIBILITY_ENHANCER=0" "WEBRTC_OPUS_SUPPORT_120MS_PTIME=1")
target_link_libraries(${PROJECT_NAME} usrsctplib)