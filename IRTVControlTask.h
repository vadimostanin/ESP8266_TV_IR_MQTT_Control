#include <IRremoteESP8266.h>
//#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <TaskSchedulerDeclarations.h>

#include <inttypes.h>

class IRTVControlTask
{
public:
  IRTVControlTask();
  void init();

  void operator()();

  void handleTopic();
  void resetSequence();
private:
  const uint16_t mIrLed;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

  IRsend mIrSend;  // Set the GPIO to be used to sending the message.
  int32_t mSequenceCounter;
  int32_t mDelayTimeSum;
  int32_t mLoopCounter;
};
