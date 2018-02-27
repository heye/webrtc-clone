project(rtc_logging)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_LOGGING_SRC
  rtc_event_log/rtc_event_log.cc
  rtc_event_log/rtc_stream_config.cc
  rtc_event_log/events/rtc_event_alr_state.cc
  rtc_event_log/events/rtc_event_audio_network_adaptation.cc
  rtc_event_log/events/rtc_event_audio_playout.cc
  rtc_event_log/events/rtc_event_audio_receive_stream_config.cc
  rtc_event_log/events/rtc_event_audio_send_stream_config.cc
  rtc_event_log/events/rtc_event_bwe_update_delay_based.cc
  rtc_event_log/events/rtc_event_bwe_update_loss_based.cc
  rtc_event_log/events/rtc_event_probe_cluster_created.cc
  rtc_event_log/events/rtc_event_probe_result_failure.cc
  rtc_event_log/events/rtc_event_probe_result_success.cc
  rtc_event_log/events/rtc_event_rtcp_packet_incoming.cc
  rtc_event_log/events/rtc_event_rtcp_packet_outgoing.cc
  rtc_event_log/events/rtc_event_rtp_packet_incoming.cc
  rtc_event_log/events/rtc_event_rtp_packet_outgoing.cc
  rtc_event_log/events/rtc_event_video_receive_stream_config.cc
  rtc_event_log/events/rtc_event_video_send_stream_config.cc
  rtc_event_log/encoder/rtc_event_log_encoder_legacy.cc
  rtc_event_log/output/rtc_event_log_output_file.cc
  rtc_event_log/rtc_event_log_factory.cc
  rtc_event_log/rtc_event_log_impl.cc
  rtc_event_log/events/rtc_event_ice_candidate_pair.cc
  rtc_event_log/events/rtc_event_ice_candidate_pair_config.cc
  rtc_event_log/icelogger.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_LOGGING_SRC})
