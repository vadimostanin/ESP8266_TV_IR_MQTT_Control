#include <IRremoteESP8266.h>
//#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <TaskSchedulerDeclarations.h>

#include <inttypes.h>
#include <functional>

class IRTVControlTask
{
public:
  IRTVControlTask();
  void init();

  void operator()();

  void handleTopic();
  void resetSequence();
  void setYoutubeFromTVScratchHandler();
  void setYoutubeFromTVInitialHandler();
  int32_t getLoopsOnYoutubeFromScratchCount();
  int32_t getLoopsOnYoutubeFromInitialCount();
private:
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
};
