#include "conndataobserver.h"
#include "connection.h"
namespace sample
{
  ConnectionDataObs::ConnectionDataObs(Connection & aConn)
    :mConnection(aConn)
  {
  }
  void ConnectionDataObs::OnStateChange()
  {
    mConnection.onDataStateChange();
  }
  void ConnectionDataObs::OnBufferedAmountChange(uint64_t previous_amount)
  {
    mConnection.onDataBufferedAmountChange(previous_amount);
  }
  void ConnectionDataObs::OnMessage(const webrtc::DataBuffer & buffer)
  {
    mConnection.onDataReceived(buffer);
  }
}