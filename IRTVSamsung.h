#ifndef __IRTV_SAMSUNG_H__
#define __IRTV_SAMSUNG_H__
#include "IRTVBase.h"
#include <map>

namespace
{
  uint16_t rawDataSamsungPowerOn[] = {4536, 4440,  620, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  616, 512,  616, 510,  618, 510,  618, 1638,  620, 1638,  618, 1638,  618, 510,  618, 512,  616, 510,  616, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  620, 1638,  618, 510,  616, 510,  616, 1640,  618, 1638,  618, 510,  616, 512,  616, 512,  618, 45958,  4530, 4448,  618, 1640,  618, 1638,  618, 1638,  620, 510,  616, 512,  616, 510,  616, 510,  618, 510,  618, 1638,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 510,  618, 510,  618, 510,  616, 510,  618, 1638,  618, 1638,  618, 510,  618, 510,  618, 1638,  618, 1640,  618, 1638,  618, 1638,  618, 510,  618, 512,  616, 1638,  618, 1638,  620, 510,  624, 504,  618, 510,  618};  // SAMSUNG E0E06798
  uint16_t rawDataSamsungVolumeUp[] = {};
  uint16_t rawDataSamsungVolumeDown[] = {};
  uint16_t rawDataSamsungVolumeMuteUnmute[] = {};
  uint16_t rawDataSamsungChannelUp[] = {};
  uint16_t rawDataSamsungChannelDown[] = {};
  uint16_t rawDataSamsungBack[] = {};
  uint16_t rawDataSamsungHome[] = {};
  uint16_t rawDataSamsungPlayPause[] = {};
  uint16_t rawDataSamsungJoystickUp[] = {};
  uint16_t rawDataSamsungJoystickDown[] = {};
  uint16_t rawDataSamsungJoystickLeft[] = {};
  uint16_t rawDataSamsungJoystickRight[] = {};
  uint16_t rawDataSamsungJoystickEnter[] = {};
  uint16_t rawDataSamsungNumerical[] = {};
  uint16_t rawDataSamsungColorDots[] = {};
}

#define SIZEOF( ARRAY ) ( sizeof( ARRAY ) / sizeof( ARRAY[0] ) )

#define IRTOPIC_FUNC_PREPARE(devtype, devmodel, devcommand, rawBytes)\
void prepare_##devtype##_##devmodel##_##devcommand()\
{\
  resetSequence();\
  (*mHandler) = std::bind( &IRTVSamsung::handle_##devtype##_##devmodel##_##devcommand, this );\
}\
void handle_##devtype##_##devmodel##_##devcommand()\
{\
  /*Serial.println( "##devtype## ##devmodel## ##devcommand On" );*/\
  mIrSend.sendRaw( rawBytes, SIZEOF( rawBytes ), mIRFrequency );\
  mINet->publish( mStatusTopic.c_str(), "##devtype## ##devmodel## ##devcommand" );\
}
#define IRTOPIC_FUNC_PREPARE_GET(devtype, devmodel, devcommand) prepare_##devtype##_##devmodel##_##devcommand
#define IRTOPIC_TVSAM_FUNC_PREPARE_GET(devcommand) IRTOPIC_FUNC_PREPARE_GET(tv, samsung, devcommand)
#define IRTOPIC_STR(devtype, devmodel, devcommand) std::string mqtt_topic_##devtype##_##devmodel##_##devcommand = "##devtype##_##devmodel##_##dev_command";
#define IRTOPIC_STR_GET(dev_type, dev_model, dev_command) mqtt_topic_##dev_type##_##dev_model##_##dev_command
#define IRTOPIC_TVSAM_STR_GET(dev_command) IRTOPIC_STR_GET(tv, samsung, dev_command)

#define IRTOPIC_STR_AND_FUNC(devtype, devmodel, devcommand, rawBytes)\
IRTOPIC_STR(devtype, devmodel, devcommand)\
IRTOPIC_FUNC_PREPARE(devtype, devmodel, devcommand, rawBytes)

#define IRTOPIC_TVSAM_STR_AND_FUNC(devcommand, rawBytes) IRTOPIC_STR_AND_FUNC(tv, samsung, devcommand, rawBytes)

class IRTVSamsung : public IRTVBase
{
public:
  IRTVSamsung();

  int32_t getLoopsOneCommandCount();
  void subscribe();
  bool process( std::string topic );
private:

  IRTOPIC_TVSAM_STR_AND_FUNC(power, rawDataSamsungPowerOn)
  IRTOPIC_TVSAM_STR_AND_FUNC(volume_up, rawDataSamsungVolumeUp)
  IRTOPIC_TVSAM_STR_AND_FUNC(volume_down, rawDataSamsungVolumeDown)
  IRTOPIC_TVSAM_STR_AND_FUNC(volume_muteunmute, rawDataSamsungVolumeMuteUnmute)
  IRTOPIC_TVSAM_STR_AND_FUNC(channel_up, rawDataSamsungChannelUp)
  IRTOPIC_TVSAM_STR_AND_FUNC(channel_down, rawDataSamsungChannelDown)
  IRTOPIC_TVSAM_STR_AND_FUNC(joystick_up, rawDataSamsungJoystickUp)
  IRTOPIC_TVSAM_STR_AND_FUNC(joystick_down, rawDataSamsungJoystickDown)
  IRTOPIC_TVSAM_STR_AND_FUNC(joystick_left, rawDataSamsungJoystickLeft)
  IRTOPIC_TVSAM_STR_AND_FUNC(joystick_right, rawDataSamsungJoystickRight)
  IRTOPIC_TVSAM_STR_AND_FUNC(joystick_enter, rawDataSamsungJoystickEnter)
  IRTOPIC_TVSAM_STR_AND_FUNC(numerical, rawDataSamsungNumerical)
  IRTOPIC_TVSAM_STR_AND_FUNC(colordots, rawDataSamsungColorDots)
  
  std::string mStatusTopic;
  std::map<std::string, std::function<void()>> mTopicListeners;
};

#endif
