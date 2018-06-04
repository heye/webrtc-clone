project(data_sample)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../../../)
include_directories(../../../api)

add_subdirectory("../../../" "${CMAKE_CURRENT_BINARY_DIR}/webrtc")

list(APPEND SRC
      main.cpp
    # connection.cpp
      manager.cpp
    )

list(APPEND sample_definitions "WEBRTC_WIN" "_CRT_SECURE_NO_WARNINGS" "NOMINMAX" "_UNICODE" "UNICODE" "WIN32_LEAN_AND_MEAN" )
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} webrtc)

if(WIN32 AND rtc_build_win)
  target_link_libraries(${PROJECT_NAME} Ws2_32 Secur32 Iphlpapi)
else()
#TODO:
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC ${sample_definitions})