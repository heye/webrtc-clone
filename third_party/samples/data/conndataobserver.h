#pragma once
#include "api/peerconnectioninterface.h"

namespace sample
{
  class Connection;

  class ConnectionDataObs : public webrtc::DataChannelObserver
  {
    public:
     ConnectionDataObs(Connection& aConn);

  protected:
     void OnStateChange() override;
     void OnBufferedAmountChange(uint64_t previous_amount) override;
     void OnMessage(const webrtc::DataBuffer& buffer) override;

  private:
    Connection & mConnection;
  };
}