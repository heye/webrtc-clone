project(rtc_audio_mixer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_AUDIO_MIXER_SRC
  audio_mixer_impl.cc
  default_output_rate_calculator.cc
  frame_combiner.cc
  audio_frame_manipulator.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_AUDIO_MIXER_SRC})
