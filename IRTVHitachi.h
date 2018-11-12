#include "IRTVBase.h"

class IRTVHitachi : public IRTVBase
{
public:
  IRTVHitachi();
  
  void prepareMuteHandler();
  void prepareExitHandler();
  void prepareBackHandler();
  void prepareJoystickDownHandler();
  void prepareJoystickRightHandler();
  void prepareJoystickUpHandler();
  void prepareJoystickLeftHandler();
  void prepareJoystickEnterHandler();
  void preparePowerHandler();
  void prepareSmartHandler();
  void prepareYoutubeFromTVScratchHandler();
  void prepareYoutubeFromTVInitialHandler();
  int32_t getLoopsOnYoutubeFromScratchCount();
  int32_t getLoopsOnYoutubeFromInitialCount();
  int32_t getLoopsOneCommandCount();
private:
  void handleMute();
  void handleExit();
  void handleBack();
  void handleJoystickDown();
  void handleJoystickRight();
  void handleJoystickUp();
  void handleJoystickLeft();
  void handleJoystickEnter();
  void handlePower();
  void handleSmart();
  void handleYoutubeFromTVScratch();
  void handleYoutubeFromTVInitial();

  int32_t mDelayTimeSum;
  int32_t mLoopCounter;

  int32_t mLoopsOnYoutubeFromTVScratchCount;
  int32_t mLoopsOnYoutubeFromTVInitialCount;

  std::string mStatusTopic;
};

