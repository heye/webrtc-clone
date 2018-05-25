project(rtc_api)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../)
include_directories(../third_party/libyuv/include)

list(APPEND API_JINGLE_SRC
  candidate.cc
  jsep.cc
  mediaconstraintsinterface.cc
  mediastreaminterface.cc
  mediatypes.cc
  proxy.cc
  rtcerror.cc
  rtp_headers.cc
  rtpparameters.cc
  rtpreceiverinterface.cc
  statstypes.cc
  umametrics.cc
  videosourceinterface.cc
)

list(APPEND API_ORTC_SRC
  ortc/mediadescription.cc
  ortc/sessiondescription.cc
)
list(APPEND API_AUDIO_FRAME_SRC "")
list(APPEND API_VIDEO_FRAME_SRC "")

if(NOT build_webrtc_data_only)

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
endif(NOT build_webrtc_data_only)

list(APPEND API_SRC
  optional.cc
)

add_library(${PROJECT_NAME} STATIC ${API_SRC} ${API_VIDEO_FRAME_SRC} ${API_AUDIO_FRAME_SRC} ${API_ORTC_SRC} ${API_JINGLE_SRC})
