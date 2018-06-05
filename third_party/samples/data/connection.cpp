#include "connection.h"

namespace sample
{
  Connection::Connection()
    : mPeerConnObs(*this)
    , mDataObs(*this)
    , mCreateSession(new rtc::RefCountedObject<CreateSessionObs>(*this))
    , mSetSession(new rtc::RefCountedObject<SetSessionObs>(*this))
    , mDataChannel(nullptr)
    , mPeerConn(nullptr)
  {
  }

  bool Connection::createPeerConnection(rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> aFactory, webrtc::PeerConnectionInterface::RTCConfiguration& aRtcConfig, webrtc::DataChannelInit & aDataConfig)
  {
    mPeerConn = aFactory->CreatePeerConnection(aRtcConfig, nullptr, nullptr, &mPeerConnObs);
    if (!mPeerConn)
    {
      return false;
    }
  
    auto isOk = createDataChannel(aDataConfig);
    if (!isOk)
    {
      return isOk;
    }
    return true;
  }

  void Connection::createOffer()
  {
    sdp_type = "Offer";
    if (mPeerConn)
    {
      mPeerConn->CreateOffer(mCreateSession.get(), nullptr);
    }
  }

  void Connection::createAnswer()
  {
    sdp_type = "Answer";
    if (mPeerConn)
    {
      mPeerConn->CreateAnswer(mCreateSession.get(), nullptr);
    }
  }

  bool Connection::createDataChannel(webrtc::DataChannelInit & aConfig)
  {
    if (!mPeerConn)
    {
      return false;
    }
    //TODO: see what about mConnId
    mDataChannel = mPeerConn->CreateDataChannel(mConnId, &aConfig);
    if (!mDataChannel)
    {
      return false;
    }
    mDataChannel->RegisterObserver(&mDataObs);
    return true;
  }

  void Connection::onIceCandidate(const webrtc::IceCandidateInterface * candidate)
  {
    icecandidate cand;
    candidate->ToString(&cand.candidatestr);
    cand.sdp_mid = candidate->sdp_mid();
    cand.sdp_mline = candidate->sdp_mline_index();
    cand.murl = candidate->server_url();
    mCandidateVec.emplace_back(std::move(cand));
  }
  void Connection::onDataStateChange()
  {
  }
  void Connection::onDataBufferedAmountChange(uint64_t previous_amount)
  {
  }
  void Connection::onDataReceived(const webrtc::DataBuffer & buffer)
  {
  }
  void Connection::onSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
  {
  }
  void Connection::onDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
  {
  }
  void Connection::onRenegotiationNeeded()
  {
  }
  void Connection::onIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
  {
  }
  void Connection::onIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
  {
  }
  void Connection::onCreateSessionSuccess(webrtc::SessionDescriptionInterface * desc)
  {
  }
  void Connection::onCreateSessionFailure(const std::string & error)
  {
  }
  void Connection::onSetSessionSuccess()
  {
  }
  void Connection::onSetSessionFailure(const std::string & error)
  {
  }
}
