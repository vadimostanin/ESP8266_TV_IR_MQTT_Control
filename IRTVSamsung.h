#include "IRTVBase.h"

class IRTVSamsung : public IRTVBase
{
public:
  IRTVSamsung();
  void prepareSamsungPowerHandler();
  void prepareSamsungVolumeUpHandler();
  void prepareSamsungVolumeDownHandler();
  void prepareSamsungVolumeMuteUnmuteHandler();
  void prepareSamsungChannelUpHandler();
  void prepareSamsungChannelDownHandler();
  void prepareSamsungJoystickUpHandler();
  void prepareSamsungJoystickDownHandler();
  void prepareSamsungJoystickLeftHandler();
  void prepareSamsungJoystickRightHandler();
  void prepareSamsungJoystickEnterHandler();
  void prepareSamsungNumericalHandler();
  void prepareSamsungColorDotsHandler();

  int32_t getLoopsOneCommandCount();
private:

  void handleTVSamsungPower();
  void handleTVSamsungVolumeUp();
  void handleTVSamsungVolumeDown();
  void handleTVSamsungVolumeMuteUnmute();
  void handleTVSamsungChannelUp();
  void handleTVSamsungChannelDown();
  void handleTVSamsungJoystickUp();
  void handleTVSamsungJoystickDown();
  void handleTVSamsungJoystickLeft();
  void handleTVSamsungJoystickRight();
  void handleTVSamsungJoystickEnter();
  void handleTVSamsungNumerical();
  void handleTVSamsungColorDots();
  
  std::string mStatusTopic;
};

