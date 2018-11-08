#include "ClientTask.h"

ClientTask::ClientTask( PubSubClient & client ) : mClient( client )
{
  ;
}

void ClientTask::operator()()
{
  mClient.loop();
}

