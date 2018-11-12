#include <IRsend.h>
#include <IRutils.h>
#include "ISubPub.h"
#include <memory>

class IRTVSamsung
{
public:
  IRTVSamsung();
  void init();
  void resetSequence();
  void setINet( std::shared_ptr<ISubPub> iNet );
  void setChangableHandler( std::shared_ptr<std::function<void()>> handler );
  void prepareSamsungPowerHandler();
  void handleTVSamsungPower();

  int32_t getLoopsOneCommandCount();
private:
  std::shared_ptr<ISubPub> mINet{nullptr};
  std::shared_ptr<std::function<void()>> mHandler{nullptr};

  const uint16_t mIrLed;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
  IRsend mIrSend;  // Set the GPIO to be used to sending the message.
  int32_t mSequenceCounter;
  std::string mStatusTopic;
};

