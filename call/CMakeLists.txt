project(rtc_call)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_CALL_SRC
  syncable.cc
  rtp_config.cc
  rtcp_demuxer.cc
  rtp_demuxer.cc
  rtp_rtcp_demuxer_helper.cc
  rtp_stream_receiver_controller.cc
  rtp_transport_controller_send.cc
  rtx_receive_stream.cc
  bitrate_allocator.cc
  call.cc
  callfactory.cc
  flexfec_receive_stream_impl.cc
  video_config.cc
  video_receive_stream.cc
  video_send_stream.cc
  audio_send_stream.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_CALL_SRC})