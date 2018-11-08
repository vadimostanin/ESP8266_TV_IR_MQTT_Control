#include <PubSubClient.h>

class ClientTask
{
public:
  ClientTask( PubSubClient & client );

  void operator()();

  PubSubClient & mClient;
};

