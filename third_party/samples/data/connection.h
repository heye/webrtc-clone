#pragma once
#include <string>
#include "api/peerconnectioninterface.h"
#include "connobserver.h"
#include "conndataobserver.h"
#include "setsessionobs.h"
#include "createsessionobs.h"

namespace sample
{

  class Connection
  {
    public:
     Connection();
    bool createPeerConnection(rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> aFactory, webrtc::PeerConnectionInterface::RTCConfiguration& aRtcConfig, webrtc::DataChannelInit & aDataConfig);
    void createOffer();
    void createAnswer();

    void onIceCandidate(const webrtc::IceCandidateInterface* candidate);
    void onDataStateChange();
    void onDataBufferedAmountChange(uint64_t previous_amount);
    void onDataReceived(const webrtc::DataBuffer& buffer);

    void onSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state);
    void onDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel);
    void onRenegotiationNeeded();
    void onIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state);
    void onIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state);

    void onCreateSessionSuccess(webrtc::SessionDescriptionInterface* desc);
    void onCreateSessionFailure(const std::string& error);
    void onSetSessionSuccess();
    void onSetSessionFailure(const std::string& error);


    private:
    bool createDataChannel(webrtc::DataChannelInit& aConfig);

    ConnectionObs mPeerConnObs;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> mPeerConn;
    rtc::scoped_refptr<webrtc::DataChannelInterface> mDataChannel;
    ConnectionDataObs mDataObs;
    rtc::scoped_refptr<CreateSessionObs> mCreateSession;
    rtc::scoped_refptr<SetSessionObs> mSetSession;
    std::string mConnId;
    std::string sdp_type;
  };
}