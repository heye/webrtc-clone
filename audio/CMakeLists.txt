project(rtc_audio)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_AUDIO_SRC
  audio_level.cc
  audio_receive_stream.cc
  audio_send_stream.cc
  audio_state.cc
  audio_transport_impl.cc
  channel.cc
  channel_proxy.cc
  null_audio_poller.cc
  remix_resample.cc
  remix_resample.h
  time_interval.cc
  transport_feedback_packet_loss_tracker.cc
  utility/audio_frame_operations.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_AUDIO_SRC})