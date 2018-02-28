project(rtc_ortc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


list(APPEND RTC_ORTC_SRC
ortcfactory.cc
ortcrtpreceiveradapter.cc
ortcrtpsenderadapter.cc
rtpparametersconversion.cc
rtptransportadapter.cc
rtptransportcontrolleradapter.cc
)

add_library(${PROJECT_NAME} STATIC ${RTC_ORTC_SRC})
