#include <IRremoteESP8266.h>
//#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <TaskSchedulerDeclarations.h>

#include <inttypes.h>
#include <functional>
#include "ISubPub.h"

class IRTVControlTask
{
public:
  IRTVControlTask();
  void init();

  void operator()();

  void resetSequence();
  void setMuteHandler();
  void setExitHandler();
  void setBackHandler();
  void setJoystickDownHandler();
  void setJoystickRightHandler();
  void setJoystickUpHandler();
  void setJoystickLeftHandler();
  void setJoystickEnterHandler();
  void setPowerHandler();
  void setSmartHandler();
  void setYoutubeFromTVScratchHandler();
  void setYoutubeFromTVInitialHandler();
  void setSamsungPowerHandler();
  int32_t getLoopsOnYoutubeFromScratchCount();
  int32_t getLoopsOnYoutubeFromInitialCount();
  int32_t getLoopsOneCommandCount();

  void setINet( ISubPub * iNet );
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
  void handleTVSamsungPower();
  void handleYoutubeFromTVScratch();
  void handleYoutubeFromTVInitial();
  void emptyHandler();
  const uint16_t mIrLed;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

  IRsend mIrSend;  // Set the GPIO to be used to sending the message.
  int32_t mSequenceCounter;
  int32_t mDelayTimeSum;
  int32_t mLoopCounter;
  std::function<void()> mHandler;
  int32_t mLoopsOnYoutubeFromTVScratchCount;
  int32_t mLoopsOnYoutubeFromTVInitialCount;
  int32_t mIRFrequency;

  ISubPub * mINet{nullptr};
};
