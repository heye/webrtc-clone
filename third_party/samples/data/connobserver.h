#pragma once
#include "api/peerconnectioninterface.h"

namespace sample
{
  class Connection;

  class ConnectionObs: public webrtc::PeerConnectionObserver
  {
    public:
     ConnectionObs(Connection& aConn);

     void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state) override;
     void OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) override;
     void OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) override;
     void OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel) override;
     void OnRenegotiationNeeded() override;
     void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state) override;
     void OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state) override;
     void OnIceCandidate(const webrtc::IceCandidateInterface* candidate) override;

  private:
    Connection& mConnection;
  };
}