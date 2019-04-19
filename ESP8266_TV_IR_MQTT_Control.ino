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
std::string mqtt_topic_any = "*";

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
  iNet->subscribe( handleIRTopicAny );
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

  static const auto emptyFunc = [](){};
  iNet->subscribe( mqtt_topic_tv_samsung_power, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_volume_up, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_volume_down, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_volume_muteunmute, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_channel_up, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_channel_down, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_up, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_down, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_left, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_right, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_joystick_enter, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_numerical, emptyFunc );
  iNet->subscribe( mqtt_topic_tv_samsung_colordots, emptyFunc );

  IRTVControl.getSamsung().subscribe();
  iNet->subscribe( handleIRTopicAny );
  
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
void handleIRTopicAny( std::string topic )
{
  if( IRTVControl.getHitachi().process( topic ) )
  {
    reRunIRTask( 1 /*IRTVControl.getHitachi().getLoopsOnYoutubeFromScratchCount()*/ );
  }
  else if( IRTVControl.getSamsung().process( topic ) )
  {
    reRunIRTask( 1 /*IRTVControl.getSamsung().getLoopsOnYoutubeFromScratchCount()*/ );
  }
  else
  {
    Serial.println( "Handler wan't found" );
  }
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

void loop()
{
  taskRunnerAsync.execute();
}

