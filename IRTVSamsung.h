#include "IRTVBase.h"
#include <map>

class IRTVSamsung : public IRTVBase
{
public:
  IRTVSamsung();

  int32_t getLoopsOneCommandCount();
  void subscribe();
  bool process( std::string topic );
private:

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
  std::map<std::string, std::function<void()>> mTopicListeners;
};

