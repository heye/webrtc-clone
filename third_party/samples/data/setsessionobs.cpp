#include "setsessionobs.h"
#include "connection.h"

namespace sample
{
  SetSessionObs::SetSessionObs(Connection & aConn)
    :mConnection(aConn)
  {
  }
  void SetSessionObs::OnSuccess()
  {
    mConnection.onSetSessionSuccess();
  }
  void SetSessionObs::OnFailure(const std::string & error)
  {
    mConnection.onSetSessionFailure(error);
  }
} // sample
