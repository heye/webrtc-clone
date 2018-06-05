#pragma once
#include "api/peerconnectioninterface.h"

namespace sample
{
  class Connection;

  // CreateOffer and CreateAnswer callback interface.
  class CreateSessionObs: public webrtc::CreateSessionDescriptionObserver
  {
    public:
     CreateSessionObs(Connection& aConn);
     void OnSuccess(webrtc::SessionDescriptionInterface* desc) override;
     void OnFailure(const std::string& error) override;


  private:
    Connection & mConnection;
  };
}