#include "createsessionobs.h"
#include "connection.h"
namespace sample
{
  CreateSessionObs::CreateSessionObs(Connection & aConn)
    :mConnection(aConn)
  {
  }
  void CreateSessionObs::OnSuccess(webrtc::SessionDescriptionInterface * desc)
  {
    mConnection.onCreateSessionSuccess(desc);
  }
  void CreateSessionObs::OnFailure(const std::string & error)
  {
    mConnection.onCreateSessionFailure(error);
  }
} // sample
