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
std::shared_ptr<NetworkingTask> Networking = std::make_shared<NetworkingTask>();
ClientTask pubSubClient( Networking->getPubSubClient() );
Task controlTask( 0, 0, NULL );
Task netTask( 0, 0, NULL );
Task pubSubClientTask( 0, 0, NULL );

std::string mqtt_topic_tv_hitach_youtube_on = "tv_hitachi_youtube_on";
std::string mqtt_topic_tv_hitach_youtube_initial_on = "tv_hitachi_youtube_initial_on";
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
  Serial.println( "setup enter" );
  Networking->init();
  IRTVControl.init();
  std::shared_ptr<ISubPub> iNet = Networking;
  IRTVControl.setINet( iNet );
  iNet->subscribe( mqtt_topic_tv_hitach_youtube_on, handleIRTopicYoutubeFromScratch );
  iNet->subscribe( mqtt_topic_tv_hitach_youtube_initial_on, handleIRTopicYoutubeFromScratch );
  iNet->subscribe( mqtt_topic_tv_hitach_mute, handleIRTopicMute );
  iNet->subscribe( mqtt_topic_tv_hitach_back, handleIRTopicBack );
  iNet->subscribe( mqtt_topic_tv_hitach_power, handleIRTopicPower );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_down, handleIRTopicJoystickDown );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_up, handleIRTopicJoystickUp );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_right, handleIRTopicJoystickRight );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_left, handleIRTopicJoystickLeft );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_enter, handleIRTopicJoystickEnter );
  iNet->subscribe( mqtt_topic_tv_hitach_smart, handleIRTopicSmart );
  iNet->subscribe( mqtt_topic_tv_hitach_exit, handleIRTopicExit );
  iNet->subscribe( mqtt_topic_tv_samsung_power, handleIRTopicSamsungPower );
  taskRunnerAsync.init();
  
  netTask.set( 0, TASK_FOREVER, Networking->getLoop() );
  pubSubClientTask.set( 0, TASK_FOREVER, pubSubClient.getLoop() );
  
  taskRunnerAsync.addTask( netTask );
  taskRunnerAsync.addTask( pubSubClientTask );
  
  netTask.enable();
  pubSubClientTask.enable();
  
  Serial.println( "setup leave" );
}

void reRunIRTask( int iterations )
{
  controlTask.set( 0, iterations, IRTVControl.getLoop() );
  taskRunnerAsync.addTask( controlTask );
  controlTask.enable();
}
void handleIRTopicYoutubeFromScratch()
{
  IRTVControl.getHitachi().prepareYoutubeFromTVScratchHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOnYoutubeFromScratchCount() );
}
void handleIRTopicYoutubeFromInitial()
{
  IRTVControl.getHitachi().prepareYoutubeFromTVInitialHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOnYoutubeFromScratchCount() );
}
void handleIRTopicMute()
{
  IRTVControl.getHitachi().prepareMuteHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicBack()
{
  IRTVControl.getHitachi().prepareBackHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicExit()
{
  IRTVControl.getHitachi().prepareExitHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicPower()
{
  IRTVControl.getHitachi().preparePowerHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicSmart()
{
  IRTVControl.getHitachi().prepareSmartHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicJoystickDown()
{
  IRTVControl.getHitachi().prepareJoystickDownHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicJoystickUp()
{
  IRTVControl.getHitachi().prepareJoystickUpHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicJoystickRight()
{
  IRTVControl.getHitachi().prepareJoystickRightHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicJoystickLeft()
{
  IRTVControl.getHitachi().prepareJoystickLeftHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicJoystickEnter()
{
  IRTVControl.getHitachi().prepareJoystickEnterHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicSamsungPower()
{
  IRTVControl.getSamsung().prepareSamsungPowerHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
}
void loop()
{
  taskRunnerAsync.execute();
}

