#define _TASK_STD_FUNCTION
#define _TASK_SLEEP_ON_IDLE_RUN
#define ARDUINO_ARCH_ESP8266
#define _TASK_STATUS_REQUEST
#define _TASK_TIMECRITICAL
#define _TASK_PRIORITY
#include <TaskScheduler.h>

#include "IRTVControlTask.h"
#include "NetworkingTask.h"
#include "ClientTask.h"


Scheduler taskRunnerAsync;

IRTVControlTask IRTVControl;
NetworkingTask Networking;
ClientTask pubSubClient( Networking.getPubSubClient() );
Task controlTask( 0, 0, IRTVControl );
Task netTask( 0, TASK_FOREVER, Networking );
Task pubSubClientTask( 0, TASK_FOREVER, pubSubClient );

std::string mqtt_topic_tv_hitach_youtube_on = "tv_hitachi_youtube_on";

void setup()
{
  Serial.begin( 9600 );
  
  while( ! Serial )  // Wait for the serial connection to be establised.
  {
    delay( 100 );
  }
  delay( 5000 );
  Serial.println( "setup enter" );
  Serial.println();
  Networking.init();
  IRTVControl.init();
  Networking.addListener( mqtt_topic_tv_hitach_youtube_on, handleIRTopic );
  taskRunnerAsync.init();
  taskRunnerAsync.addTask( netTask );
  taskRunnerAsync.addTask( pubSubClientTask );
  netTask.enable();
  pubSubClientTask.enable();
  Serial.println( "setup leave" );
}

void handleIRTopic()
{
  Serial.println( "Catch signal to start youtube on Hitachi TV" );
  Serial.println( "Add new task" );
//  controlTask.setIterations( controlTask.getIterations() + 1 );
  taskRunnerAsync.addTask( controlTask );
  Serial.println( "Enable new task" );
  controlTask.enable();
  Serial.println( "SEND sequence of IR commands" );
}

void loop()
{
//  Serial.print( "loop" );
  taskRunnerAsync.execute();
//  delay( 100 );
}

