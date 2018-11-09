#include <PubSubClient.h>

class ClientTask
{
public:
  ClientTask( PubSubClient & client );
  void loopFunc();
  void setPubSubClient( PubSubClient & client );
  std::function<void()> getLoop();
private:
  PubSubClient & mClient;
};

