project(rtc_pc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_PC_SRC
  createpeerconnectionfactory.cc
  bundlefilter.cc
  channel.cc
  channelmanager.cc
  currentspeakermonitor.cc
  dtlssrtptransport.cc
  jseptransport.cc
  mediasession.cc
  rtcpmuxfilter.cc
  rtpmediautils.cc
  rtptransport.cc
  sessiondescription.cc
  transportcontroller.cc
)

if(rtc_build_libsrtp)
  list(APPEND RTC_PC_SRC
   externalhmac.cc
   srtpfilter.cc
   srtpsession.cc
   srtptransport.cc
  )
endif(rtc_build_libsrtp)

list(APPEND RTC_PEERCONNECTION_SRC
  datachannel.cc
  dtmfsender.cc
  iceserverparsing.cc
  jsepicecandidate.cc
  jsepsessiondescription.cc
  peerconnection.cc
  peerconnectionfactory.cc
  rtcstatscollector.cc
  rtpreceiver.cc
  rtpsender.cc
  rtptransceiver.cc
  sctputils.cc
  sdputils.cc
  statscollector.cc
  webrtcsdp.cc
  webrtcsessiondescriptionfactory.cc
)

list(APPEND RTC_MEDIA_PEERCONNECTION_SRC "")
if(NOT build_webrtc_data_only)
  list(APPEND RTC_MEDIA_PEERCONNECTION_SRC
    audiotrack.cc
    localaudiosource.cc
    mediastream.cc
    mediastreamobserver.cc
    remoteaudiosource.cc
    trackmediainfomap.cc
    videocapturertracksource.cc
    videotrack.cc
    videotracksource.cc
  )
endif(NOT build_webrtc_data_only)



add_library(${PROJECT_NAME} STATIC ${RTC_PC_SRC} ${RTC_PEERCONNECTION_SRC} ${RTC_MEDIA_PEERCONNECTION_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_SCTP)
if(rtc_build_win)
  target_link_libraries(${PROJECT_NAME} strmiids.lib)
endif(rtc_build_win)
if(using_clang OR NOT rtc_build_win)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wno-sign-compare)
elseif(rtc_build_win)
  target_compile_options(${PROJECT_NAME} PRIVATE /wd4245 /wd4389)
endif()
if(rtc_build_libsrtp)
  #TODO:
  target_link_libraries(${PROJECT_NAME} libsrtp.lib)
endif()
