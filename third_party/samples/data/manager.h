# pragma once
#include "peerconnectioninterface.h"
namespace sample
{
  class Manager
  {
  public:
    Manager();
  private:
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> mPeerFactory;
    webrtc::PeerConnectionInterface::RTCConfiguration mConfig;
  };
}