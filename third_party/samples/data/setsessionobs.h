#pragma once
#include "api/peerconnectioninterface.h"

namespace sample
{
  class Connection;

  class SetSessionObs: public webrtc::SetSessionDescriptionObserver
  {
  public:
     SetSessionObs(Connection& aConn);
     void OnSuccess() override;
     void OnFailure(const std::string& error) override;

  private:
    Connection & mConnection;
  };
}