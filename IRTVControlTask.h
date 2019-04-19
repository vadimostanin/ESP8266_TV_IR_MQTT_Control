#include <IRremoteESP8266.h>
//#include <IRrecv.h>
//#include <TaskSchedulerDeclarations.h>
#include "IRTVHitachi.h"
#include "IRTVSamsung.h"
#include <inttypes.h>
#include <functional>
#include "ISubPub.h"
#include <memory>

class IRTVControlTask
{
public:
  IRTVControlTask();
  void init();

  std::function<void()> getLoop();

  void setINet( std::shared_ptr<ISubPub> iNet );
  IRTVHitachi & getHitachi();
  IRTVSamsung & getSamsung();

private:
  void loopFunc();
  
  void emptyHandler();

  IRTVHitachi mIrHitachi;
  IRTVSamsung mIrSamsung;
  std::shared_ptr<std::function<void()>> mHandler;
};
