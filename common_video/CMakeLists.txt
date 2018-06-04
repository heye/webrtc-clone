project(rtc_common_video)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libyuv)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libyuv/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/libyuv "${CMAKE_BINARY_DIR}/libyuv")

list(APPEND RTC_COMMON_VIDEO_SRC
  bitrate_adjuster.cc
  h264/h264_bitstream_parser.cc
  h264/h264_common.cc
  h264/pps_parser.cc
  h264/sps_parser.cc
  h264/sps_vui_rewriter.cc
  i420_buffer_pool.cc
  incoming_video_stream.cc
  libyuv/webrtc_libyuv.cc
  video_frame.cc
  video_frame_buffer.cc
  video_render_frames.cc
)


add_library(${PROJECT_NAME} STATIC ${RTC_COMMON_VIDEO_SRC})
target_link_libraries(${PROJECT_NAME} yuv)