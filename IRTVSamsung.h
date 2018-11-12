#include "IRTVBase.h"

class IRTVSamsung : public IRTVBase
{
public:
  IRTVSamsung();
  void prepareSamsungPowerHandler();
  void handleTVSamsungPower();

  int32_t getLoopsOneCommandCount();
private:

  std::string mStatusTopic;
};

