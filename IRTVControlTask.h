#include <IRremoteESP8266.h>
//#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <TaskSchedulerDeclarations.h>

class IRTVControlTask
{
public:
  IRTVControlTask();
  void init();

  void operator()();

  void handleTopic();
private:
  const uint16_t mIrLed;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

  IRsend mIrSend;  // Set the GPIO to be used to sending the message.
};
