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
Task controlTask( 0, 0, NULL );
Task netTask( 0, 0, NULL );
Task pubSubClientTask( 0, 0, NULL );

std::string mqtt_topic_tv_hitach_youtube_on = "tv_hitachi_youtube_on";
std::string mqtt_topic_tv_hitach_mute = "tv_hitachi_mute";
std::string mqtt_topic_tv_hitach_back = "tv_hitachi_back";
std::string mqtt_topic_tv_hitach_power = "tv_hitachi_power";
std::string mqtt_topic_tv_hitach_joystick_down = "tv_hitachi_joystick_down";
std::string mqtt_topic_tv_hitach_joystick_up = "tv_hitachi_joystick_up";
std::string mqtt_topic_tv_hitach_joystick_right = "tv_hitachi_joystick_right";
std::string mqtt_topic_tv_hitach_joystick_left = "tv_hitachi_joystick_left";
std::string mqtt_topic_tv_hitach_joystick_enter = "tv_hitachi_joystick_enter";
std::string mqtt_topic_tv_hitach_smart = "tv_hitachi_smart";
std::string mqtt_topic_tv_hitach_exit = "tv_hitachi_exit";
std::string mqtt_topic_tv_samsung_power = "tv_samsung_power";

void setup()
{
  Serial.begin( 9600 );
  
  while( ! Serial )  // Wait for the serial connection to be establised.
  {
    delay( 100 );
  }
  delay( 5000 );
  Serial.println( "setup enter" );
  Networking.init();
  IRTVControl.init();
  ISubPub & iNet = Networking;
  IRTVControl.setINet( &iNet );
  iNet.subscribe( mqtt_topic_tv_hitach_youtube_on, handleIRTopicYoutubeFromScratch );
  iNet.subscribe( mqtt_topic_tv_hitach_mute, handleIRTopicMute );
  iNet.subscribe( mqtt_topic_tv_hitach_back, handleIRTopicBack );
  iNet.subscribe( mqtt_topic_tv_hitach_power, handleIRTopicPower );
  iNet.subscribe( mqtt_topic_tv_hitach_joystick_down, handleIRTopicJoystickDown );
  iNet.subscribe( mqtt_topic_tv_hitach_joystick_up, handleIRTopicJoystickUp );
  iNet.subscribe( mqtt_topic_tv_hitach_joystick_right, handleIRTopicJoystickRight );
  iNet.subscribe( mqtt_topic_tv_hitach_joystick_left, handleIRTopicJoystickLeft );
  iNet.subscribe( mqtt_topic_tv_hitach_joystick_enter, handleIRTopicJoystickEnter );
  iNet.subscribe( mqtt_topic_tv_hitach_smart, handleIRTopicSmart );
  iNet.subscribe( mqtt_topic_tv_hitach_exit, handleIRTopicExit );
  iNet.subscribe( mqtt_topic_tv_samsung_power, handleIRTopicSamsungPower );
  taskRunnerAsync.init();
  
  netTask.set( 0, TASK_FOREVER, Networking.getLoop() );
  pubSubClientTask.set( 0, TASK_FOREVER, pubSubClient.getLoop() );
  
  taskRunnerAsync.addTask( netTask );
  taskRunnerAsync.addTask( pubSubClientTask );
  
  netTask.enable();
  pubSubClientTask.enable();
  
  Serial.println( "setup leave" );
}

void handleIRTopicYoutubeFromScratch()
{
  IRTVControl.resetSequence();
  IRTVControl.setYoutubeFromTVScratchHandler();
  controlTask.set( 0, IRTVControl.getLoopsOnYoutubeFromScratchCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicMute()
{
  IRTVControl.resetSequence();
  IRTVControl.setMuteHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicBack()
{
  IRTVControl.resetSequence();
  IRTVControl.setBackHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicExit()
{
  IRTVControl.resetSequence();
  IRTVControl.setExitHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicPower()
{
  IRTVControl.resetSequence();
  IRTVControl.setPowerHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicSmart()
{
  IRTVControl.resetSequence();
  IRTVControl.setSmartHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicJoystickDown()
{
  IRTVControl.resetSequence();
  IRTVControl.setJoystickDownHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicJoystickUp()
{
  IRTVControl.resetSequence();
  IRTVControl.setJoystickUpHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicJoystickRight()
{
  IRTVControl.resetSequence();
  IRTVControl.setJoystickRightHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicJoystickLeft()
{
  IRTVControl.resetSequence();
  IRTVControl.setJoystickLeftHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicJoystickEnter()
{
  IRTVControl.resetSequence();
  IRTVControl.setJoystickEnterHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void handleIRTopicSamsungPower()
{
  IRTVControl.resetSequence();
  IRTVControl.setSamsungPowerHandler();
  controlTask.set( 0, IRTVControl.getLoopsOneCommandCount(), IRTVControl );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}

void loop()
{
//  Serial.print( "loop" );
  taskRunnerAsync.execute();
//  delay( 100 );
}

