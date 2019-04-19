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
std::string mqtt_topic_tv_samsung_volume_up = "tv_samsung_volume_up";
std::string mqtt_topic_tv_samsung_volume_down = "tv_samsung_volume_down";
std::string mqtt_topic_tv_samsung_volume_muteunmute = "tv_samsung_volume_muteunmute";
std::string mqtt_topic_tv_samsung_channel_up = "tv_samsung_channel_up";
std::string mqtt_topic_tv_samsung_channel_down = "tv_samsung_channel_down";
std::string mqtt_topic_tv_samsung_joystick_up = "tv_samsung_joystick_up";
std::string mqtt_topic_tv_samsung_joystick_down = "tv_samsung_joystick_down";
std::string mqtt_topic_tv_samsung_joystick_left = "tv_samsung_joystick_left";
std::string mqtt_topic_tv_samsung_joystick_right = "tv_samsung_joystick_right";
std::string mqtt_topic_tv_samsung_joystick_enter = "tv_samsung_joystick_enter";
std::string mqtt_topic_tv_samsung_numerical = "tv_samsung_numerical";
std::string mqtt_topic_tv_samsung_colordots = "tv_samsung_colordots";

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
  iNet->subscribe( mqtt_topic_tv_hitach_youtube_on, handleIRTopicHitachiYoutubeFromScratch );
  iNet->subscribe( mqtt_topic_tv_hitach_youtube_initial_on, handleIRTopicHitachiYoutubeFromScratch );
  iNet->subscribe( mqtt_topic_tv_hitach_mute, handleIRTopicHitachiMute );
  iNet->subscribe( mqtt_topic_tv_hitach_back, handleIRTopicHitachiBack );
  iNet->subscribe( mqtt_topic_tv_hitach_power, handleIRTopicHitachiPower );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_down, handleIRTopicHitachiJoystickDown );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_up, handleIRTopicHitachiJoystickUp );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_right, handleIRTopicHitachiJoystickRight );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_left, handleIRTopicHitachiJoystickLeft );
  iNet->subscribe( mqtt_topic_tv_hitach_joystick_enter, handleIRTopicHitachiJoystickEnter );
  iNet->subscribe( mqtt_topic_tv_hitach_smart, handleIRTopicHitachiSmart );
  iNet->subscribe( mqtt_topic_tv_hitach_exit, handleIRTopicHitachiExit );

  iNet->subscribe( mqtt_topic_tv_samsung_power, handleIRTopicSamsungPower );
  iNet->subscribe( mqtt_topic_tv_samsung_volume_up, handleIRTopicSamsungVolumeUp );
  iNet->subscribe( mqtt_topic_tv_samsung_volume_down, handleIRTopicSamsungVolumeDown );
  iNet->subscribe( mqtt_topic_tv_samsung_volume_muteunmute, handleIRTopicSamsungVolumeMuteUnmute );
  iNet->subscribe( mqtt_topic_tv_samsung_channel_up, handleIRTopicSamsungChannelUp );
  iNet->subscribe( mqtt_topic_tv_samsung_channel_down, handleIRTopicSamsungChannelDown );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_up, handleIRTopicSamsungJoystickUp );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_down, handleIRTopicSamsungJoystickDown );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_left, handleIRTopicSamsungJoystickLeft );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_right, handleIRTopicSamsungJoystickRight );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_enter, handleIRTopicSamsungJoystickEnter );
  iNet->subscribe( mqtt_topic_tv_samsung_numerical, handleIRTopicSamsungNumerical );
  iNet->subscribe( mqtt_topic_tv_samsung_colordots, handleIRTopicSamsungColorDots );
  
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
void handleIRTopicHitachiYoutubeFromScratch()
{
  IRTVControl.getHitachi().prepareYoutubeFromTVScratchHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOnYoutubeFromScratchCount() );
}
void handleIRTopicHitachiYoutubeFromInitial()
{
  IRTVControl.getHitachi().prepareYoutubeFromTVInitialHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOnYoutubeFromScratchCount() );
}
void handleIRTopicHitachiMute()
{
  IRTVControl.getHitachi().prepareMuteHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiBack()
{
  IRTVControl.getHitachi().prepareBackHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiExit()
{
  IRTVControl.getHitachi().prepareExitHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiPower()
{
  IRTVControl.getHitachi().preparePowerHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiSmart()
{
  IRTVControl.getHitachi().prepareSmartHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiJoystickDown()
{
  IRTVControl.getHitachi().prepareJoystickDownHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiJoystickUp()
{
  IRTVControl.getHitachi().prepareJoystickUpHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiJoystickRight()
{
  IRTVControl.getHitachi().prepareJoystickRightHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiJoystickLeft()
{
  IRTVControl.getHitachi().prepareJoystickLeftHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicHitachiJoystickEnter()
{
  IRTVControl.getHitachi().prepareJoystickEnterHandler();
  reRunIRTask( IRTVControl.getHitachi().getLoopsOneCommandCount() );
}
void handleIRTopicSamsungPower()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungPowerHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungVolumeUp()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungVolumeUpHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungVolumeDown()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungVolumeDownHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungVolumeMuteUnmute()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungVolumeMuteUnmuteHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungChannelUp()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungChannelUpHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungChannelDown()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungChannelDownHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungJoystickUp()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungJoystickUpHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungJoystickDown()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungJoystickDownHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungJoystickLeft()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungJoystickLeftHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungJoystickRight()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungJoystickRightHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungJoystickEnter()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungJoystickEnterHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungNumerical()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungNumericalHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}
void handleIRTopicSamsungColorDots()
{
  //Serial.println( "handleIRTopicSamsungPower 1" );
  IRTVControl.getSamsung().prepareSamsungColorDotsHandler();
  reRunIRTask( IRTVControl.getSamsung().getLoopsOneCommandCount() );
  //Serial.println( "handleIRTopicSamsungPower 2" );
}

void loop()
{
  taskRunnerAsync.execute();
}

