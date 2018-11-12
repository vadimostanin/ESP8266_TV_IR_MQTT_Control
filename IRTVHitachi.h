#include <IRsend.h>
#include <IRutils.h>
#include "ISubPub.h"
#include <memory>

class IRTVHitachi
{
public:
  IRTVHitachi();
  void init();
  void resetSequence();
  void setINet( std::shared_ptr<ISubPub> iNet );
  void setChangableHandler( std::shared_ptr<std::function<void()>> handler );
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

  const uint16_t mIrLed;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

  IRsend mIrSend;  // Set the GPIO to be used to sending the message.
  int32_t mSequenceCounter;
  int32_t mDelayTimeSum;
  int32_t mLoopCounter;

  int32_t mLoopsOnYoutubeFromTVScratchCount;
  int32_t mLoopsOnYoutubeFromTVInitialCount;
  int32_t mIRFrequency;

  std::shared_ptr<ISubPub> mINet{nullptr};
  std::shared_ptr<std::function<void()>> mHandler;

  std::string mStatusTopic;
};

