project(rtc_common_audio)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

list(APPEND RTC_COMMON_AUDIO_SRC
  audio_converter.cc
  audio_ring_buffer.cc
  audio_util.cc
  blocker.cc
  channel_buffer.cc
  lapped_transform.cc
  real_fourier.cc
  real_fourier_ooura.cc
  resampler/push_resampler.cc
  resampler/push_sinc_resampler.cc
  resampler/resampler.cc
  resampler/sinc_resampler.cc
  smoothing_filter.cc
  sparse_fir_filter.cc
  vad/vad.cc
  wav_file.cc
  wav_header.cc
  window_generator.cc
)

if(rtc_use_openmax_dl)
  list(APPEND RTC_COMMON_AUDIO_SRC
    real_fourier_openmax.cc
  )
  target_compile_definitions(${PROJECT_NAME} PUBLIC "RTC_USE_OPENMAX_DL")
endif(rtc_use_openmax_dl)

if(rtc_buildfor_arm)
  list(APPEND RTC_COMMON_AUDIO_SRC
    signal_processing/complex_bit_reverse_arm.S
    signal_processing/spl_sqrt_floor_arm.S
  )
  # TODO: add check for arm_version 7
  #for now just add filter_ar_fast_q12.c
  list(APPEND RTC_COMMON_AUDIO_SRC
    signal_processing/filter_ar_fast_q12.c
  )
  #[[  if (arm_version >= 7)
      list(APPEND RTC_COMMON_AUDIO_SRC
        signal_processing/filter_ar_fast_q12_armv7.S
      )
    else()
      list(APPEND RTC_COMMON_AUDIO_SRC
        signal_processing/filter_ar_fast_q12.c
      )
    endif(arm_version >= 7)
  ]]
endif(rtc_buildfor_arm)

list(APPEND RTC_COMMON_AUDIO_SRC
  fft4g.c
  ring_buffer.c
  signal_processing/auto_corr_to_refl_coef.c
  signal_processing/auto_correlation.c
  signal_processing/copy_set_operations.c
  signal_processing/cross_correlation.c
  signal_processing/division_operations.c
  signal_processing/downsample_fast.c
  signal_processing/energy.c
  signal_processing/filter_ar.c
  signal_processing/filter_ma_fast_q12.c
  signal_processing/get_hanning_window.c
  signal_processing/get_scaling_square.c
  signal_processing/ilbc_specific_functions.c
  signal_processing/levinson_durbin.c
  signal_processing/lpc_to_refl_coef.c
  signal_processing/min_max_operations.c
  signal_processing/randomization_functions.c
  signal_processing/real_fft.c
  signal_processing/refl_coef_to_lpc.c
  signal_processing/resample.c
  signal_processing/resample_48khz.c
  signal_processing/resample_by_2.c
  signal_processing/resample_by_2_internal.c
  signal_processing/resample_fractional.c
  signal_processing/spl_init.c
  signal_processing/spl_inl.c
  signal_processing/spl_sqrt.c
  signal_processing/splitting_filter.c
  signal_processing/sqrt_of_one_minus_x_squared.c
  signal_processing/vector_scaling_operations.c
  vad/vad_core.c
  vad/vad_filterbank.c
  vad/vad_gmm.c
  vad/vad_sp.c
  vad/webrtc_vad.c
)
# currently mipsel not supported
list(APPEND RTC_COMMON_AUDIO_SRC
  signal_processing/complex_fft.c
)
if(NOT rtc_buildfor_arm OR NOT rtc_buildfor_arm64)
  list(APPEND RTC_COMMON_AUDIO_SRC
    signal_processing/complex_bit_reverse.c
    signal_processing/filter_ar_fast_q12.c
    signal_processing/spl_sqrt_floor.c
  )
endif()

list(APPEND RTC_COMMON_AUDIO_SRC
  signal_processing/dot_product_with_scale.cc
)

list(APPEND RTC_COMMON_AUDIO_SRC
  fir_filter_c.cc
  fir_filter_c.h
  fir_filter_factory.cc
)
if(NOT rtc_buildfor_arm OR NOT rtc_buildfor_arm64)
  list(APPEND RTC_COMMON_AUDIO_SRC
    fir_filter_sse.cc
    fir_filter_sse.h
    resampler/sinc_resampler_sse.cc
  )
  if(rtc_buildfor_linux OR rtc_buildfor_mac)
    target_compile_options(${PROJECT_NAME} -msse2)
  endif(rtc_buildfor_linux OR rtc_buildfor_mac)
endif(NOT rtc_buildfor_arm OR NOT rtc_buildfor_arm64)

if(rtc_build_with_neon)
  list(APPEND RTC_COMMON_AUDIO_SRC
    fir_filter_neon.cc
    fir_filter_neon.h
    resampler/sinc_resampler_neon.cc
    signal_processing/cross_correlation_neon.c
    signal_processing/downsample_fast_neon.c
    signal_processing/min_max_operations_neon.c
  )
  if(rtc_buildfor_arm)
    target_compile_options(${PROJECT_NAME} -mfpu=neon)
  endif(rtc_buildfor_arm)
  if(rtc_use_lto)
    target_compile_options(${PROJECT_NAME} -flto -ffat-lto-objects)
  endif(rtc_use_lto)
endif(rtc_build_with_neon)

add_library(${PROJECT_NAME} STATIC ${RTC_COMMON_AUDIO_SRC})