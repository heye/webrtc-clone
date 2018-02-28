project(rtc_audio_processing)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

option(rtc_enable_intelligibility_enhancer "enable" OFF) #default
list(APPEND RTC_AUDIO_PROCESSING_COMP_FLAGS "")
list(APPEND RTC_AUDIO_PROCESSING_DEF "WEBRTC_APM_DEBUG_DUMP=0")

list(APPEND RTC_AUDIO_PROCESSING_SRC
  aec/aec_resampler.cc
  aec/echo_cancellation.cc
  aec3/adaptive_fir_filter.cc
  aec3/aec3_common.cc
  aec3/aec3_fft.cc
  aec3/aec_state.cc
  aec3/block_framer.cc
  aec3/block_processor.cc
  aec3/block_processor_metrics.cc
  aec3/cascaded_biquad_filter.cc
  aec3/comfort_noise_generator.cc
  aec3/decimator.cc
  aec3/downsampled_render_buffer.cc
  aec3/echo_canceller3.cc
  aec3/echo_path_delay_estimator.cc
  aec3/echo_path_variability.cc
  aec3/echo_remover.cc
  aec3/echo_remover_metrics.cc
  aec3/erl_estimator.cc
  aec3/erle_estimator.cc
  aec3/fft_buffer.cc
  aec3/frame_blocker.cc
  aec3/main_filter_update_gain.cc
  aec3/matched_filter.cc
  aec3/matched_filter_lag_aggregator.cc
  aec3/matrix_buffer.cc
  aec3/output_selector.cc
  aec3/render_buffer.cc
  aec3/render_delay_buffer.cc
  aec3/render_delay_controller.cc
  aec3/render_delay_controller_metrics.cc
  aec3/render_signal_analyzer.cc
  aec3/residual_echo_estimator.cc
  aec3/shadow_filter_update_gain.cc
  aec3/subtractor.cc
  aec3/suppression_filter.cc
  aec3/suppression_gain.cc
  aec3/vector_buffer.cc
  agc/agc.cc
  agc/agc_manager_direct.cc
  agc/loudness_histogram.cc
  agc/utility.cc
  agc2/gain_controller2.cc
  audio_buffer.cc
  audio_processing_impl.cc
  beamformer/array_util.cc
  beamformer/covariance_matrix_generator.cc
  beamformer/nonlinear_beamformer.cc
  echo_cancellation_impl.cc
  echo_control_mobile_impl.cc
  echo_detector/circular_buffer.cc
  echo_detector/mean_variance_estimator.cc
  echo_detector/moving_max.cc
  echo_detector/normalized_covariance_estimator.cc
  gain_control_for_experimental_agc.cc
  gain_control_impl.cc
  include/audio_processing.cc
  include/config.cc
  level_controller/biquad_filter.cc
  level_controller/down_sampler.cc
  level_controller/gain_applier.cc
  level_controller/gain_selector.cc
  level_controller/level_controller.cc
  level_controller/noise_level_estimator.cc
  level_controller/noise_spectrum_estimator.cc
  level_controller/peak_level_estimator.cc
  level_controller/saturating_gain_estimator.cc
  level_controller/signal_classifier.cc
  level_estimator_impl.cc
  low_cut_filter.cc
  noise_suppression_impl.cc
  residual_echo_detector.cc
  rms_level.cc
  splitting_filter.cc
  three_band_filter_bank.cc
  transient/moving_moments.cc
  transient/transient_detector.cc
  transient/transient_suppressor.cc
  transient/wpd_node.cc
  transient/wpd_tree.cc
  typing_detection.cc
  voice_detection_impl.cc
  include/audio_processing_statistics.cc
  include/aec_dump.cc
  agc/legacy/analog_agc.c
  agc/legacy/digital_agc.c
  logging/apm_data_dumper.cc
)

if (rtc_prefer_fixed_point)
  list(APPEND RTC_AUDIO_PROCESSING_SRC
    ns/noise_suppression_x.c
    ns/nsx_core.c
  )
else()
  list(APPEND RTC_AUDIO_PROCESSING_SRC
    ns/noise_suppression.c
    ns/ns_core.c
  )
endif(rtc_prefer_fixed_point)

list(APPEND RTC_AUDIO_PROCESSING_AEC_CORE
  aec/aec_core.cc
  aecm/aecm_core.cc
  aecm/aecm_core_c.cc
  aecm/echo_control_mobile.cc
  utility/block_mean_calculator.cc
  utility/delay_estimator.cc
  utility/delay_estimator_wrapper.cc
  utility/ooura_fft.cc
)

if(rtc_build_win OR rtc_build_linux OR rtc_build_mac)
  #that is current_cpu == "x86" || current_cpu == "x64"
  list(APPEND RTC_AUDIO_PROCESSING_AEC_CORE
    aec/aec_core_sse2.cc
    utility/ooura_fft_sse2.cc
  )
  list(APPEND RTC_AUDIO_PROCESSING_COMP_FLAGS "-msse2")
endif(rtc_build_win OR rtc_build_linux OR rtc_build_mac)
if(rtc_build_with_neon)
  list(APPEND RTC_AUDIO_PROCESSING_AEC_CORE
   aec/aec_core_neon.cc
   aecm/aecm_core_neon.cc
   utility/ooura_fft_neon.cc
  )
endif(rtc_build_with_neon)


if(rtc_enable_intelligibility_enhancer)
  list(APPEND RTC_AUDIO_PROCESSING_DEF "WEBRTC_INTELLIGIBILITY_ENHANCER=1")
  list(APPEND RTC_AUDIO_PROCESSING_SRC
    intelligibility/intelligibility_enhancer.cc
    intelligibility/intelligibility_utils.cc
  )
else()
  list(APPEND RTC_AUDIO_PROCESSING_DEF "WEBRTC_INTELLIGIBILITY_ENHANCER=0")
endif(rtc_enable_intelligibility_enhancer)

if(rtc_prefer_fixed_point)
  list(APPEND RTC_AUDIO_PROCESSING_DEF "WEBRTC_NS_FIXED")
else()
  list(APPEND RTC_AUDIO_PROCESSING_DEF "WEBRTC_NS_FLOAT")
endif(rtc_prefer_fixed_point)
if(rtc_build_with_neon)
  list(APPEND RTC_AUDIO_PROCESSING_SRC ns/nsx_core_neon.c)
  if(NOT rtc_buildfor_arm64)
    list(APPEND RTC_AUDIO_PROCESSING_COMP_FLAGS "-mfpu=neon")
  endif(NOT rtc_buildfor_arm64)
  if(rtc_use_lto)
    list(APPEND RTC_AUDIO_PROCESSING_COMP_FLAGS "-flto" "-ffat-lto-objects")
  endif(rtc_use_lto)
endif(rtc_build_with_neon)


add_library(${PROJECT_NAME} STATIC ${RTC_AUDIO_PROCESSING_SRC} ${RTC_AUDIO_PROCESSING_AEC_CORE})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${RTC_AUDIO_PROCESSING_DEF})
target_compile_options(${PROJECT_NAME} PRIVATE ${RTC_AUDIO_PROCESSING_COMP_FLAGS})

