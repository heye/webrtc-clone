project(rtc_api_audio_codecs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ilbc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/g711)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/g722)
include_directories(../)

list(APPEND AUDIO_CODECS_SRC 
    audio_decoder.cc
    audio_encoder.cc
    audio_format.cc
    builtin_audio_decoder_factory.cc
    builtin_audio_encoder_factory.cc
  )

  list(APPEND AUDIO_CODECS_SRC
    ilbc/audio_decoder_ilbc.cc
    ilbc/audio_encoder_ilbc.cc
    g711/audio_decoder_g711.cc
    g711/audio_encoder_g711.cc
    g722/audio_decoder_g722.cc
    g722/audio_encoder_g722.cc
    L16/audio_decoder_L16.cc
    L16/audio_encoder_L16.cc
  )

if(rtc_build_isacfix)
  list(APPEND AUDIO_CODECS_SRC
      isac/audio_decoder_isac_fix.cc
      isac/audio_encoder_isac_fix.cc
      )
else()
  list(APPEND AUDIO_CODECS_SRC
      isac/audio_decoder_isac_float.cc
      isac/audio_encoder_isac_float.cc
      )
endif(rtc_buildfor_arm OR rtc_buildfor_arm64)

add_library(${PROJECT_NAME} STATIC ${AUDIO_CODECS_SRC})
