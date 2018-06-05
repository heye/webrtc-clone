# pragma once
#include "peerconnectioninterface.h"
namespace rtc
{
  class PhysicalSocketServer;
  class AutoSocketServerThread;
}
namespace sample
{
  class Connection;
  class Manager
  {
  public:
    Manager();
    ~Manager();
  private:
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> mPeerFactory;
    webrtc::PeerConnectionInterface::RTCConfiguration mRtcConfig;
    webrtc::DataChannelInit mDataConfig;
    std::unique_ptr<Connection> mConnection;
    std::unique_ptr<rtc::PhysicalSocketServer> mSocketServer;
    std::unique_ptr<rtc::AutoSocketServerThread> mRtcThread;
  };
}