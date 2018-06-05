#include "connobserver.h"
#include "connection.h"
namespace sample
{
  ConnectionObs::ConnectionObs(Connection & aConn)
    :mConnection(aConn)
  {
  }
  void ConnectionObs::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
  {
    mConnection.onSignalingChange(new_state);
  }
  void ConnectionObs::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
  {
  }
  void ConnectionObs::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
  {
  }
  void ConnectionObs::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
  {
  }
  void ConnectionObs::OnRenegotiationNeeded()
  {
    mConnection.onRenegotiationNeeded();
  }
  void ConnectionObs::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
  {
    mConnection.onIceConnectionChange(new_state);
  }
  void ConnectionObs::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
  {
    mConnection.onIceGatheringChange(new_state);
  }
  void ConnectionObs::OnIceCandidate(const webrtc::IceCandidateInterface * candidate)
  {
    mConnection.onIceCandidate(candidate);
  }
} // sample
