project(rtc_pc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libsrtp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libsrtp/crypto/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libsrtp "${CMAKE_BINARY_DIR}/libsrtp")
#include_directories(${CMAKE_BINARY_DIR}/libsrtp/include) # for configure.h

check_include_files(winsock2.h HAVE_WINSOCK2_H)
check_include_files(netinet/in.h HAVE_NETINET_IN_H)

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
  externalhmac.cc
  srtpfilter.cc
  srtpsession.cc
  srtptransport.cc
)

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

target_link_libraries(${PROJECT_NAME} libsrtp.lib)
#workaround building with srtp , add definitions for pc project
if(HAVE_NETINET_IN_H)
  target_compile_definitions(${PROJECT_NAME} PUBLIC HAVE_NETINET_IN_H)
endif(HAVE_NETINET_IN_H)
if(HAVE_WINSOCK2_H)
  target_compile_definitions(${PROJECT_NAME} PUBLIC HAVE_WINSOCK2_H)
endif(HAVE_WINSOCK2_H)
