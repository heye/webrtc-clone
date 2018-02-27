project(rtc_p2p)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_P2P_SRC
  base/relayserver.cc
  base/relayserver.h
  base/stunserver.cc
  base/stunserver.h
  base/turnserver.cc
  base/turnserver.h
  base/asyncstuntcpsocket.cc
  base/basicpacketsocketfactory.cc
  base/dtlstransport.cc
  base/dtlstransportinternal.cc
  base/icetransportinternal.cc
  base/p2pconstants.cc
  base/p2ptransportchannel.cc
  base/packetlossestimator.cc
  base/packetsocketfactory.cc
  base/packettransportinternal.cc
  base/port.cc
  base/portallocator.cc
  base/portinterface.cc
  base/pseudotcp.cc
  base/relayport.cc
  base/session.cc
  base/stun.cc
  base/stunport.cc
  base/stunrequest.cc
  base/tcpport.cc
  base/transportdescription.cc
  base/transportdescriptionfactory.cc
  base/turnport.cc
  base/udptransport.cc
  client/basicportallocator.cc
  client/turnportfactory.cc
)

list(APPEND RTC_STUNPROBER
  stunprober/stunprober.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_P2P_SRC} ${RTC_STUNPROBER})
target_compile_definitions(${PROJECT_NAME} PRIVATE FEATURE_ENABLE_VOICEMAIL FEATURE_ENABLE_PSTN)
