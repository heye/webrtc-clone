project(rtc_modules)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
add_subdirectory(audio_coding)
add_subdirectory(audio_device)
add_subdirectory(audio_mixer)
add_subdirectory(audio_processing)
add_subdirectory(video_processing)
add_subdirectory(video_coding)
#TODO: video coding needs vpx

  
if(rtc_desktop_capture_supported)
  #TODO: add support for desktop capture
  #add_subdirectory(video_capture)
endif(rtc_desktop_capture_supported)

add_subdirectory(bitrate_controller)
add_subdirectory(congestion_controller)
add_subdirectory(pacing)
add_subdirectory(remote_bitrate_estimator)
add_subdirectory(rtp_rtcp)
add_subdirectory(utility)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE rtc_audio_coding rtc_audio_device rtc_audio_mixer rtc_audio_processing rtc_bitrate_controller rtc_congestion_controller rtc_pacing rtc_remote_bitrate_estimator rtc_rtp_rtcp rtc_utility rtc_video_processing rtc_video_coding)

target_compile_definitions(rtc_audio_coding PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_audio_device PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_audio_mixer PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_audio_processing PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_audio_processing PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_video_processing PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_video_coding PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_bitrate_controller PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_congestion_controller PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_pacing PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_remote_bitrate_estimator PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_rtp_rtcp PUBLIC ${rtc_definitions})
target_compile_definitions(rtc_utility PUBLIC ${rtc_definitions})
