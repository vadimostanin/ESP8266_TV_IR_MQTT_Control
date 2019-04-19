#ifndef _IRTVBASE_H__
#define _IRTVBASE_H__

#include <IRsend.h>
#include <IRutils.h>
#include "ISubPub.h"
#include <memory>

class IRTVBase
{
public:
  IRTVBase( int32_t irPin );
  void init();
  void resetSequence();
  void setINet( std::shared_ptr<ISubPub> iNet );
  void setChangableHandler( std::shared_ptr<std::function<void()>> handler );
protected:
  const uint16_t mIrLed;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

  IRsend mIrSend;  // Set the GPIO to be used to sending the message.
  int32_t mSequenceCounter;

  int32_t mIRFrequency;

  std::shared_ptr<ISubPub> mINet{nullptr};
  std::shared_ptr<std::function<void()>> mHandler{nullptr};

};
#endif
