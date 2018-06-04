project(rtc_base)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/experiments)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/jsoncpp/include)

if(UNIX)
  list(APPEND PLATFORM_SRC file_posix.cc ifaddrs_converter.cc unixfilesystem.cc)
endif()
if(rtc_build_win)
  list(APPEND PLATFORM_SRC file_win.cc
                          win32.cc
                          win32filesystem.cc
                          win32securityerrors.cc
                          win32socketinit.cc
                          win32socketserver.cc
                          win32window.cc
                          noop.cc
      )
endif()
if(APPLE)
  list(APPEND PLATFORM_SRC logging_mac.mm noop.mm thread_darwin.mm macifaddrs_converter.cc macutils.cc)
endif()

if(rtc_enable_libevent)
#TODO: add libevent 
else()
  if(rtc_build_mac OR rtc_build_ios)
  list(APPEND PLATFORM_SRC task_queue_posix.cc task_queue_gcd.cc)
  endif()
  if(rtc_build_win)
    list(APPEND PLATFORM_SRC task_queue_win.cc)
  endif()
endif()

if(rtc_build_android)
  list(APPEND PLATFORM_SRC ifaddrs-android.cc)
  #TODO:
  #[[
  list(APPEND PLATFORM_SRC java/src/org/webrtc/ContextUtils.java
  java/src/org/webrtc/Logging.java
  java/src/org/webrtc/Size.java
  java/src/org/webrtc/ThreadUtils.java)
  ]]
endif()
#set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED) 
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else() 
  message(FATAL "OpenSSL Not Found")
endif()
set(JSONCPP_WITH_TESTS OFF CACHE BOOL "jsoncpp" FORCE)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "jsoncpp" FORCE)
set(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL "Enable jsoncpp pkgconfig support" FORCE)
set(BUILD_STATIC_LIBS ON CAHCE BOOL "jsoncpp build shared ?")
add_subdirectory(../third_party/jsoncpp "${CMAKE_CURRENT_BINARY_DIR}/jsoncpp")

list(APPEND RTC_BASE_SRC
  asyncinvoker.cc
  asyncpacketsocket.cc
  asyncresolverinterface.cc
  asyncsocket.cc
  asynctcpsocket.cc
  asyncudpsocket.cc
  base64.cc
  bitbuffer.cc
  bitrateallocationstrategy.cc
  bufferqueue.cc
  bytebuffer.cc
  checks.cc
  copyonwritebuffer.cc
  crc32.cc
  criticalsection.cc
  cryptstring.cc
  event.cc
  event_tracer.cc
  file.cc
  filerotatingstream.cc
  fileutils.cc
  flags.cc
  helpers.cc
  httpcommon.cc
  ipaddress.cc
  json.cc
  location.cc
  logging.cc
  logsinks.cc
  messagedigest.cc
  messagehandler.cc
  messagequeue.cc
  nethelper.cc
  nethelpers.cc
  network.cc
  networkmonitor.cc
  nullsocketserver.cc
  numerics/exp_filter.cc
  numerics/histogram_percentile_counter.cc
  openssladapter.cc
  openssldigest.cc
  opensslidentity.cc
  opensslstreamadapter.cc
  optionsfile.cc
  pathutils.cc
  physicalsocketserver.cc
  platform_file.cc
  platform_thread.cc
  platform_thread_types.cc
  proxyinfo.cc
  race_checker.cc
  random.cc
  ratelimiter.cc
  ratetracker.cc
  rate_limiter.cc
  rate_statistics.cc
  rtccertificate.cc
  rtccertificategenerator.cc
  sequenced_task_checker_impl.cc
  signalthread.cc
  sigslot.cc
  socketadapters.cc
  socketaddress.cc
  socketaddresspair.cc
  socketstream.cc
  ssladapter.cc
  sslfingerprint.cc
  sslidentity.cc
  sslstreamadapter.cc
  stream.cc
  stringencode.cc
  stringutils.cc
  string_to_number.cc
  thread.cc
  thread_checker_impl.cc
  timestampaligner.cc
  timeutils.cc
  transformadapter.cc
  weak_ptr.cc
  zero_memory.cc
  experiments/alr_experiment.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_BASE_SRC} ${PLATFORM_SRC})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} jsoncpp)
if(using_clang)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wno-sign-compare -Wno-missing-braces)
elseif(rtc_build_win)
  target_compile_options(${PROJECT_NAME} PRIVATE /wd4005 /wd4703)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_NONSTDC_NO_DEPRECATE) 
endif()
