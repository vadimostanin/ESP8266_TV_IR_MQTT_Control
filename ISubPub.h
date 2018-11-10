#include <string>
#include <functional>

class IPubSub
{
  virtual void subscribe( std::string topic, std::function<void()> callback ) = 0;
  virtual void publish( std::string topic, std::string message ) = 0;
};

