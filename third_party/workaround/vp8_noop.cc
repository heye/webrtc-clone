#include "modules/video_coding/codecs/vp8/include/vp8.h"
#include "rtc_base/checks.h"
namespace webrtc {

std::unique_ptr<VP8Encoder> VP8Encoder::Create() {
  RTC_NOTREACHED();
  return nullptr;
}

std::unique_ptr<VP8Decoder> VP8Decoder::Create() {
  RTC_NOTREACHED();
  return nullptr;
}

}  // namespace webrtc