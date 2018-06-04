project(rtc_api)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../)
include_directories(../third_party/libyuv/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/video_codecs)
#allways add audio_codecs even if we build data channel only
add_subdirectory(audio_codecs)

list(APPEND API_JINGLE_SRC
  candidate.cc
  jsep.cc
  mediatypes.cc
  proxy.cc
  rtcerror.cc
  rtp_headers.cc
  rtpparameters.cc
  rtpreceiverinterface.cc
  statstypes.cc
  umametrics.cc
)

list(APPEND API_JINGLE_MEDIA_SRC "")
list(APPEND API_JINGLE_MEDIA_SRC
  mediaconstraintsinterface.cc
  mediastreaminterface.cc
  videosourceinterface.cc
)

list(APPEND API_ORTC_SRC
  ortc/mediadescription.cc
  ortc/sessiondescription.cc
)
list(APPEND API_AUDIO_FRAME_SRC "")
list(APPEND API_VIDEO_FRAME_SRC "")

list(APPEND API_AUDIO_FRAME_SRC
  audio/audio_frame.cc
)
list(APPEND API_VIDEO_FRAME_SRC
  video/video_content_type.cc
  video/video_frame.cc
  video/video_frame_buffer.cc
  video/video_timing.cc
  video/i420_buffer.cc
)

list(APPEND API_VIDEO_CODECS_SRC
  video_codecs/video_encoder.cc
)

list(APPEND API_SRC
  optional.cc
)

add_library(${PROJECT_NAME} STATIC ${API_SRC} ${API_VIDEO_FRAME_SRC} ${API_AUDIO_FRAME_SRC} ${API_ORTC_SRC} ${API_JINGLE_SRC} ${API_JINGLE_MEDIA_SRC} ${API_VIDEO_CODECS_SRC})
target_link_libraries(${PROJECT_NAME} rtc_api_audio_codecs)
target_compile_definitions(rtc_api_audio_codecs PUBLIC ${rtc_definitions})