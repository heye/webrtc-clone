project(api)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../)
include_directories(../logging)
include_directories(../media)
include_directories(../modules/audio_processing)
include_directories(../rtc_base)

list(APPEND API_SRC
  audio/audio_frame.cc
  audio_codecs/audio_decoder.cc
  audio_codecs/audio_encoder.cc
  audio_codecs/audio_format.cc
  audio_codecs/builtin_audio_decoder_factory.cc
  audio_codecs/builtin_audio_encoder_factory.cc
  audio_codecs/g711/audio_decoder_g711.cc
  audio_codecs/g711/audio_encoder_g711.cc
  audio_codecs/g722/audio_decoder_g722.cc
  audio_codecs/g722/audio_encoder_g722.cc
  audio_codecs/ilbc/audio_decoder_ilbc.cc
  audio_codecs/ilbc/audio_encoder_ilbc.cc
  audio_codecs/isac/audio_decoder_isac_fix.cc
  audio_codecs/isac/audio_decoder_isac_float.cc
  audio_codecs/isac/audio_encoder_isac_fix.cc
  audio_codecs/isac/audio_encoder_isac_float.cc
  audio_codecs/L16/audio_decoder_L16.cc
  audio_codecs/L16/audio_encoder_L16.cc
  audio_codecs/opus/audio_decoder_opus.cc
  audio_codecs/opus/audio_encoder_opus.cc
  audio_codecs/opus/audio_encoder_opus_config.cc
  candidate.cc
  fakemetricsobserver.cc
  jsep.cc
  mediaconstraintsinterface.cc
  mediastreaminterface.cc
  mediatypes.cc
  optional.cc
  ortc/mediadescription.cc
  ortc/sessiondescription.cc
  proxy.cc
  rtcerror.cc
  rtpparameters.cc
  rtpreceiverinterface.cc
  rtp_headers.cc
  statstypes.cc
  umametrics.cc
  video/i420_buffer.cc
  video/video_content_type.cc
  video/video_frame.cc
  video/video_frame_buffer.cc
  video/video_timing.cc
  videosourceinterface.cc
  video_codecs/video_encoder.cc
)

add_library(${PROJECT_NAME} STATIC ${API_SRC})
