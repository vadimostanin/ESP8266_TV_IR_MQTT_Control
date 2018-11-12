#include "ClientTask.h"

ClientTask::ClientTask( PubSubClient & client ) : mClient( client )
{
  ;
}

void ClientTask::loopFunc()
{
//  Serial.print( "ClientTask mClient.connected()=" );Serial.println( mClient.connected() );
  mClient.loop();
  delay( 100 );
}

void ClientTask::setPubSubClient( PubSubClient & client )
{
  mClient = client;
}

std::function<void()> ClientTask::getLoop()
{
  auto func = [this](){ loopFunc(); };
  return std::bind( func );
}
