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
#include <inttypes.h>

Scheduler taskRunnerAsync;

IRTVControlTask IRTVControl;
NetworkingTask Networking;
ClientTask pubSubClient( Networking.getPubSubClient() );
const int32_t controlTaskIterations = 92;// depends on IRTVControlTask::mLoopCounter
Task controlTask( 0, 0, NULL );
Task netTask( 0, 0, NULL );
Task pubSubClientTask( 0, 0, NULL );

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
  Networking.addListener( mqtt_topic_tv_hitach_youtube_on, handleIRTopicYoutubeFromScratch );
  taskRunnerAsync.init();
  
  netTask.set( 0, TASK_FOREVER, Networking.getLoop() );
//  pubSubClient.setPubSubClient( Networking.getPubSubClient() );
  pubSubClientTask.set( 0, TASK_FOREVER, pubSubClient.getLoop() );
  
  taskRunnerAsync.addTask( netTask );
  taskRunnerAsync.addTask( pubSubClientTask );
  
  netTask.enable();
  pubSubClientTask.enable();
  
  Serial.println( "setup leave" );
}

void handleIRTopicYoutubeFromScratch()
{
  Serial.println( "Catch signal to start youtube on Hitachi TV" );
  Serial.println( "Add new task" );
  IRTVControl.resetSequence();
  IRTVControl.setYoutubeFromTVScratchHandler();
  Serial.printf( "%s: controlTask.getIterations()=%d\n", __FUNCTION__, controlTask.getIterations() );
  controlTask.set( 0, IRTVControl.getLoopsOnYoutubeFromScratchCount(), IRTVControl );
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

