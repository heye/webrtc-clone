project(rtc_audio_coding)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/cng/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/red/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/g711/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/g722/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/isac/main/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/pcm16b/include)

option(rtc_include_opus "includes opus source files" OFF)
option(rtc_build_opus "build opus support" OFF)
option(rtc_build_ilbc "build ilbc support" OFF)
option(rtc_build_isac "build isac support" OFF)
option(rtc_build_isacfix "build isac support" ON)
# RED is disabled by default 

if(rtc_build_opus)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/opus)
endif(rtc_build_opus)
if(rtc_build_ilbc)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/ilbc/include)
endif(rtc_build_ilbc)
if(rtc_build_isacfix)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/codecs/isac/fix/include)
endif(rtc_build_isacfix)

if(rtc_build_isac AND NOT rtc_build_isacfix)
  list(APPEND rtc_audio_coding_definitions "WEBRTC_CODEC_ISAC")
endif(rtc_build_isac AND NOT rtc_build_isacfix)
if(rtc_build_isacfix)
  list(APPEND rtc_audio_coding_definitions "WEBRTC_CODEC_ISACFX")
endif(rtc_build_isacfix)
if(rtc_build_ilbc)
  list(APPEND rtc_audio_coding_definitions "WEBRTC_CODEC_ILBC")
endif(rtc_build_ilbc)
if(rtc_build_opus)
  list(APPEND rtc_audio_coding_definitions "WEBRTC_CODEC_OPUS")
endif(rtc_build_opus)

list(APPEND RTC_AUDIO_ILBC_SRC "")
list(APPEND RTC_AUDIO_WEBRTC_OPUS_SRC "")
list(APPEND RTC_AUDIO_ISACFX_SRC "")
list(APPEND RTC_AUDIO_ISAC_SRC "")

list(APPEND RTC_AUDIO_CODING_SRC
  codecs/audio_format_conversion.cc
  acm2/acm_codec_database.cc
  acm2/rent_a_codec.cc
  acm2/acm_receiver.cc
  acm2/acm_resampler.cc
  acm2/audio_coding_module.cc
  acm2/call_statistics.cc
  acm2/codec_manager.cc
  codecs/legacy_encoded_audio_frame.cc
  codecs/cng/audio_encoder_cng.cc
  codecs/cng/webrtc_cng.cc
  codecs/g711/audio_decoder_pcm.cc
  codecs/g711/audio_encoder_pcm.cc
  codecs/g711/g711.c
  codecs/g711/g711_interface.c
  codecs/g722/audio_decoder_g722.cc
  codecs/g722/audio_encoder_g722.cc
  codecs/g722/g722_decode.c
  codecs/g722/g722_encode.c
  codecs/g722/g722_interface.c
)
if(rtc_build_ilbc)
  list(APPEND RTC_AUDIO_ILBC_SRC
    codecs/ilbc/audio_decoder_ilbc.cc
    codecs/ilbc/audio_encoder_ilbc.cc
    codecs/ilbc/abs_quant.c
    codecs/ilbc/abs_quant_loop.c
    codecs/ilbc/augmented_cb_corr.c
    codecs/ilbc/bw_expand.c
    codecs/ilbc/cb_construct.c
    codecs/ilbc/cb_mem_energy.c
    codecs/ilbc/cb_mem_energy_augmentation.c
    codecs/ilbc/cb_mem_energy_calc.c
    codecs/ilbc/cb_search.c
    codecs/ilbc/cb_search_core.c
    codecs/ilbc/cb_update_best_index.c
    codecs/ilbc/chebyshev.c
    codecs/ilbc/comp_corr.c
    codecs/ilbc/constants.c
    codecs/ilbc/create_augmented_vec.c
    codecs/ilbc/decode.c
    codecs/ilbc/decode_residual.c
    codecs/ilbc/decoder_interpolate_lsf.c
    codecs/ilbc/do_plc.c
    codecs/ilbc/encode.c
    codecs/ilbc/energy_inverse.c
    codecs/ilbc/enh_upsample.c
    codecs/ilbc/enhancer.c
    codecs/ilbc/enhancer_interface.c
    codecs/ilbc/filtered_cb_vecs.c
    codecs/ilbc/frame_classify.c
    codecs/ilbc/gain_dequant.c
    codecs/ilbc/gain_quant.c
    codecs/ilbc/get_cd_vec.c
    codecs/ilbc/get_lsp_poly.c
    codecs/ilbc/get_sync_seq.c
    codecs/ilbc/hp_input.c
    codecs/ilbc/hp_output.c
    codecs/ilbc/ilbc.c
    codecs/ilbc/index_conv_dec.c
    codecs/ilbc/index_conv_enc.c
    codecs/ilbc/init_decode.c
    codecs/ilbc/init_encode.c
    codecs/ilbc/interpolate.c
    codecs/ilbc/interpolate_samples.c
    codecs/ilbc/lpc_encode.c
    codecs/ilbc/lsf_check.c
    codecs/ilbc/lsf_interpolate_to_poly_dec.c
    codecs/ilbc/lsf_interpolate_to_poly_enc.c
    codecs/ilbc/lsf_to_lsp.c
    codecs/ilbc/lsf_to_poly.c
    codecs/ilbc/lsp_to_lsf.c
    codecs/ilbc/my_corr.c
    codecs/ilbc/nearest_neighbor.c
    codecs/ilbc/pack_bits.c
    codecs/ilbc/poly_to_lsf.c
    codecs/ilbc/poly_to_lsp.c
    codecs/ilbc/refiner.c
    codecs/ilbc/simple_interpolate_lsf.c
    codecs/ilbc/simple_lpc_analysis.c
    codecs/ilbc/simple_lsf_dequant.c
    codecs/ilbc/simple_lsf_quant.c
    codecs/ilbc/smooth.c
    codecs/ilbc/smooth_out_data.c
    codecs/ilbc/sort_sq.c
    codecs/ilbc/split_vq.c
    codecs/ilbc/state_construct.c
    codecs/ilbc/state_search.c
    codecs/ilbc/swap_bytes.c
    codecs/ilbc/unpack_bits.c
    codecs/ilbc/vq3.c
    codecs/ilbc/vq4.c
    codecs/ilbc/window32_w32.c
    codecs/ilbc/xcorr_coef.c
  )
endif(rtc_build_ilbc)

list(APPEND RTC_AUDIO_ISAC_COMMON_SRC
  codecs/isac/locked_bandwidth_info.cc
  codecs/isac/main/source/arith_routines.c
  codecs/isac/main/source/arith_routines_hist.c
  codecs/isac/main/source/arith_routines_logist.c
  codecs/isac/main/source/bandwidth_estimator.c
  codecs/isac/main/source/crc.c
  codecs/isac/main/source/decode.c
  codecs/isac/main/source/decode_bwe.c
  codecs/isac/main/source/encode.c
  codecs/isac/main/source/encode_lpc_swb.c
  codecs/isac/main/source/entropy_coding.c
  codecs/isac/main/source/fft.c
  codecs/isac/main/source/filter_functions.c
  codecs/isac/main/source/filterbank_tables.c
  codecs/isac/main/source/filterbanks.c
  codecs/isac/main/source/intialize.c
  codecs/isac/main/source/isac.c
  codecs/isac/main/source/lattice.c
  codecs/isac/main/source/lpc_analysis.c
  codecs/isac/main/source/lpc_gain_swb_tables.c
  codecs/isac/main/source/lpc_shape_swb12_tables.c
  codecs/isac/main/source/lpc_shape_swb16_tables.c
  codecs/isac/main/source/lpc_tables.c
  codecs/isac/main/source/pitch_estimator.c
  codecs/isac/main/source/pitch_filter.c
  codecs/isac/main/source/pitch_gain_tables.c
  codecs/isac/main/source/pitch_lag_tables.c
  codecs/isac/main/source/spectrum_ar_model_tables.c
  codecs/isac/main/source/transform.c
)

if(rtc_build_isacfix)
  list(APPEND RTC_AUDIO_ISACFX_SRC
      ${RTC_AUDIO_ISAC_COMMON_SRC}
      codecs/isac/fix/source/audio_decoder_isacfix.cc
      codecs/isac/fix/source/audio_encoder_isacfix.cc
      codecs/isac/fix/source/fft.c
      codecs/isac/fix/source/arith_routines.c
      codecs/isac/fix/source/arith_routines_hist.c
      codecs/isac/fix/source/arith_routines_logist.c
      codecs/isac/fix/source/bandwidth_estimator.c
      codecs/isac/fix/source/decode.c
      codecs/isac/fix/source/decode_bwe.c
      codecs/isac/fix/source/decode_plc.c
      codecs/isac/fix/source/encode.c
      codecs/isac/fix/source/entropy_coding.c
      codecs/isac/fix/source/filterbank_tables.c
      codecs/isac/fix/source/filterbanks.c
      codecs/isac/fix/source/filters.c
      codecs/isac/fix/source/initialize.c
      codecs/isac/fix/source/isacfix.c
      codecs/isac/fix/source/lattice.c
      codecs/isac/fix/source/lattice_c.c
      codecs/isac/fix/source/lpc_masking_model.c
      codecs/isac/fix/source/lpc_tables.c
      codecs/isac/fix/source/pitch_estimator.c
      codecs/isac/fix/source/pitch_estimator_c.c
      codecs/isac/fix/source/pitch_filter.c
      codecs/isac/fix/source/pitch_filter_c.c
      codecs/isac/fix/source/pitch_gain_tables.c
      codecs/isac/fix/source/pitch_lag_tables.c
      codecs/isac/fix/source/spectrum_ar_model_tables.c
      codecs/isac/fix/source/transform.c
      codecs/isac/fix/source/transform_tables.c
  )
  if(rtc_buildfor_arm64)
    list(APPEND RTC_AUDIO_ISACFX_SRC
      codecs/isac/fix/source/lattice_armv7.S
      codecs/isac/fix/source/pitch_filter_armv6.S
    )
  endif(rtc_buildfor_arm64)
  if(rtc_build_with_neon)
    list(APPEND RTC_AUDIO_ISACFX_SRC
      codecs/isac/fix/source/entropy_coding_neon.c
      codecs/isac/fix/source/filterbanks_neon.c
      codecs/isac/fix/source/filters_neon.c
      codecs/isac/fix/source/lattice_neon.c
      codecs/isac/fix/source/transform_neon.c
    )
  endif(rtc_build_with_neon)
endif(rtc_build_isacfix)

if(rtc_build_isac)
  list(APPEND RTC_AUDIO_ISAC_SRC
    ${RTC_AUDIO_ISAC_COMMON_SRC}
    codecs/isac/main/source/audio_decoder_isac.cc
    codecs/isac/main/source/audio_encoder_isac.cc
  )
endif(rtc_build_isac)

list(APPEND RTC_AUDIO_PCM16b_SRC
  codecs/pcm16b/audio_decoder_pcm16b.cc
  codecs/pcm16b/audio_encoder_pcm16b.cc
  codecs/pcm16b/pcm16b_common.cc
  codecs/pcm16b/pcm16b.c
)

if(rtc_build_opus)
  list(APPEND RTC_AUDIO_WEBRTC_OPUS_SRC
    codecs/opus/audio_decoder_opus.cc
    codecs/opus/audio_encoder_opus.cc
    codecs/opus/opus_interface.c
  )
endif(rtc_build_opus)

list(APPEND RTC_AUDIO_AUDIO_NETWORK_ADAPTOR_SRC
  audio_network_adaptor/audio_network_adaptor_config.cc
  audio_network_adaptor/audio_network_adaptor_impl.cc
  audio_network_adaptor/bitrate_controller.cc
  audio_network_adaptor/channel_controller.cc
  audio_network_adaptor/controller.cc
  audio_network_adaptor/controller_manager.cc
  audio_network_adaptor/debug_dump_writer.cc
  audio_network_adaptor/dtx_controller.cc
  audio_network_adaptor/event_log_writer.cc
  audio_network_adaptor/fec_controller_plr_based.cc
  audio_network_adaptor/fec_controller_rplr_based.cc
  audio_network_adaptor/frame_length_controller.cc
)
list(APPEND RTC_AUDIO_NETEQ_SRC
  neteq/neteq_decoder_enum.cc
  neteq/accelerate.cc
  neteq/audio_multi_vector.cc
  neteq/audio_vector.cc
  neteq/background_noise.cc
  neteq/buffer_level_filter.cc
  neteq/comfort_noise.cc
  neteq/cross_correlation.cc
  neteq/decision_logic.cc
  neteq/decision_logic_fax.cc
  neteq/decision_logic_normal.cc
  neteq/decoder_database.cc
  neteq/delay_manager.cc
  neteq/delay_peak_detector.cc
  neteq/dsp_helper.cc
  neteq/dtmf_buffer.cc
  neteq/dtmf_tone_generator.cc
  neteq/expand.cc
  neteq/merge.cc
  neteq/nack_tracker.cc
  neteq/neteq.cc
  neteq/neteq_impl.cc
  neteq/normal.cc
  neteq/packet.cc
  neteq/packet_buffer.cc
  neteq/post_decode_vad.cc
  neteq/preemptive_expand.cc
  neteq/random_vector.cc
  #neteq/red_payload_splitter.cc
  neteq/rtcp.cc
  neteq/statistics_calculator.cc
  neteq/sync_buffer.cc
  neteq/tick_timer.cc
  neteq/time_stretch.cc
  neteq/timestamp_scaler.cc
#TODO: check if it is needed neteq_tools_minimal
)

add_library(${PROJECT_NAME} STATIC ${RTC_AUDIO_CODING_SRC} ${RTC_AUDIO_ILBC_SRC} ${RTC_AUDIO_ISACFX_SRC} ${RTC_AUDIO_ISAC_SRC} ${RTC_AUDIO_PCM16b_SRC} ${RTC_AUDIO_WEBRTC_OPUS_SRC} ${RTC_AUDIO_AUDIO_NETWORK_ADAPTOR_SRC} ${RTC_AUDIO_NETEQ_SRC})

if(rtc_build_with_neon AND rtc_use_lto)
  target_compile_options(${PROJECT_NAME} -flto -ffat-lto-objects)
endif(rtc_build_with_neon AND rtc_use_lto)

if(rtc_build_with_neon AND rtc_buildfor_arm)
  target_compile_options(${PROJECT_NAME} -mfpu=neon)
endif(rtc_build_with_neon AND rtc_buildfor_arm)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${rtc_audio_coding_definitions})

