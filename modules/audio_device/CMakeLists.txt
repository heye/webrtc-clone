project(rtc_audio_device)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

if(NOT rtc_include_internal_audio_device)
  message(FATAL_ERROR "standalone webrtc should be build with internal audio device")
  message(FATAL_ERROR "currently the other option is not supported")
endif(NOT rtc_include_internal_audio_device)

if(rtc_build_win)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win)
elseif(rtc_build_linux)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux)
  option(rtc_include_pulse_audio "enable pulse audio" ON)
  if(NOT rtc_include_pulse_audio)
    message(FATAL_ERROR "standalone webrtc should be build with rtc_include_pulse_audio")
    message(FATAL_ERROR "currently the other option is not supported")
  endif()
elseif(rtc_build_android)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/android)
elseif(rtc_build_ios)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ios)
elseif(rtc_build_mac)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mac)
endif()

list(APPEND RTC_AUDIO_DEVICE_LIBS "")
list(APPEND RTC_AUDIO_DEVICE_DEFINES "")
list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC "")
list(APPEND RTC_AUDIO_DEVICE_SRC
  audio_device_buffer.cc
  audio_device_generic.cc
  dummy/audio_device_dummy.cc
  dummy/file_audio_device.cc
  dummy/file_audio_device_factory.cc
  fine_audio_buffer.cc
  audio_device_data_observer.cc
  audio_device_impl.cc
)

if(rtc_build_ios)
  list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC
    ios/audio_device_ios.mm
    ios/audio_device_not_implemented_ios.mm
    ios/objc/RTCAudioSessionDelegateAdapter.mm
    ios/voice_processing_audio_unit.mm
  )
  list(APPEND RTC_AUDIO_DEVICE_LIBS "-framework UIKit" "-framework Foundation" "-framework AVFoundation" "-framework AudioToolbox")
endif(rtc_build_ios)

if(rtc_include_internal_audio_device)
  list(APPEND RTC_AUDIO_DEVICE_SRC
      audio_device_data_observer.cc
      audio_device_impl.cc
  )
  if(rtc_build_android)
    list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC
        android/audio_manager.cc
        android/audio_record_jni.cc
        android/audio_track_jni.cc
        android/build_info.cc
        android/opensles_common.cc
        android/opensles_player.cc
        android/opensles_recorder.cc
    )
    list(APPEND RTC_AUDIO_DEVICE_LIBS "OpenSLES" "log")
  endif(rtc_build_android)
  if(rtc_build_linux)
    list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC
        linux/alsasymboltable_linux.cc
        linux/audio_device_alsa_linux.cc
        linux/audio_mixer_manager_alsa_linux.cc
        linux/latebindingsymboltable_linux.cc
    )
    list(APPEND RTC_AUDIO_DEVICE_DEFINES
        LINUX_ALSA
    )
    if(rtc_include_pulse_audio)
      list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC
        linux/audio_device_pulse_linux.cc
        linux/audio_mixer_manager_pulse_linux.cc
        linux/pulseaudiosymboltable_linux.cc
      )
      list(APPEND RTC_AUDIO_DEVICE_DEFINES
        LINUX_PULSE
      )
      endif(rtc_include_pulse_audio)
    list(APPEND RTC_AUDIO_DEVICE_LIBS "dl") 
  endif(rtc_build_linux)
  if(rtc_build_mac)
    list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC
      mac/audio_device_mac.cc
      mac/audio_mixer_manager_mac.cc
    )
    #CoreGraphics Needed for CGEventSourceKeyState in audio_device_mac.cc:
    list(APPEND RTC_AUDIO_DEVICE_LIBS "-framework ApplicationServices" "-framework AudioToolbox" "-framework CoreAudio" "-framework CoreGraphics")
  endif(rtc_build_mac)
  if(rtc_build_win)
    list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC
      win/audio_device_core_win.cc
    )
    list(APPEND RTC_AUDIO_DEVICE_LIBS "dmoguids" "wmcodecdspuuid" "amstrmid" "msdmo")
  endif(rtc_build_win)
else(rtc_include_internal_audio_device)
  list(APPEND RTC_AUDIO_DEVICE_DEFINES WEBRTC_DUMMY_AUDIO_BUILD)
endif(rtc_include_internal_audio_device)
if(rtc_build_mac)
  list(APPEND RTC_AUDIO_DEVICE_PLATFORM_SRC mac/portaudio/pa_ringbuffer.c)
endif(rtc_build_mac)


#TODO: add android java files

add_library(${PROJECT_NAME} STATIC ${RTC_AUDIO_DEVICE_SRC} ${RTC_AUDIO_DEVICE_PLATFORM_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${RTC_AUDIO_DEVICE_DEFINES})
target_link_libraries(${PROJECT_NAME} ${RTC_AUDIO_DEVICE_LIBS})
