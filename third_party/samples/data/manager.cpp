 #include "manager.h"
#include "connection.h"
#include "audio_codecs/builtin_audio_decoder_factory.h"
#include "audio_codecs/builtin_audio_encoder_factory.h"
#include "rtc_base/physicalsocketserver.h"
#include "rtc_base/ssladapter.h"
#include <iostream>
namespace sample
{
  Manager::Manager()
    :mRtcConfig()
    ,mConnection(new Connection())
    ,mDataConfig()
    ,mSocketServer(new rtc::PhysicalSocketServer())
    ,mRtcThread(nullptr)
  {
    webrtc::PeerConnectionInterface::IceServer ice_server;
    ice_server.uri = "stun:stun.l.google.com:19302";
    mRtcConfig.servers.push_back(ice_server);
    mPeerFactory = webrtc::CreatePeerConnectionFactory(
      webrtc::CreateBuiltinAudioEncoderFactory(),
      webrtc::CreateBuiltinAudioDecoderFactory());
    rtc::InitializeSSL();
    auto isOk = mConnection->createPeerConnection(mPeerFactory, mRtcConfig, mDataConfig);
    if (!isOk)
    {
      std::cout << "can't create peer connection";
    }
    mConnection->createOffer();
    mRtcThread = std::make_unique<rtc::AutoSocketServerThread>(mSocketServer.get());
  }
  Manager::~Manager()
  {
    rtc::CleanupSSL();
  }
}