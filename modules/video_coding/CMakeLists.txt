project(rtc_video_coding)

if(rtc_use_h264)
  list(APPEND RTC_VIDEO_CODING_SRC_DEFINES WEBRTC_USE_H264)
endif(rtc_use_h264)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_VIDEO_CODING_SRC
  codec_database.cc
  codec_timer.cc
  decoding_state.cc
  encoded_frame.cc
  fec_controller_default.cc
  frame_buffer.cc
  frame_buffer2.cc
  frame_object.cc
  generic_decoder.cc
  generic_encoder.cc
  h264_sprop_parameter_sets.cc
  h264_sps_pps_tracker.cc
  histogram.cc
  inter_frame_delay.cc
  jitter_buffer.cc
  jitter_estimator.cc
  media_opt_util.cc
  media_optimization.cc
  nack_module.cc
  packet.cc
  packet_buffer.cc
  qp_parser.cc
  receiver.cc
  rtp_frame_reference_finder.cc
  rtt_filter.cc
  session_info.cc
  timestamp_map.cc
  timing.cc
  video_codec_initializer.cc
  video_coding_impl.cc
  video_receiver.cc
  video_sender.cc
  utility/default_video_bitrate_allocator.cc
  utility/frame_dropper.cc
  utility/ivf_file_writer.cc
  utility/moving_average.cc
  utility/quality_scaler.cc
  utility/vp8_header_parser.cc
  utility/vp9_uncompressed_header_parser.cc
  codecs/multiplex/multiplex_decoder_adapter.cc
  codecs/multiplex/multiplex_encoded_image_packer.cc
  codecs/multiplex/multiplex_encoder_adapter.cc
)

if(rtc_use_builtin_sw_codecs)
list(APPEND RTC_VIDEO_CODING_SRC
    codecs/i420/i420.cc
    codecs/vp8/default_temporal_layers.cc
    codecs/vp8/screenshare_layers.cc
    codecs/vp8/simulcast_rate_allocator.cc
    codecs/vp8/temporal_layers.cc
    codecs/vp8/vp8_impl.cc
    )
endif(rtc_use_builtin_sw_codecs)

if(rtc_use_h264)
  if(rtc_initialize_ffmpeg)
    list(APPEND RTC_VIDEO_CODING_DEFINES WEBRTC_INITIALIZE_FFMPEG)
  endif(rtc_initialize_ffmpeg)
  list(APPEND RTC_VIDEO_CODING_SRC
      codecs/h264/h264_decoder_impl.cc
      codecs/h264/h264_encoder_impl.cc
      codecs/h264/h264.cc
    )
endif(rtc_use_h264)

if(rtc_libvpx_build_vp9)
  list(APPEND RTC_VIDEO_CODING_SRC
    codecs/vp9/screenshare_layers.cc
    codecs/vp9/vp9_frame_buffer_pool.cc
    codecs/vp9/vp9_impl.cc
  )
else()
  list(APPEND RTC_VIDEO_CODING_SRC
    codecs/vp9/vp9_noop.cc
  )
endif(rtc_libvpx_build_vp9)


# TODO: add ffmpeg
#[[
include(ExternalProject)
find_program(MAKE_EXE NAMES gmake nmake make)
#TODO: implement ffmpeg for different platforms and configurations
# min build without x264
# --disable-all --disable-pthreads --disable-w32threads --disable-os2threads --disable-bzlib --disable-iconv --disable-libxcb --disable-libxcb-shm --disable-libxcb-xfixes --disable-libxcb-shape --disable-lzma --disable-schannel --disable-sdl2 --disable-securetransport --disable-xlib --disable-zlib --disable-audiotoolbox --disable-cuvid --disable-d3d11va --disable-dxva2 --disable-nvenc --disable-vaapi --disable-vda --disable-vdpau --disable-videotoolbox --enable-ffmpeg --enable-small --enable-avcodec --enable-avformat --enable-avfilter --enable-swresample --enable-swscale --enable-encoder='rawvideo' --enable-protocol=file --enable-demuxer=mov --enable-muxer='rawvideo,mp4' --enable-filter=scale --enable-gpl
# min build with x264
# --disable-all --disable-pthreads --disable-w32threads --disable-os2threads --disable-bzlib --disable-iconv --disable-libxcb --disable-libxcb-shm --disable-libxcb-xfixes --disable-libxcb-shape --disable-lzma --disable-schannel --disable-sdl2 --disable-securetransport --disable-xlib --disable-zlib --disable-audiotoolbox --disable-cuvid --disable-d3d11va --disable-dxva2 --disable-nvenc --disable-vaapi --disable-vda --disable-vdpau --disable-videotoolbox --enable-ffmpeg --enable-small --enable-avcodec --enable-avformat --enable-avfilter --enable-swresample --enable-swscale --enable-decoder=h264 --enable-encoder='rawvideo,libx264' --enable-parser=h264 --enable-protocol=file --enable-demuxer=mov --enable-muxer='rawvideo,mp4' --enable-filter=scale --enable-gpl --enable-libx264 --extra-cflags=-I../x264 --extra-cxxflags=-I../x264 --extra-ldflags=-L../x264
set(FFMPEG_BUILD_FLAGS "--disable-all --enable-static --disable-pthreads --disable-w32threads --disable-os2threads --disable-bzlib --disable-iconv --disable-libxcb --disable-libxcb-shm --disable-libxcb-xfixes --disable-libxcb-shape --disable-lzma --disable-schannel --disable-sdl2 --disable-securetransport --disable-xlib --disable-zlib --disable-audiotoolbox --disable-cuvid --disable-d3d11va --disable-dxva2 --disable-nvenc --disable-vaapi --disable-vda --disable-vdpau --disable-videotoolbox --enable-ffmpeg --enable-small --enable-avcodec --enable-avformat --enable-avfilter --enable-swresample --enable-swscale --enable-encoder='rawvideo' --enable-protocol=file --enable-demuxer=mov --enable-muxer='rawvideo,mp4' --enable-filter=scale --enable-gpl")
ExternalProject_add(
  ffmpeg
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/FFMpeg
  CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/FFMpeg/./configure --prefix=${CMAKE_BINARY_DIR} ${FFMPEG_BUILD_FLAGS}
  BUILD_COMMAND ${MAKE_EXE}
)
]]
add_library(${PROJECT_NAME} STATIC ${RTC_VIDEO_CODING_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${RTC_VIDEO_CODING_DEFINES})
#add_dependencies(${PROJECT_NAME} ffmpeg)
