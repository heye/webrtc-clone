#include "manager.h"
#include "audio_codecs/builtin_audio_decoder_factory.h"
#include "audio_codecs/builtin_audio_encoder_factory.h"
namespace sample
{
  Manager::Manager()
    :mConfig()
  {
    webrtc::PeerConnectionInterface::IceServer ice_server;
    ice_server.uri = "stun:stun.l.google.com:19302";
    mConfig.servers.push_back(ice_server);

    mPeerFactory = webrtc::CreatePeerConnectionFactory(
      webrtc::CreateBuiltinAudioEncoderFactory(),
      webrtc::CreateBuiltinAudioDecoderFactory());
  }
}