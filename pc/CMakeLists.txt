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
  audiotrack.cc
  datachannel.cc
  dtmfsender.cc
  dtmfsender.h
  iceserverparsing.cc
  jsepicecandidate.cc
  jsepsessiondescription.cc
  localaudiosource.cc
  mediastream.cc
  mediastreamobserver.cc
  peerconnection.cc
  peerconnectionfactory.cc
  remoteaudiosource.cc
  rtcstatscollector.cc
  rtpreceiver.cc
  rtpsender.cc
  rtptransceiver.cc
  sctputils.cc
  sdputils.cc
  statscollector.cc
  trackmediainfomap.cc
  videocapturertracksource.cc
  videotrack.cc
  videotracksource.cc
  webrtcsdp.cc
  webrtcsessiondescriptionfactory.cc
)


add_library(${PROJECT_NAME} STATIC ${RTC_PC_SRC} ${RTC_PEERCONNECTION_SRC})
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
