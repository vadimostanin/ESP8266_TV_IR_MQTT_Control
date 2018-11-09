#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <map>
class NetworkingTask
{
public:
  NetworkingTask();

  void operator()();
  std::function<void()> getLoop();
  void addListener( const std::string & topic, const std::function<void()> & callback );
  void init();
  PubSubClient& getPubSubClient();
  static void callbackTopic( char* topic, unsigned char* payload, unsigned int length );
  
private:
  void loopFunc();
  bool connectWiFi();
  void reconnectMQTT();
  void publishPingMQTT();

  WiFiClient wclient;
  PubSubClient mClient;
};

