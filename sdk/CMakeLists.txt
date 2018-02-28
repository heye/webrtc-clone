project(rtc_video)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_VIDEO_SRC
call_stats.cc
encoder_rtcp_feedback.cc
overuse_frame_detector.cc
payload_router.cc
quality_threshold.cc
receive_statistics_proxy.cc
report_block_stats.cc
rtp_streams_synchronizer.cc
rtp_video_stream_receiver.cc
send_delay_stats.cc
send_statistics_proxy.cc
stats_counter.cc
stream_synchronization.cc
transport_adapter.cc
video_receive_stream.cc
video_send_stream.cc
video_stream_decoder.cc
video_stream_encoder.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_VIDEO_SRC})
