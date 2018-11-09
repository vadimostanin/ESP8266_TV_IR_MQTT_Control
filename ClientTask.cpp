#include "ClientTask.h"

ClientTask::ClientTask( PubSubClient & client ) : mClient( client )
{
  ;
}

void ClientTask::operator()()
{
  Serial.print( "mClient.connected()=" );Serial.println( mClient.connected() );
  mClient.loop();
  delay( 100 );
}

